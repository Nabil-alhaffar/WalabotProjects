from __future__ import print_function,absolute_import, division, print_function # WalabotAPI works on both Python 2 an 3.
from sys import platform
from os import system
from imp import load_source
from os.path import join
import time
import numpy as np
import matplotlib.pyplot as plt

import warnings
warnings.filterwarnings("ignore")


if platform == 'win32':
    modulePath = join('C:/', 'Program Files', 'Walabot', 'WalabotSDK',
                      'python', 'WalabotAPI.py')
elif platform.startswith('linux'):
    modulePath = join('/usr', 'share', 'walabot', 'python', 'WalabotAPI.py')

wlbt = load_source('WalabotAPI', modulePath)
wlbt.Init()


def PrintBreathingEnergy(energy):
    system('cls' if platform == 'win32' else 'clear')
    print('Energy = {}'.format(energy))


def BreathingApp():
    # Walabot_SetArenaR - input parameters
    minInCm, maxInCm, resInCm = 20, 80, 0.2
    # Walabot_SetArenaTheta - input parameters
    minIndegrees, maxIndegrees, resIndegrees = -1, 1, 1
    # Walabot_SetArenaPhi - input parameters
    minPhiInDegrees, maxPhiInDegrees, resPhiInDegrees = -1, 1, 1
    # Initializes walabot lib
    wlbt.Initialize()
    # 1) Connect : Establish communication with walabot.
    wlbt.ConnectAny()
    # 2) Configure: Set scan profile and arena
    # Set Profile - to Sensor-Narrow.
    wlbt.SetProfile(wlbt.PROF_SENSOR_NARROW)
    # Setup arena - specify it by Cartesian coordinates.
    wlbt.SetArenaR(minInCm, maxInCm, resInCm)
    # Sets polar range and resolution of arena (parameters in degrees).
    wlbt.SetArenaTheta(minIndegrees, maxIndegrees, resIndegrees)
    # Sets azimuth range and resolution of arena.(parameters in degrees).
    wlbt.SetArenaPhi(minPhiInDegrees, maxPhiInDegrees, resPhiInDegrees)
    # Dynamic-imaging filter for the specific frequencies typical of breathing
    wlbt.SetDynamicImageFilter(wlbt.FILTER_TYPE_NONE)
    # 3) Start: Start the system in preparation for scanning.
    wlbt.Start()
    while True:
        for i in range(2): ##round starts
            energy_vals = []
            ##start = time.time()
            for i in range(25):
                appStatus, calibrationProcess = wlbt.GetStatus()
                # 5) Trigger: Scan(sense) according to profile and record signals
                # to be available for processing and retrieval.
                wlbt.Trigger()
                # 6) Get action: retrieve the last completed triggered recording
                energy = wlbt.GetImageEnergy()
                energy_vals.append(energy)
                # PrintBreathingEnergy(energy)
                PrintBreathingEnergy(energy)
            # 7) Stop and Disconnect.
            ##end = time.time()
            ##duration= end- start

            result = 0

            energy_vals.append(result)  ##append result to new row of data

            all = np.loadtxt("test.csv", delimiter=",")  ##open existing csv

            ar = np.vstack([all, energy_vals])  ##APPEND NEW ROW to data file

            np.savetxt("test.csv", ar, delimiter=',', fmt="%10.5f")  ## SAVE

            print("round completed")

        #    print()

        ##plt.plot(energy_vals)
        ##plt.show()
        time.sleep(8)
        print("READY")
        time.sleep(2)

    wlbt.Stop()
    wlbt.Disconnect()
    wlbt.Clean()

    print('Terminate successfully')


if __name__ == '__main__':
    BreathingApp()
