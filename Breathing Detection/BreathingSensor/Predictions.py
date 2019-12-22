from __future__ import print_function, absolute_import, division, \
    print_function  # WalabotAPI works on both Python 2 an 3.
from sys import platform
from os import system
from imp import load_source
from os.path import join
from phue import Bridge
import time
import numpy as np
import matplotlib.pyplot as plt
import warnings
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import confusion_matrix, precision_recall_curve, roc_auc_score, roc_curve, accuracy_score
from sklearn.ensemble import RandomForestClassifier
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
    ###load and train model

    data = np.loadtxt('test.csv', delimiter=',')

    COLUMNS_IN = 25
    COLUMNS_OUT = 1

    X = data[:, 0:COLUMNS_IN]
    y = data[:, COLUMNS_IN:(COLUMNS_IN + COLUMNS_OUT)]

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.0, random_state=11111)

    rf_model = RandomForestClassifier(n_estimators=1000)
    rf_model.fit(X_train, y_train)


    b = Bridge('10.99.58.50')
    lights = b.lights[1:2]

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

    # 4) Trigger: Scan (sense) according to profile and record signals to be
    # available for processing and retrieval.
    while True:
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

        ##make a prediction
        t = []
        t.append(energy_vals)
        y_pred_class_rf = rf_model.predict(t)
        print(y_pred_class_rf[0])  ##print prediction
        if y_pred_class_rf[0] != 0:
            b.set_light(2, 'bri', 200)
        else:
            b.set_light(2, 'bri', 0 )

    wlbt.Stop()
    wlbt.Disconnect()
    wlbt.Clean()

    # 7) Stop and Disconnect.

    ##max_slope=0

    ##for i in range (0,7,1):
    ##    slope = abs(energy_vals[i] - energy_vals[i+2]/2)
    ##    if slope > max_slope:
    ##        max_slope = slope
    ##print('Max Slope={}'.format(max_slope))
    ##t = [i for y in range(10)]
    # plt.plot(energy_vals)
    # plt.show()

    ##result = int(input("result: "))


if __name__ == '__main__':
    BreathingApp()

