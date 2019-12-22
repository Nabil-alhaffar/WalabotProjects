from __future__ import print_function  # WalabotAPI works on both Python 2 an 3.
from __future__ import print_function  # WalabotAPI works on both Python 2 an 3.
import sys
import math
import operator
import time
from sys import platform
from os import system
from imp import load_source
from os.path import join
from twilio.rest import Client
import tkinter


try:
    import Queue
except ImportError:
    import queue as Queue

MIN_PERSON_HEIGHT = 130
MAX_PERSON_HEIGHT = 210
FALL_THRESHOLD_MAX = 50
FALL_THRESHOLD_MIN = 10
R_MAX = 400
R_MIN = 10
R_RES = 5
THETA_MIN = -45
THETA_MAX = 45
THETA_RES = 10
PHI_MIN = -45
PHI_MAX = 45
PHI_RES = 5
THRESHOLD = 35

if platform == 'win32':
    modulePath = join('C:/', 'Program Files', 'Walabot', 'WalabotSDK',
                      'python', 'WalabotAPI.py')
elif platform.startswith('linux'):
    modulePath = join('/usr', 'share', 'walabot', 'python', 'WalabotAPI.py')

def SendMsg():
    # Your Account SID from twilio.com/console
    account_sid = "AC7bc8a2bcee268407fd9672306a703b3d"
    # Your Auth Token from twilio.com/console
    auth_token = "2ec77307b5c81ec1728883ea9e50d3ea"

    client = Client(account_sid, auth_token)

    message = client.messages.create(
        to="+18124701987",
        from_="+12024173280",
        body="EMERGENCY ALERT: Someone has Fallen!")

    print(message.sid)

class FallDetector:

    def __init__(self, *args):
        self.wlbt = load_source('WalabotAPI', modulePath)
        self.wlbt.Init()
        self.clearCommandLine = False

    def verifyWalabotIsConnected(self):
        """ Check for Walabot connectivity. loop until detect a Walabot.
        """
        while True:
            try:
                self.wlbt.ConnectAny()
            except self.wlbt.WalabotError as err:
                input("- Connect Walabot and press 'Enter'.")
                print(err)
            else:
                print('- Connection to Walabot established.')
                return

    def setWalabotSettings(self):
        """ Configure Walabot's profile, arena (r, theta, phi), threshold and
            the image filter.
        """
        self.wlbt.SetProfile(self.wlbt.PROF_TRACKER)
        self.wlbt.SetArenaTheta(THETA_MIN, THETA_MAX, THETA_RES)
        self.wlbt.SetArenaPhi(PHI_MIN, PHI_MAX, PHI_RES)
        self.wlbt.SetArenaR(R_MIN, R_MAX, R_RES)
        self.wlbt.SetThreshold(THRESHOLD)
        self.wlbt.SetDynamicImageFilter(self.wlbt.FILTER_TYPE_MTI)

        print('- Walabot Configured.')

    def is_target_a_person(self, room_height, target):
        person_height = room_height - target.zPosCm
        return (person_height > MIN_PERSON_HEIGHT and person_height < MAX_PERSON_HEIGHT)

    def did_person_fall(self, room_height, target, Fall_threshold):
        person_height = room_height - target.zPosCm
        if person_height < 0:
            return False
        return (person_height < Fall_threshold and person_height > FALL_THRESHOLD_MIN)

    def FallDetectionInit(self):
        # Initializes walabot lib
        self.wlbt.Initialize()
        # Connect
        self.verifyWalabotIsConnected()
        # Configure
        self.setWalabotSettings()
        # Start
        self.wlbt.Start()
        self.recognized = False
        self.Falling_Buffer = -1
        self.Standing_Buffer = 0
        self.No_Target_Buffer = 0
        self.flag = False

    def FallDetectionCheck(self, height, Fall_threshold, Position_confidenceFactor, framesToIndicateFall):
        # print('Recognized: {}'.format(recognized))
        # 5) Trigger: Scan(sense) according to profile and record signals
        # to be available for processing and retrieval.
        # print('Position_confidenceFactor: {}, framesToIndicateFall: {}'.format(Position_confidenceFactor,framesToIndicateFall))
        self.wlbt.Trigger()

        # 6) Get action: retrieve the last completed triggered recording
        targets = self.wlbt.GetTrackerTargets()

        # 7) Checking if targets were detected in Position_confidenceFactor frames:
        if len(targets) == 0:
            if (self.clearCommandLine):
                system('cls' if platform == 'win32' else 'clear')
                print('No Target Detected')

            if self.No_Target_Buffer < Position_confidenceFactor:
                self.No_Target_Buffer += 1  # Counting the number of frames in which no target is detected
            else:
                print('No Target Detected')
                # self.Falling_Buffer = -1                                                                   # Initializing Falling buffer
                self.Standing_Buffer = 0  # Initializing Standing buffer
            return (0, self.flag, [])
            # continue

        self.No_Target_Buffer = 0  # Initializing No_Target buffer

        # 8) Searching for the index of the target with the minimal zPosCm (the nearest to the ceiling).
        zPositions = [target.zPosCm for target in targets]  # Creating a list of the z positions

        index = zPositions.index(min(zPositions))

        # 9) Checking if a person is recognized (standing):
        self.recognized = self.is_target_a_person(height, targets[index])

        if self.recognized:
            if self.flag:  # Gets TRUE if a person fell. The purpose is to restart the buffers when standing person is recognized after falling occured.
                self.Falling_Buffer = -1
                self.Standing_Buffer = 0
                self.flag = False

            # if (self.clearCommandLine) :
            #   system('cls' if platform == 'win32' else 'clear')
            print('Recognized a person. Height:', round(height - targets[index].zPosCm, 1), '[cm]')

            if self.Standing_Buffer < Position_confidenceFactor:  # Counting the number of consecutive frames in which a person is detected
                self.Standing_Buffer += 1
            else:
                self.Falling_Buffer = 0


        # 10) Checking if the person fell:
        else:
            if self.Falling_Buffer != -1 and self.did_person_fall(height, targets[index], Fall_threshold):
                print('Fall height:', round(height - targets[index].zPosCm, 1), '[cm]')
                if self.Falling_Buffer < framesToIndicateFall:
                    self.Falling_Buffer += 1
                else:
                    print('Person fell!!!')
                    SendMsg()
                    self.flag = True
        if height - targets[index].zPosCm > FALL_THRESHOLD_MIN:
            return (height - targets[index].zPosCm, self.flag, [targets[index]])
        return (0, self.flag, [targets[index]])

    def FallDetectionEnd(self):
        # Stop and Disconnect.
        self.wlbt.Stop()
        self.wlbt.Disconnect()
        self.wlbt.Clean()
        print('Terminate successfully')


class FallDetectionAgent():
    def __init__(self, *args):
        self.height = args[0]
        self.Fall_threshold = args[1]
        self.Position_confidenceFactor = args[2]
        self.framesToIndicateFall = args[3]

        self._detector = FallDetector()


if __name__ == '__main__':
    height = 255
    fallDetectorAgent = FallDetectionAgent(float(height), 50, 5, 10)
    fallDetectorAgent._detector.FallDetectionInit()
    while True:
        fallDetectorAgent._detector.FallDetectionCheck(fallDetectorAgent.height, fallDetectorAgent.Fall_threshold,
                                                       fallDetectorAgent.Position_confidenceFactor,
                                                       fallDetectorAgent.framesToIndicateFall)
    fallDetectorAgent._detector.FallDetectionEnd()






