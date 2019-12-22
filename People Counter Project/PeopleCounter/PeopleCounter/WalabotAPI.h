#pragma once

/******************************************************************************
* CONFIDENTIAL AND PROPRIETARY DATA											  *
*===================================										  *
*																			  *
* Copyright 2015 Vayyar Imaging Ltd. All rights reserved.					  *
*																			  *
* This document is the property of Vayyar and all  materials  and information *
* contained herein are the confidential and proprietary information of Vayyar *
* and are protected by international copyright laws. The copyrights are owned *
* by  Vayyar  or  the  original  creator  of the material.  The materials and *
* information contained herein  are provided to you  for internal information *
* purposes only,  and no portion of the materials and  information herein may *
* be  copied,  reproduced,  distributed,  transmitted,  displayed, published, *
* broadcasted  or  used  in any way whatsoever directly or indirectly without *
* the  prior  written  consent  of  Vayyar  or  in  any  case  of third party *
* materials,  without  that  third  party's  consent.  This document shall be *
* returned to Vayyar promptly upon request.									  *
*																			  *
* The materials  and  information  contained  herein are provided "AS IS" and *
* Vayyar  does  not  provide  any  warranties of any kind, whether express or *
* implied, including but not limited to implied warranties of merchantability,*
* fitness for a particular purpose, and non-infringement.					  *
*																			  *
******************************************************************************/

/** @mainpage Overview of Walabot Application
*
* Walabot is a pocket-sized device that provides cutting-edge technology for Radio Frequency (RF) tridimensional
* (3D) sensing and image processing, enabling sophisticated applications such as:
*
* - Breathing monitoring
* - Object tracking and fall detection
* - In-wall pipe and wire detection
*
* Several sample applications are provided, and Walabot's flexible API enables you to
* create your own applications to access Walabot as a peripheral.
* With Walabot connected via USB and the Walabot SDK installed, your custom application can use Walabot's API to receive various
* types of processed and unprocessed images. The application can then use image data as needed, including 
* performing additional processing such as tracking changes between images to identify movement.
*
* To create your application, first understand what Walabot can do as explained in \subpage _features.
* You can then design high-level application flows according to the \subpage _tasks,
* and implement in code with the functions listed in \subpage _flow. There is also an \subpage _sample that may be of help.
*
* \n\n\n Fill out our 5 question survey \ref _survey
* \n\n\n
\htmlonly
* <iframe width="560" height="315" src="https://www.youtube.com/embed/a2f7mmmdwMg" frameborder="0" allowfullscreen></iframe>
* 
* <iframe width="560" height="315" src="https://www.youtube.com/embed/8PHS0c8JBW8" frameborder="0" allowfullscreen></iframe>
\endhtmlonly
*/



/** @page _features Imaging Features
*
* Walabot can provide your application with several types of imaging data.
* These depend primarily on two types of settings:
* - <b>Scan profile</b>: Defines various scanning details such as the appropriate internal antenna sets and frequencies to use.
* - <b>Get action </b>: Define how the image is processed and what data is provided to the application.
*
* @section _profiles Scan Profiles
*
* The following profiles are available:
* - <b>Short-range</b>: Short-range, penetrative scanning inside dielectric materials such as walls. 
* - Profiles for distance scanning:
*   - <b>Sensor/Tracker</b>: High-resolution images, but slower capture rate.
*   - <b>Sensor narrow</b>: Lower-resolution images for a fast capture rate. Useful for tracking quick movement.
*   
* @section _get Get Actions
*
* The following types of Get actions are available:
* - <b>Raw image</b>: Provides tridimensional (3-D) image data.
* - <b>Raw image slice</b>: Provides bidimensional (2-D) image data (3D image is projected to 2D plane) of the slice where the strongest signal is produced.
* - <b>Image energy</b>: Provides a number representing the sum of all the raw image’s pixels’ signal power.
* - <b>Imaging targets</b> (if the short-range scan profile was used), <b>Sensor targets</b>
* (if one of the sensor scan profiles was used), and <b>Tracker targets</b> (if the tracker scan profile was used): Provide a list of and the number of identified targets
* (in the current API version, Imaging targets provides only the single target with the strongest signal).
* - <b>Raw Signals</b> raw signals as recorded by the sensor. Each signal (<i>i,<i>j) represents the reflected pulse 
* transmitted from antenna <i>i, reflected from the target and received in antenna <i>j.
*
* @section _examples Examples
*
* Here are a few examples of applicative displays based on data provided by various profile / get combinations:
* - Raw image slice of data from short-range scanning:\n
\htmlonly
 <img width="560" height="315" alt="Inwall_raw" src="Inwall_raw.png" ></img>
\endhtmlonly

* - Raw image slice and sensor targets from sensor scanning (Object tracking):\n
\htmlonly
<img width="560" height="315" alt="Sensor" src="Sensor.png" ></img>
\endhtmlonly
* - Imaging target (pipe) from short-range scanning:\n
\htmlonly
<img width="560" height="315" alt="Pipe" src="Pipe.png" ></img>
\endhtmlonly
*
* @section _filtering Dynamic Filtering
*
* For applications that require tracking movement, Walabot can apply a <b>dynamic-imaging filter</b> that removes static signals,
* leaving only changing signals. In addition to the Moving Target Identification (\b MTI) filter,
* the \b Derivative filter is available for the specific frequencies typical of breathing.
* Here’s an example display of Derivative-filtered image energy from sensor-narrow scanning (breathing):
*
\htmlonly
<img width="560" height="315" alt="Breathing" src="Breathing.png" ></img>
\endhtmlonly
*
* @section _calib Calibration and Sensitivity
*
* Walabot \b calibrates scanning to ignore or reduce the signals of fixed reflectors such as walls.
* Additionally, for raw images (3-D and Slice), Walabot removes very weak signals
* according to a configurable <b>sensitivity threshold</b>.
*
* @section _arena Arena
*
* Upon Get actions, Walabot processes and provides image data for a configurable, delimited space known as the \b arena,
* with configurable image resolution. If the triggered scan used the short-range profile,
* the arena size should have similar dimensions as Walabot, and you’ll specify it by Cartesian coordinates
* (ranges and resolution on the x, y, z axes); If one of the Sensor or Tracker profiles was used, the arena is usually much larger and \n
* a Spherical coordinates system is being used (ranges and resolution along radial distance and Theta and Phi angles).
*
* Your application can convert spherical coordinates to Cartesian ones, using the formulae:
* \image html formulae.png
* For example:
* \htmlonly
* <img width="560" height="315" alt="Sensor conversion" src="Sensor_conversion.png" ></img>
* \endhtmlonly


* @section _coordination Coordinate Systems
*
* For arena definitions, and in image data provided by Walabot, Cartesian (X-Y-Z) axes start from Walabot's center as the origin, and their positive directions are: \n\n
\htmlonly
<img width="160" height="280" alt="Walabot card axes" src="Walabot card axes.png" ></img>
\endhtmlonly

\htmlonly
<img width="200" height="280" alt="Walabot axes" src="Walabot's axes.jpg" ></img>
\endhtmlonly

* \n\n When Walabot is in its plastic case, Walabot's bottom as in the above figure is at the USB connector,
* and the side visible in the above figure (the front) faces away from the case's Walabot logo (the logo is in the back).
* For spherical coordinates, radial distance (R) is from Walabot along the Z axis, and polar angle (&Theta;) is from the Z axis.
* \image html "Walabot Polar Coordinate.png"
* Azimuth angle is from the X axis to orthogonal projection on the XY plane.
*
* Units are in centimeters and degrees as relevant.
*
* Now that you understand what Walabot can do,
* you can begin to design high-level application flow according to the \ref _tasks.
* \n\n\n Fill out our 5 question survey \ref _survey
*/


/** @page _tasks Imaging Tasks
*
* Before you begin to design high-level application flows, make sure you understand what Walabot can do as explained in \ref _features. \n
* For an image to be received by the application, the following needs to happen:
* -# \b Connect: Establish communication with Walabot.
* -# \b Configure: Set scan profile and arena; optionally, set a dynamic-imaging filter and/or change the sensitivity threshold.
* -# \b Calibrate: Ignore or reduce the signals of fixed reflectors such as walls according to environment.\n
* Must be performed initially (to avoid delays – preferably before Start), upon any profile change, and is recommended upon possible changes to environment.
* -# \b Start: Start the system in preparation for scanning. Requires a scan profile to have been set.
* -# \b Trigger: Scan (sense) according to profile and record signals to be available for processing and retrieval.\n
* Should be performed before every Get action.
* -# <b>Get action</b>: Process as relevant and provide image data for the current arena,
* according to specified get action, current dynamic-imaging filter (if any), and current sensitivity threshold.\n
* Get actions retrieve the last completed triggered recording, and Walabot automatically makes sure the application
* doesn’t receive the same recording twice (so, you have the option of implementing Trigger and Get action in parallel).
* -# \b Stop and \b Disconnect.
*
* Configuration settings can be changed at any stage, and Walabot makes sure that subsequent Get actions receive data from scans that were triggered after the change.
*
* The scan profile can be changed at any stage, upon which Walabot automatically performs Stop > change profile.
* Upon a profile change, Walabot should be recalibrated and restarted.
*
* Once you've designed high-level application flow according to the above tasks, implement them in code as in \ref _flow.
* \n\n\n Fill out our 5 question survey \ref _survey
*/

/** @page _flow Code Implementation Flow
*
* Before you begin to write code, design high-level application flows according to the \ref _tasks.
* To implement them in an application, follow the below guidelines. There is also a \ref _sample that may help.
* - The application must include references to the API Header file and to the iostream library. For example:\n
*   \code{.C}
*   #include "WalabotApi.h"
*   #include <iostream>
*   \endcode
* - \b General note: Walabot API is not thread safe
* - \b Connect to Walabot: Walabot_ConnectAny()
* - Perform \b configuration (initially, and subsequently as needed) with the following:
*    - Set scan \b profile: Walabot_SetProfile()
*    - For scans that used the short-range profile, set \b arena by Cartesian coordinates (), with arena resolution:
* Walabot_SetArenaX(), Walabot_SetArenaY(), Walabot_SetArenaZ()
*    - For scans that used one of the Sensor or Tracker profiles, set \b arena by spherical coordinates, with arena resolution:
* Walabot_SetArenaR(), Walabot_SetArenaTheta(), Walabot_SetArenaPhi()
*    - If relevant, set a dynamic-imaging \b filter: Walabot_SetDynamicImageFilter()
*    - Optionally, change the sensitivity \b threshold: Walabot_SetThreshold()
* - For each of the above configuration settings (except for profile), you can retrieve the current setting with another function,
* usually named similarly to the above configuration function, with \b get replacing \b set.
* The retrieval functions are referenced in this documentation from the respective setting functions.
* - \b Start (requires profile already set): Walabot_Start()
* - The application loop should usually include at least the following:
*    - \b Trigger: Walabot_Trigger()
*    - <b>Get action</b>: Walabot_GetRawImage(), Walabot_GetRawImageSlice(), Walabot_GetImageEnergy(), Walabot_GetImagingTargets(), Walabot_GetSensorTargets(), Walabot_GetTrackerTargets()
* - \b Calibrate (initially, upon any profile change, and as needed upon possible changes to environment): Walabot_StartCalibration()\n
* To check on the calibration’s progression, use Walabot_GetStatus(), which, if the calibration is still ongoing,
* also provides the percentage completed, which can be used to determine whether to begin scanning or to wait.\n
* You can also stop the calibration: Walabot_CancelCalibration()
* - \b Stop: Walabot_Stop()
* - \b Disconnect: Walabot_Disconnect()
* - At any point you can check Walabot’s \b status: Walabot_GetStatus()
*
* All functions \b return: ::WALABOT_RESULT , which the application should check.
*
* The following advanced functions are also available:
*
* - For connecting to one of multiple Walabots: Walabot_Connect(), Walabot_GetInstrumentsList()
* - For detailed error information: Walabot_GetErrorString()
* - To set the location of Walabot internal database: Walabot_SetSettingsFolder() or Walabot_Initialize()
* - To obtain raw image data from specified antennas: Walabot_GetSignal(), Walabot_GetAntennaPairs()
* \n\n\n Fill out our 5 question survey \ref _survey
*/



/** @page _sample Code Examples
* All sample applications share the coding format: \n
* - <b>Variable</b> definitions -  local variable used during the function \n
* - <b>Initialize configuration</b> - set of variables with predefine value, \n which are used by the Walabot API during Configuration phase.\n
* - <b>Code Sample</b> is divided into 7 steps: \n
1) Connect \n
2) Configure \n
3) Start\n
4) Calibrate  \n
5) Trigger \n
6) Get action \n
7) Stop/Disconnect \n
*
* - <b>Important implementation note:</b> Walabot uses internal Database (DB), these files are located by default \n
* in Windows at : "%ProgramData%/Walabot/WalabotSDK" folder. When you write your own application, there is need to modify Walabot lib \n
* its database location. \ref Walabot_SetSettingsFolder
* -# \b Sensor Sample Code: this example shows how to build up a simple sensor application using Walabot API.
*	There are two modes MTI mode enable/disable, can be set by modifying the \a mtiMode variable. \n
* <b> C# Sample Code </b>
* \include CS_ExampleCode/SensorApp_SampleCode/Program.cs
* <b> C++ Sample Code </b>
* \include cpp/SensorCodeSample.cpp
* <b> Python Sample Code </b>
* \include python/SensorApp.py

* \n
* -# \b Breathing example, setting up a Narrow Sensor profile
* \n<b> C# Sample Code </b>
* \include "CS_ExampleCode/BreathingApp_SampleCode/Program.cs"
* <b> C++ Sample Code </b>
* \include cpp/SensorBreathingSampleCode.cpp
* <b> Pyhton Sample Code </b>
* \include python/BreathingApp.py

* \n
* -# \b InWall application  sensor
* \n<b> C# Sample Code </b>
* \include "CS_ExampleCode/InWallApp_SampleCode\Program.cs"
* <b> C++ Sample Code </b>
* \include \line cpp/InWallSampleCode.cpp
* <b> Python Sample Code </b>
* \include python/InWallApp.py
* \n
* -# \b Tracker example
* <b> C++ Sample Code </b>
* \include cpp/TrackerSampleCode.cpp
* <b> Pyhton Sample Code </b>
* \include python/TrackerApp.py
* \n
* -# \b Tracker example
* <b> Pyhton Sample Code </b>
* \include python/PeopleCounter.py
* \n
* -# <b> Gesture recognition example:</b>
*  This sample code allows you to flip pages of a file (a pdf file, a presentation etc.) using a hand gesture. \n
*  By moving your hand along the Walabots' y axis in a gentle wave fashion, a page would flip forward or backwards. \n
*  After running the code, you need to bring into focus the file which you want to use the app with. \n
*  In order to make the files' paged to flip, The code takes over the "PgUp" and "PgDn" keys of your keyboard. \n
*  If you wish, you can decide which keys should be pressed as the outcome of your hand gesture, by changing the virtual key-codes (in the function PageFlip) \n
*  IMPORTANT NOTE: The hand should cross the origin of the walabot device during its movement.
* \include cpp/FlipPagesSampleCode.cpp
* \n\n\n\b Fill out our 5 question survey \ref _survey
*/


/** @page _install Installation instructions and  Troubleshooting
*
** @section _installationlocation Installation location
* Walabot latest stable installation can be down in the following link : <b>
* <a href="http://www.walabot.com/getting-started"> Walabot Installer </a>
* </b>
* @section _windowsInstall Windows Installation
* @subsection _installationinstructions Installation instructions
* The installation checks if the software is already installed on your computer or ot, it will propose to install it.
* @subsection _installationTroubleshooting Installation Troubleshooting
*
* -#	Walabot SDK installation fails with various errors.\n
* <b>Fix</b> : If the Walabot installation fails it may leave the system in inconsistent state.Try to uninstall the Walabot package and then rerun the installation.
* -#	After installation of the Walabot SDK package the WalabotDemo application complains on missing dlls.\n
* <b>Fix</b>: In rare cases, the installation may require reboot.Please reboot your system and try to run WalabotDemo again.
* -# Driver installtion error - Sometime the driver installation fails. \n
* Pop up window with message: "device driver was not successfully installed" \n
* <b>Fix</b>: reboot the system \n
* Note :The driver problem also could be see in event viewer: Device manager "... with exit code 0xD 0xD = The data is invalid"
*
* @section _linuxInstall Linux Installation
* @subsection _installationlinuxinstructions Installation Linux instructions
* Linux installation is done with debian package.\n
* In order to install, please download th einstallation package from Walabot site, and execute the following command:\n
* \code{.C}
* sudo dpkg -i walabot-maker.deb
* \endcode
*  
* The package installs the following files/paths:\n
* 
* -# /usr/lib/libWalabotAPI.so  - The walabot library.
* -# /usr/include/WalabotAPI.h  - The walabot library header file.
* -# /var/lib/walabot/...       - The walabot database and configuration files. Give this path to Walabot_SetSettingsFolder.
* -# /usr/share/doc/walabot/... - Example code, licence and README
* -# /etc/udev/rules.d/...      - Special udev rule for walabot device, so it could be access without root priviliges.
* 


*/



/** @page _pythonapi Walabot Python API Documentation
*
* The Walabot library now supports Python, with its own Python API module for both Python 2 and 3, and makes it incredibly easy to take your first steps in developing Walabot applications. 
* Importing WalabotAPI
* To use the WalabotAPI module in your Python code, you must import the module.
* You have two options for this: you can install WalabotAPI as a Python package, or you can import the Python file WalabotAPI.py into your specific script, using its file location.
* 
* @section _installingwalabotapi Installing WalabotAPI as a Package
*
* You must have both Python and pip installed.
* @subsection  _onWindows On Windows
* Run the Command Prompt as an Administrator, and enter:
* \code{.C}
* pip install WalabotAPI --no-index --find-links="%PROGRAMFILES%/Walabot/WalabotSDK/python/"
* \endcode
*
* @subsection  _onLinux  On Linux
* You may need to use sudo.
* \code{.C}
* pip install WalabotAPI --no-index --find-links="/usr/share/walabot/python/"
* \endcode
* Once you have installed the package, simply import the package in your Python code using:
* import WalabotAPI
*
* @subsection  _importingwalabotapi Importing WalabotAPI by Location
* It is recommended to use the built-in imp.load_source() to load the module easily.
* @subsection _importingforwindows For Windows
* \code{.C}
* from imp import load_source
* WalabotAPI = load_source(‘WalabotAPI’,
* ‘C:/Program Files/Walabot/WalabotSDK/python/WalabotAPI.py’)
* \endcode
*
* @subsection _importingforlinux For Linux
* \code{.C}
* from imp import load_source
* WalabotAPI = load_source(‘WalabotAPI’,
* ‘/usr/share/walabot/python/WalabotAPI.py’)
* \endcode
* @section _gettingstarter Getting Started
*
* @subsection _moduleinit Module Initialization
* Before using any other Walabot calls, you must call WalabotAPI.Init().
* The Python API is using the ‘low-level’ library for C++ (WalabotAPI.dll on Windows and libWalabotAPI.so on Linux).\n\n
* In order to direct the Python API to the library you need to use the WalabotAPI.Init() function and pass it the path to the library.
* Moving the library file is not recommended. In case you do move it, you can pass Init() the new path to the library, e.g.:
*  \code{.C}
* 	WalabotAPI.Init(“C:/MyCode/MyWalabotProject/WalabotAPI.dll”)
*	\endcode
* @subsection _usingwalabotfunctions Using Walabot Functions
* Every function in the C++ API has a corresponding function in the Python API module which is designed to match the Python language flow.
* It is advised to look at the Python examples to fully understand how to use them. A detailed documentation about all available functions is given below, and can also be found using Python’s help() function.
*
* @subsection _callingfunctions Calling functions example
* As an example, the original Walabot_GetStatus() function which is implemented as such in the C++ example code:
* \code{.C}
* res = Walabot_GetStatus(&appStatus, &calibrationProcess);
* \endcode
* Should be written in Python as such:
* \code{.C}
* appStatus, calibrationProcess = WalabotAPI.GetStatus()
* \endcode
* @subsection _handlingexception Handling Exceptions
* Unlike the C++ functions, the functions in Python does not return WALABOT_RESULT.
* The Python module will raise WalabotError in case it encounters one. You can catch those errors and act accordingly.
* @subsection _walaboterror WalabotResult fields
* code: WALABOT_SUCCESS for success, WALABOT_ERROR for error. \n
* error string: A short description of the occurred error. Call Walabot_GetErrorString() to get it after getting a WALABOT_ERROR as a return value.
* @subsection _debugexample Debugging Example
* The following example can be used in order to test that there is a connected Walabot:
* \code{.C}
*	 try:
*		WalabotAPI.ConnectAny()
*	 except WalabotAPI.WalabotError:
*		print(Walabot_GetErrorString())
* \endcode


* @subsection _moduleconst Module ‘Constants’
* The C++ enums are available as simply ‘constants’ variables and are corresponding to them.
* For example: PROF_SENSOR is accessible in Python simply as WalabotAPI.PROF_SENSOR.
* Available ‘Constants’
* - For APP_PROFILE:
* - PROF_SHORT_RANGE_IMAGING
* - PROF_SENSOR
* - PROF_SENSOR_NARROW
* - PROF_TRACKER
* - For APP_STATUS:
* - STATUS_CLEAN
* - STATUS_INITIALIZED
* - STATUS_CONNECTED
* - STATUS_CONFIGURED
* - STATUS_SCANNING
* - STATUS_CALIBRATING
* - STATUS_CALIBRATING_NO_MOVEMENT	
* - For FILTER_TYPE:
* - FILTER_TYPE_NONE
* - FILTER_TYPE_DERIVATIVE
* - FILTER_TYPE_MTI
* - For TARGET_TYPE:
* - TARGET_TYPE_UNKNOWN
* - TARGET_TYPE_PIPE
* - TARGET_TYPE_STUD
* - TARGET_TYPE_STUD90
* - TARGET_TYPE_STUD_METAL
* - TARGET_TYPE_OTHER \n
* Custom Types \n
* The Python API implements the original C++ structs as namedtuples.\n
* Available Types \n
* AntennaPair: \n
* - (int)			txAntenna
* - (int)			rxAntenna \n
* ImagingTarget
* - (TARGET_TYPE)	type
* - (double)		angleDeg
* - (double)		xPosCm
* - (double)		yPosCm
* - (double)		zPosCm
* - (double)		widthCm
* - (double)		amplitude \n 
* SensorTarget
* - (double)		xPosCm
* - (double)		yPosCm
* - (double)		zPosCm
* - (double)		amplitude \n
* Custom Types Example \n 
* WalabotAPI.GetImagingTargets() function returns a list of ImagingTarget type. \n
* You can access the width of the first element in this list with targets[0].widthCm. \n
* Example Code: InWallApp
* \code{.C}
* from __future__ import print_function # WalabotAPI works on both Python 2 and 3.
* from sys import platform
* from os import system
* from imp import load_source
* WalabotAPI = load_source('WalabotAPI',
*     'C:/Program Files/Walabot/WalabotSDK/bin/Win32/WalabotAPI.py')
* WalabotAPI.Init()
* 
* def PrintSensorTargets(targets):
*     system('cls' if platform == 'win32' else 'clear')
*     if targets:
*         for i, target in enumerate(targets):
*             print (('Target #{}:\ntype: {}\nangleDeg: {}\nx: {}\ny: {}\nz: {}'+
*                 '\nwidth: {}\namplitude: {}\n').format(i + 1, target.type,
*                 target.angleDeg, target.xPosCm, target.yPosCm, target.zPosCm,
*                 target.widthCm, target.amplitude))
*     else:
*         print ('No Target Detected')
* 
* def InWallApp():
*     # WalabotAPI.SetArenaX - input parameters
*     xArenaMin, xArenaMax, xArenaRes = -3, 4, 0.5
*     # WalabotAPI.SetArenaY - input parameters
*     yArenaMin, yArenaMax, yArenaRes = -6, 4, 0.5
*     # WalabotAPI.SetArenaZ - input parameters
*     zArenaMin, zArenaMax, zArenaRes = 3, 8, 0.5
*     # Configure Walabot database install location (for windows)
*     WalabotAPI.SetSettingsFolder()
*     # 1) Connect: Establish communication with walabot.
*     WalabotAPI.ConnectAny()
*     # 2) Configure: Set scan profile and arena
*     # Set Profile - to Short-range.
*     WalabotAPI.SetProfile(WalabotAPI.PROF_SHORT_RANGE_IMAGING)
*     # Set arena by Cartesian coordinates, with arena resolution
*     WalabotAPI.SetArenaX(xArenaMin, xArenaMax, xArenaRes)
*     WalabotAPI.SetArenaY(yArenaMin, yArenaMax, yArenaRes)
*     WalabotAPI.SetArenaZ(zArenaMin, zArenaMax, zArenaRes)
*     # Walabot filtering disable
*     WalabotAPI.SetDynamicImageFilter(WalabotAPI.FILTER_TYPE_NONE)
*     # 3) Start: Start the system in preparation for scanning.
*     WalabotAPI.Start()
*     # calibrates scanning to ignore or reduce the signals
*     WalabotAPI.StartCalibration()
*     while True:
*         appStatus, calibrationProcess = WalabotAPI.GetStatus()
*         # 5) Trigger: Scan (sense) according to profile and record signals
*         # to be available for processing and retrieval.
*         WalabotAPI.Trigger()
*         # 6) Get action: retrieve the last completed triggered recording
*         targets = WalabotAPI.GetImagingTargets()
*         rasterImage, sliceDepth, power = WalabotAPI.GetRawImageSlice()
*         # print targets found
*         PrintSensorTargets(targets)
*     # 7) Stop and Disconnect.
*     WalabotAPI.Stop()
*     WalabotAPI.Disconnect()
*     print ('Terminate successfully')
* 
* if __name__ == '__main__':
*     InWallApp()
* \endcode


*/



/** @page _project Building your own project 
* 
* @section _overview  Overview
* Walabot library supports a variety of platforms: 
* -# windows c++,c#. 
* -# linux : c++
* 
* Under  the example folder you can find 
*
*
* @section _windows Building project for Windows
* You can build you own visual studio project (see below), or use a template version. This project can be found in the walabot folder under example folder.
* Walabot Installer install the libraries in the following folder: "C:\Program Files\Walabot\WalabotSDK\bin" \n																	
* <b>Building Application using visual studio 2015 C++</b> 
* For C++ project you need to use the following libraries: \n
* -#	WalabotAPI.dll
* -#	WalabotAPI.lib 
* -#	Qt5Core.dll
* -#	libusb-1.0.dll
* 
* <b>Flow</b>: 
* If you don't have CMake installed, please download it from: https://cmake.org/download/
* -# Open CMake gui \n
* \htmlonly
* <img width="450" height="480" src="ProjectSlide1.png" ></img>
* \endhtmlonly
*
* -# Press "Browse Source" and choose "C:\Program Files\Walabot\WalabotSDK\example\c++" \n
* \htmlonly
* <img width="450" height="480" src="ProjectSlide2a.png" ></img>
* \endhtmlonly
* 
* -# Press "Browse Build" and choose a destination directory for your built project, for example: "C:\Temp\MyProject" \n
* \htmlonly
* <img width="450" height="480" src="ProjectSlide4.png" ></img>
* \endhtmlonly
*
* -# Press "Configure", select the relevant version of Visual Studio, and press "Finish" \n
* \htmlonly
* <img width="450" height="480" src="ProjectSlide5.png" ></img>
* \endhtmlonly
*
* -# The following should appear: \n
* \htmlonly
* <img width="450" height="480" src="ProjectSlide7.png" ></img>
* \endhtmlonly
*
* -# Press "Generate" and a generated solution with the compiled example codes will be in the selected folder from step 3.\n
* * @section _linux Building Application for Linux
* Go to the examples directory, and run the script buildAll.sh:
* \code{.C}
* cd /usr/share/doc/walabot/examples 
* ./buildAll.sh
* \endcode
* That will build all the examples into binaries which you can run (Of course, don't forget to connect the Walabot device before running them!)\n
* <b>Note:</b> If you have older g++ version, you will probably have to edit the buildAll.sh script to add c++11 support.
*	
*/

/** @page _headerfile Walabot Header file
* Walabot library contains one header file WalabotApi.h \n
* This file includes all the API functions.
*/

/** @page _video  How-To-Video
*
* \htmlonly
* <iframe width="560" height="315" src="https://www.youtube.com/embed/a2f7mmmdwMg" frameborder="0" allowfullscreen></iframe>
* 
* <iframe width="560" height="315" src="https://www.youtube.com/embed/8PHS0c8JBW8" frameborder="0" allowfullscreen></iframe>
* \endhtmlonly
*
*/

/** @page _survey   Share Your API Feedback
* 
* \htmlonly
* <iframe width="700" height="2500" src="https://www.surveymonkey.com/r/FLYHC9M" frameborder="0" allowfullscreen></iframe>
* \endhtmlonly
*/

typedef enum WALABOT_RESULT_ENUM
{
	WALABOT_SUCCESS,								//!< Operation successful
	WALABOT_ERROR							//!< A general error occurred. Inspect the error logs for more information
}WALABOT_RESULT;

typedef struct vcomplex_struct //! Phasor is a complex number which includes the data on the amplitude and the phase of the reflected signal.
{
	double real; //!< Phasor real component
	double imag; //!< Phasor imaginary component
}vcomplex;

typedef struct AntennaPair_struct //! Antenna pair for Walabot_GetAntennaPairs()
{
	int txAntenna; //!< Transmitting antenna
	int rxAntenna; //!< Receiving antenna
}AntennaPair;

enum APP_PROFILE //!< Scan profile for Walabot_SetProfile(); see \ref _features
{
	PROF_SHORT_RANGE_IMAGING = 0x00010000,	//!< Short-range, penetrative scanning in dielectric materials. Only available for Walabot Developer.
	PROF_SHORT_RANGE_SINGLE_LINE,			//!< Short-range, small number of antennas pairs - This profile currently not in use
	PROF_KNOCK_KNOCK,						//!< This profile currently not in use

	PROF_SENSOR = 0x00020000,				//!< Distance scanning through air; high-resolution images, but slower capture rate
	PROF_SENSOR_NARROW,						//!< Distance scanning through air; lower-resolution images for a fast capture rate, useful for tracking quick movement
	PROF_TRACKER = 0x00030000,
	PROF_WIDE_BAND = 0x00040000

};

enum APP_STATUS //!< Walabot status returned by Walabot_GetStatus()
{
	STATUS_CLEAN,
	STATUS_INITIALIZED, //!< No communication with Walabot
	STATUS_CONNECTED,	//!< Communication established with Walabot, but no Profile set
	STATUS_CONFIGURED,	//!< Profile set, but not currently scanning or calibrating
	STATUS_SCANNING,	//!< Prepared for scanning by Walabot_Start, and not currently calibrating
	STATUS_CALIBRATING,	//!< Now calibrating; in this case Walabot_GetStatus() also provides percentage completed
	STATUS_CALIBRATING_NO_MOVEMENT	//!< TODO: doc
};

enum TARGET_TYPE
{
	TARGET_TYPE_UNKNOWN,
	TARGET_TYPE_PIPE,
	TARGET_TYPE_STUD,
	TARGET_TYPE_STUD90,
	TARGET_TYPE_STUD_METAL,
	TARGET_TYPE_OTHER
};

enum FILTER_TYPE  //!< Dynamic-imaging filter algorithm for Walabot_SetDynamicImageFilter()
{
	FILTER_TYPE_NONE, 		//!< Default, no filtering
	FILTER_TYPE_DERIVATIVE, //!<  Dynamic-imaging filter for the specific frequencies typical of breathing
	FILTER_TYPE_MTI 		//!< Moving Target Identification: standard dynamic-imaging filter: 
};

typedef struct ImagingTarget_struct //!< Imaging Tagret parameters
{
	TARGET_TYPE		type;		//!< Estimated identity of target
	double			angleDeg;	//!< Angle of pipe relative to Y axis
	double			xPosCm; 	//!< X coordinate of target center
	double			yPosCm; 	//!< Y coordinate of target center
	double			zPosCm;		//!< Z coordinate of target center
	double			widthCm;	//!< Reserved for future use
	double			amplitude;	//!< Strongest signal returned from target
}ImagingTarget;


typedef struct SensorTarget_struct //!< Sensor Tagret parameters
{
	double			xPosCm;     //!< X coordinate of target center
	double			yPosCm; 	//!< Y coordinate of target center
	double			zPosCm;		//!< Z coordinate of target center
	double			amplitude;  //!< Strongest signal returned from target
}SensorTarget;


typedef struct TrackerTarget_struct //!< Tracker Tagret parameters
{
	double			xPosCm;     //!< X coordinate of target center
	double			yPosCm; 	//!< Y coordinate of target center
	double			zPosCm;		//!< Z coordinate of target center
	double			amplitude;  //!< Strongest signal returned from target
}TrackerTarget;


#ifdef _WIN32
	#ifdef WALABOT_EXPORTS
	#define WALABOT_API __declspec(dllexport) 
	#else
	#define WALABOT_API __declspec(dllimport)
	#endif
#else
	#define WALABOT_API
#endif


extern "C" {

WALABOT_API WALABOT_RESULT Walabot_Initialize(const char* configFilename);
WALABOT_API WALABOT_RESULT Walabot_Clean();

/**
* @brief Obtains more error information for Vayyar support.
*
* @return ::WALABOT_RESULT
*/
WALABOT_API int Walabot_GetExtendedError();

/**
* @brief Obtains the detailed string of the last error.
*
* @return ::const char*
*/
WALABOT_API const char* Walabot_GetErrorString();

/**
* @brief Obtains Sets location of Walabot internal database, if moved from default.
*
* \param[in] folder Database location
* @return ::WALABOT_RESULT
*/
WALABOT_API WALABOT_RESULT Walabot_SetSettingsFolder(char* folder);

/**
* @brief <b>This function is reserved for future use</b> \n Obtains a list of connected Walabots. 
*	
* For use before Walabot_Connect(); a Walabot ID obtained here is used to identify the device to connect to.\n
* Input details of a memory buffer (size and location) to which Walabot will copy the list of connected Walabot IDs.
* 
* \param[in] bufMaxSize Available size of the provided memory buffer
* \param[in] outputBuffer Location  of the provided memory buffer
* @return ::WALABOT_RESULT
* @sa \ref _flow\n Walabot_Connect
*/
WALABOT_API WALABOT_RESULT Walabot_GetInstrumentsList(int bufMaxSize, char* outputBuffer);

/**
* @brief <b>This function is reserved for future use</b> \n Establishes communication with a specified Walabot device.
*
* Connection is required before Walabot_Start().\n
* If only a single Walabot device is present, it is simpler to use Walabot_ConnectAny().
*
* \param[in] uid Walabot device ID obtained from Walabot_GetInstrumentsList()
* @return ::WALABOT_RESULT
* @sa Walabot_ConnectAny
*/
WALABOT_API WALABOT_RESULT Walabot_Connect(char* uid);

/**
* @brief Establishes communication with Walabot.
*
* Connection is required before Walabot_Start().\n
* If multiple Walabots are present, a single available Walabot is selected; to specify one, use Walabot_Connect().
*
* @return ::WALABOT_RESULT
* @sa \ref _flow\n Walabot_Connect\n Walabot_Disconnect
*/
WALABOT_API WALABOT_RESULT Walabot_ConnectAny();

/**
* @brief Stops communication with Walabot.
*	
* @return ::WALABOT_RESULT
* @sa Walabot_Connect\n Walabot_Disconnect
*/
WALABOT_API WALABOT_RESULT Walabot_Disconnect();

/**
* @brief Starts Walabot in preparation for scanning. 
*
* Requires previous Connect (Walabot_ConnectAny() or Walabot_Connect() ) and Walabot_SetProfile().\n
* Required before Walabot_Trigger() and GET actions.
* 
* @return ::WALABOT_RESULT
* @sa \ref _flow\n Walabot_Stop
*/
WALABOT_API WALABOT_RESULT Walabot_Start();

/**
* @brief Stops Walabot when finished scanning. 
*
* @return ::WALABOT_RESULT
* @sa \ref _flow\n Walabot_Start
*/
WALABOT_API WALABOT_RESULT Walabot_Stop();

/**
* @brief Initiates a scan and records signals.
*
* Initiates a scan according to profile and records signals to be available for processing and retrieval.\n
* Should be performed before every GET action.
*
* @return ::WALABOT_RESULT
* @sa \ref _flow
*/
WALABOT_API WALABOT_RESULT Walabot_Trigger();

/**
* @brief Obtains a list of Walabot antenna pairs.
*	
* For use before Walabot_GetSignal(). To identify the antennas on your Walabot device, see the specifications for your model.
* 
* \param[out] antennaPairs List of antenna pairs
* \param[out] numPairs The number of antenna pairs in the list
* @return ::WALABOT_RESULT
* @sa Walabot_GetSignal
*/
WALABOT_API WALABOT_RESULT Walabot_GetAntennaPairs(AntennaPair** antennaPairs, int* numPairs);

/**
* @brief Obtains raw signals data from specified antennas. CURRENTLY NOT SUPPORTED FOR TRACKER PROFILE.
*
* \param[in] txAntenna Transmitting antenna ID as obtained from Walabot_GetAntennaPairs()
* \param[in] rxAntenna Receiving antenna ID as obtained from Walabot_GetAntennaPairs()
* \param[out] signal List of amplitude values representing received signal amplitude in time domain
* \param[out] timeAxis time axis ticks values
* \param[out] numSamples Number of sample in the list
* @return ::WALABOT_RESULT
* @sa Walabot_GetAntennaPairs
*/
WALABOT_API WALABOT_RESULT Walabot_GetSignal(int txAntenna, int rxAntenna, double** signal, double** timeAxis, int* numSamples);

/**
* @brief Sets scan profile.
*
* For an explanation of available profiles, see \ref _features.
* \param[in] profile The scan profile to use
* @return ::WALABOT_RESULT
* @sa \ref _flow
*/
WALABOT_API WALABOT_RESULT Walabot_SetProfile(APP_PROFILE profile);

/**
* @brief Obtains Walabot status.
*
* For an explanation of possible statuses, see ::APP_STATUS.
* \param[out] status Walabot's status
* \param[out] param Percentage of calibration completed, if status is STATUS_CALIBRATING
* @return ::WALABOT_RESULT
* @sa \ref _flow
*/
WALABOT_API WALABOT_RESULT Walabot_GetStatus(APP_STATUS* status, double* param);

/**
* @brief Initiates calibration.
*	
* Ignores or reduces the signals of fixed reflectors such as walls according to environment.\n
* Must be performed initially (to avoid delays – preferably before Walabot_Start()), upon any profile change,
* and is recommended upon possible changes to environment.\n
* Calibration is done via recording and processing. So after calling StartCalibration, 
*   a continues trigger & GetImage/GetTargets function calls is required. 
* To check on calibration progress, use Walabot_GetStatus().
* @return ::WALABOT_RESULT
* @sa \ref _flow\n Walabot_GetStatus\n Walabot_CancelCalibration
*/
WALABOT_API WALABOT_RESULT Walabot_StartCalibration();

/**
* @brief Stops calibration.
*
* To check on calibration progress, use Walabot_GetStatus().
* @return ::WALABOT_RESULT
* @sa \ref _flow\n Walabot_GetStatus\n Walabot_StartCalibration
*/
WALABOT_API WALABOT_RESULT Walabot_CancelCalibration();

/**
* @brief Changes the sensitivity threshold.
*	
* For raw images (3-D and Slice), Walabot removes very weak signals, below this threshold. If the threshold is not set, a default value is used.\n
* For tracker profile, this threshold also controls the targets shown based on the accumulated power.
* To check the current value, use Walabot_GetThreshold().
* \param[in] value The threshold to set
* @return ::WALABOT_RESULT
* @sa \ref _flow
*/
WALABOT_API WALABOT_RESULT Walabot_SetThreshold(double value);	

WALABOT_API WALABOT_RESULT Walabot_SetTrackerAquisitionThreshold(double value);
/**
* @brief Obtains the current sensitivity threshold.
*	
* To set the threshold, use Walabot_SetThreshold().
* \param[out] threshold The current threshold value
* @return ::WALABOT_RESULT
* @sa \ref _flow
*/
WALABOT_API WALABOT_RESULT Walabot_GetThreshold(double* threshold);

/**
* @brief Sets X-axis range and resolution of arena.
*	
* For coordinate directions, see \ref _coordination.\n
* To check the current value, use Walabot_GetArenaX().\n
* \b Note: Cartesian (X-Y-Z) coordinates should be used only to get image data from a triggered scan that used the short-range profile.
* Otherwise use the Walabot_SetArena functions for spherical (r-&Theta;-&Phi;) coordinates.
* \param[in] min Beginning of range on axis (cm)
* \param[in] max End of range on axis (cm)
* \param[in] res Distance between pixels along axis (cm)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_SetArenaY\n Walabot_SetArenaZ
*/
WALABOT_API WALABOT_RESULT Walabot_SetArenaX(double min, double max, double res);

/**
* @brief Sets Y-axis range and resolution of arena.
*	
* For coordinate directions, see \ref _coordination.\n
* To check the current value, use Walabot_GetArenaY().\n
* \b Note: Cartesian (X-Y-Z) coordinates should be used only to get image data from a triggered scan that used the short-range profile.
* Otherwise use the Walabot_SetArena functions for spherical (r-&Theta;-&Phi;) coordinates.
* \param[in] min Beginning of range on axis (cm)
* \param[in] max End of range on axis (cm)
* \param[in] res Distance between pixels along axis (cm)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_SetArenaX\n Walabot_SetArenaZ
*/
WALABOT_API WALABOT_RESULT Walabot_SetArenaY(double min, double max, double res);

/**
* @brief Sets Z-axis range and resolution of arena.
*	
* For coordinate directions, see \ref _coordination.\n
* To check the current value, use Walabot_GetArenaZ().\n
* \b Note: Cartesian (X-Y-Z) coordinates should be used only to get image data from a triggered scan that used the short-range profile.
* Otherwise use the Walabot_SetArena functions for spherical (r-&Theta;-&Phi;) coordinates.
* \param[in] start Beginning of range on axis (cm)
* \param[in] end End of range on axis (cm)
* \param[in] res Distance between pixels along axis (cm)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_SetArenaX\n Walabot_SetArenaY
*/
WALABOT_API WALABOT_RESULT Walabot_SetArenaZ(double start, double end, double res);

/**
* @brief Sets radial (r) range and resolution of arena.
*	
* For coordinate directions, see \ref _coordination.\n
* To check the current value, use Walabot_GetArenaR().\n
* Spherical (r-&Theta;-&Phi;) coordinates should be used only to get image data from a triggered scan that used one of the Sensor profiles.
* Otherwise use the Walabot_SetArena functions for cartesian (X-Y-Z) coordinates.
* \param[in] start Beginning of radial distance range (cm)
* \param[in] end End of radial distance range (cm)
* \param[in] res Distance between pixels along radius (cm)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_SetArenaTheta\n Walabot_SetArenaPhi
*/
WALABOT_API WALABOT_RESULT Walabot_SetArenaR(double start, double end, double res);

/**
* @brief Sets polar (&Theta;) range and resolution of arena.
*
* For coordinate directions, see \ref _coordination.\n
* To check the current value, use Walabot_GetArenaTheta().\n
* Spherical (r-&Theta;-&Phi;) coordinates should be used only to get image data from a triggered scan that used one of the Sensor profiles.
* Otherwise use the Walabot_SetArena functions for cartesian (X-Y-Z) coordinates.
* \param[in] min start Beginning of polar angular range (degrees)
* \param[in] max end End of polar angular range (degrees)
* \param[in] res Angle between pixels across polar angle (degrees)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_SetArenaR\n Walabot_SetArenaPhi
*/
WALABOT_API WALABOT_RESULT Walabot_SetArenaTheta(double min, double max, double res);

/**
* @brief Sets azimuth (&Phi;) range and resolution of arena.
*	
* For coordinate directions, see \ref _coordination.\n
* To check the current value, use Walabot_GetArenaPhi().\n
* Spherical (r-&Theta;-&Phi;) coordinates should be used only to get image data from a triggered scan that used one of the Sensor profiles.
* Otherwise use the Walabot_SetArena functions for cartesian (X-Y-Z) coordinates.
* \param[in] min Beginning of azimuth angular range (degrees)
* \param[in] max End of azimuth angular range (degrees)
* \param[in] res Angle between pixels across polar angle (degrees)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_SetArenaR\n Walabot_SetArenaTheta
*/
WALABOT_API WALABOT_RESULT Walabot_SetArenaPhi(double min, double max, double res);

/**
* @brief Obtains current X-axis range and resolution of arena.
*	
* Can be changed with Walabot_SetArenaX().\n
* For coordinate directions, see \ref _coordination.\n
* Cartesian (X-Y-Z) coordinates are relevant only to get image data from a triggered scan that used the short-range profile.
* Otherwise the Walabot_SetArena functions for spherical (r-&Theta;-&Phi;) coordinates apply.
* \param[out] min Beginning of range on axis (cm)
* \param[out] max End of range on axis (cm)
* \param[out] res Distance between pixels along axis (cm)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_SetArenaX
*/
WALABOT_API WALABOT_RESULT Walabot_GetArenaX(double* min, double* max, double* res);

/**
* @brief Obtains current Z-axis range and resolution of arena.
*	
* Can be changed with Walabot_SetArenaZ().\n
* For coordinate directions, see \ref _coordination.\n
* Cartesian (X-Y-Z) coordinates are relevant only to get image data from a triggered scan that used the short-range profile.
* Otherwise the Walabot_SetArena functions for spherical (r-&Theta;-&Phi;) coordinates apply.
* \param[out] start Beginning of range on axis (cm)
* \param[out] end End of range on axis (cm)
* \param[out] res Distance between pixels along axis (cm)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_SetArenaZ
*/
WALABOT_API WALABOT_RESULT Walabot_GetArenaZ(double* start, double* end, double* res);

/**
* @brief Obtains current Y-axis range and resolution of arena.
*
* Can be changed with Walabot_SetArenaY().\n
* For coordinate directions, see \ref _coordination.\n
* Cartesian (X-Y-Z) coordinates are relevant only to get image data from a triggered scan that used the short-range profile.
* Otherwise the Walabot_SetArena functions for spherical (r-&Theta;-&Phi;) coordinates apply.
* \param[out] min Beginning of range on axis (cm)
* \param[out] max End of range on axis (cm)
* \param[out] res Distance between pixels along axis (cm)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_SetArenaY
*/
WALABOT_API WALABOT_RESULT Walabot_GetArenaY(double* min, double* max, double* res);

/**
* @brief Obtains radial (r) range and resolution of arena.
*	
* Can be changed with Walabot_SetArenaR().\n
* For coordinate directions, see \ref _coordination.\n
* Spherical (r-&Theta;-&Phi;) coordinates are relevant only to get image data from a triggered scan that used one of the Sensor profiles.
* Otherwise the Walabot_SetArena functions for cartesian (X-Y-Z) coordinates apply.
* \param[out] start Beginning of radial distance range (cm)
* \param[out] end End of radial distance range (cm)
* \param[out] res Image resolution along radius (cm)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_SetArenaR
*/
WALABOT_API WALABOT_RESULT Walabot_GetArenaR(double* start, double* end, double* res);

/**
* @brief Obtains polar (&Theta;) range and resolution of arena.
*	
* Can be changed with Walabot_SetArenaTheta().\n
* For coordinate directions, see \ref _coordination.\n
* Spherical (r-&Theta;-&Phi;) coordinates are relevant only to get image data from a triggered scan that used one of the Sensor profiles.
* Otherwise the Walabot_SetArena functions for cartesian (X-Y-Z) coordinates apply.
* \param[in] min Beginning of polar angular range (degrees)
* \param[in] max End of polar angular range (degrees)
* \param[in] res Angle between pixels across polar angle (degrees)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_SetArenaTheta
*/
WALABOT_API WALABOT_RESULT Walabot_GetArenaTheta(double* min, double* max, double* res);

/**
* @brief Obtains azimuth (&Phi;) range and resolution of arena.
*	
* Can be changed with Walabot_SetArenaPhi().\n
* For coordinate directions, see \ref _coordination.\n
* Spherical (r-&Theta;-&Phi;) coordinates are relevant only to get image data from a triggered scan that used one of the Sensor profiles.
* Otherwise the Walabot_SetArena functions for cartesian (X-Y-Z) coordinates apply.
* \param[in] min Beginning of azimuth angular range (degrees)
* \param[in] max End of azimuth angular range (degrees)
* \param[in] res Angle between pixels across polar angle (degrees)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_SetArenaPhi
*/
WALABOT_API WALABOT_RESULT Walabot_GetArenaPhi(double* min, double* max, double* res);

/**
* @brief Provides bidimensional (2-D) image data of the 3D image projected to a plane.
*
* Image data is a 2-dimensional projection matrix of the 3D Raw image which can be obtained using Walabot_GetRawImage function.\n
* In this 2D matrix element represents the reflection strength at spatial location corresponding to this element indexing in the matrix. \n
* The projection is done according to the profile used. For sensor profile, the projection is to Phi-R (polar coordinates) plane, \n
* while for short-range sensor, the projection is to X-Y plane (carthesian coordinates). 
* One can always use the original 3D raw data to create other planes of interests. \n
* The value of the element indicated the reflected power measured in its  location. \n
* The matrix is transferred using a vector which is the concatenated matrix rows. meaning; assuming 2D matrix with indexes i, j.\n 
* The vector is represented as followed:\n
* \code{.C}
* // 2D index is represnted is the following schema {i,j}
* //	sizeX -  represnts the i dimension length
* //	sizeY -  represnts the j dimension length
* // img3d - represtes the walabot 2D scanned image (internal data)
* int index = (sizeX * ((k * sizeY) + j)) + i;
* double normalized_abs_val = abs( img3d[i][j] ); // normalized_abs_val is between 0 to 1
* rasterImage[index] = (int)(normalized_abs_val * 255);
* \endcode
* Each index represent the location alone it's axis according to the arena defined. E.g.: \n
* For Carthesian coordinates Arena ( see \ref Walabot_SetArenaX(), Walabot_SetArenaY()). \n E.g.: \n
* \code{.C}
* x = xMin + i * (xMax-xMin) / (sizeX-1);
* y = yMin + j *(yMax-yMin) / (sizeY-1);
* \endcode
* For Polar coordinates Arena ( see \ref Walabot_SetArenaR(), Walabot_SetArenaPhi()). \n E.g.: \n
* \code{.C}
* Phi = phiMin + i *(phiMax-phiMin) / (sizeX-1);
* R = RMin + j *(RMax-RMin) / (sizeY-1);
* \endcode
*
* Requires previous Walabot_Trigger(); provides data based on last completed triggered image.\n
* Output is details of array variable populated by provided image data.\n
* 
* Provided image data is dependent on current configured arena and on current configuration from Walabot_SetDynamicImageFilter() and Walabot_SetThreshold().
* \param[out] rasterImage Name of array variable populated by output image data
* \param[out] sizeX Dimension of array variable populated by output image data
* \param[out] sizeY Dimension of array variable populated by output image data
* \param[out] sliceDepth third dimension coordinate of maximum target power
* \param[out] power Peak measured power in arena (value of strongest pixel)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow Walabot_Trigger\n Walabot_GetRawImage
*/
WALABOT_API WALABOT_RESULT Walabot_GetRawImageSlice(int** rasterImage, int* sizeX, int* sizeY, double* sliceDepth, double* power);

/**
* @brief Provides tridimensional (3-D) image data.
*
* Image data is a 3-dimensional matrix in which each element represents the reflected power at (x,y,z) spatial location corresponding to this element indexing in the matrix.\n
* The coordinates are according to the profile used. For sensor profile, the coordinates are Theta-Phi-R (polar coordinates) , \n
* while for short-range sensor, the coordinates are to X-Y-Z plane (carthesian coordinates).
* The matrix is transferred using a vector which is the concatenated matrix rows. \n
* Meaning; assuming 3D matrix with indexes i, j & k. the vector is represented as followed:\n
* \code{.C}
* // 3D index is represnted is the following schema {i,j,k}
* //	sizeX -  represnts the i dimension length
* //	sizeY -  represnts the j dimension length
* //	sizeZ -  represnts the k dimension length
* // img3d - represtes the walabot 3D scanned image (internal data)
* int index = (sizeX * ((k * sizeY) + j)) + i;
* double normalized_abs_val = abs( img3d[i][j][k] ); // normalized_abs_val is between 0 to 1 
* rasterImage[index] = (int)(normalized_abs_val * 255);
* \endcode
* 
* Each index represent the location alone it's axis according to the arena defined.\n
* For Carthesian coordinates Arena ( see \ref Walabot_SetArenaX(), Walabot_SetArenaY(), Walabot_SetArenaZ()). \n E.g.: \n
* \code{.C}
* x = xMin + i * (xMax-xMin) / (sizeX-1);
* y = yMin + j *(yMax-yMin) / (sizeY-1); 
* z = zMin + k *(zMax-zMin) / (sizeZ-1);
* \endcode
* For Polar coordinates Arena ( see \ref Walabot_SetArenaR(), Walabot_SetArenaTheta(), Walabot_SetArenaPhi()). \n E.g.: \n
* \code{.C}
* Theta = thetaMin + i * (thetaMax-thetaMin) / (sizeX-1);
* Phi = phiMin + j *(phiMax-phiMin) / (sizeY-1);
* R = RMin + k *(RMax-RMin) / (sizeZ-1);
* \endcode
* Requires previous Walabot_Trigger(); provides data based on last completed triggered image.\n
* Output is details of array variable populated by provided image data.\n
* Provided image data is dependent on current configured arena and on current configuration from Walabot_SetDynamicImageFilter() and Walabot_SetThreshold().
* \param[out] rasterImage Name of array variable populated by output image data
* \param[out] sizeX Dimension of array variable populated by output image data
* \param[out] sizeY Dimension of array variable populated by output image data
* \param[out] sizeZ Dimension of array variable populated by output image data
* \param[out] power Peak measured power in arena (value of strongest pixel)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow Walabot_Trigger\n Walabot_GetRawImageSlice
*/
WALABOT_API WALABOT_RESULT Walabot_GetRawImage(int** rasterImage, int* sizeX, int* sizeY, int* sizeZ, double* power);

/**
* @brief Provides the sum of all the raw image’s pixels’ signal power.
*	
* Requires previous Walabot_Trigger(); provides data based on last completed triggered image.\n
* Provided image data is dependent on current configured arena.
* \param[out] energy Number representing the sum of all the raw image’s pixels’ signal power
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow Walabot_Trigger
*/
WALABOT_API WALABOT_RESULT Walabot_GetImageEnergy(double* energy);

/**
* @brief Provides a list of and the number of identified targets.
*	
* Available only if the short-range scan profile was used.\n
* Requires previous Walabot_Trigger(); provides data based on last completed triggered image.\n
* Provided image data is dependent on current configured arena and on current configuration from Walabot_SetDynamicImageFilter() and Walabot_SetThreshold().
* \b Note: In the current API version, provides only the single target with the strongest signal, in format appropriate for pipe
* \param[out] targets List of identified targets (in current API version, a single target)
* \param[out] numTargets Number of identified targets (in current API version, 1)
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow Walabot_Trigger\n Walabot_GetSensorTargets
*/
WALABOT_API WALABOT_RESULT Walabot_GetImagingTargets(ImagingTarget** targets, int* numTargets);

/**
* @brief Provides a list of and the number of identified targets.
*
* Available only if one of the Sensor scan profiles was used.\n
* Requires previous Walabot_Trigger(); provides data based on last completed triggered image.\n
* Provided image data is dependent on current configured arena and on current configuration from Walabot_SetDynamicImageFilter() and Walabot_SetThreshold().
* \param[out] targets List of identified targets
* \param[out] numTargets Number of identified targets
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow Walabot_Trigger\n Walabot_GetImagingTargets
*/
WALABOT_API WALABOT_RESULT Walabot_GetSensorTargets(SensorTarget** targets, int* numTargets);

/**
* @brief Provides a list of and the number of identified targets.
*
* Available only if one of the Tracker scan profiles was used.\n
* Requires previous Walabot_Trigger(); provides data based on last completed triggered image.\n
* Provided Tracked targets configured arena and on current configuration from Walabot_SetDynamicImageFilter() and Walabot_SetThreshold().
* \param[out] targets List of identified targets
* \param[out] numTargets Number of identified targets
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow Walabot_Trigger\n Walabot_
*/
WALABOT_API WALABOT_RESULT Walabot_GetTrackerTargets(TrackerTarget** targets, int* numTargets);


/**
* @brief Dynamic-imaging filter removes static signals, leaving only changing signals.
*
* Specify filter algorithm to use. Filters are explained in \ref _features.\n
* Filter is not applied to Walabot_GetImageEnergy().\n
* To check the current value, use Walabot_GetDynamicImageFilter().
* \param[in] type Filter algorithm to use
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_GetDynamicImageFilter
*/
WALABOT_API WALABOT_RESULT Walabot_SetDynamicImageFilter(FILTER_TYPE type);


/**
* @brief Obtains current Walabot Dynamic-imaging filter setting.
* 
* Can be called at any time, default value is FILTER_TYPE_NONE
* \param[out] type Dynamic-imaging filter current setting.
* @return ::WALABOT_RESULT
* @sa \ref _features\n \ref _flow\n Walabot_GetDynamicImageFilter
*/
WALABOT_API WALABOT_RESULT Walabot_GetDynamicImageFilter(FILTER_TYPE* type);

/**
* @brief Obtains current Walabot version.
*
* Function returns Walabot version. The version is build from according to\n
* the following parameters:\n
* 1) HW version - Walabot device revision.\n
* 2) SW version - Walabot SW revision.\n
* 3) Regulation information (where applicable).\n
* The user needs to pass pointer to array, and function returns\n
* a pointer to string (array of char) with the version.\n
* The function can be called only after connecting to the device.

* \param[out] version pointer to array of char with the version
* @return ::WALABOT_RESULT
* @sa Walabot_Connect\n Walabot_ConnectAny
*/
WALABOT_API WALABOT_RESULT Walabot_GetVersion(char** version);

/*!
	The linear permittivity of a homogeneous material is usually given relative to that of free space, \n
	as a relative permittivity εr.
	Valid values {1-30}
*/
#define PARAM_DIELECTRIC_CONSTANT	((char*)"DielectricConstant")

/*!
	Walabot internal pipe sensor detection percentage.
	Read only parameter.
*/
#define PARAM_CONFIDENCE_FACTOR 		((char*)"ConfidenceFactor")

/**
* @brief Set advanced Walabot parameter
*
* \param[in] paramName type Filter algorithm to use \a PARAM_DIELECTRIC_CONSTANT 
* \param[in] value advance parameter set value
* @return ::WALABOT_RESULT 
* @sa  Walabot_GetDynamicImageFilter
*/
WALABOT_API WALABOT_RESULT Walabot_SetAdvancedParameter(char* paramName, double value);

/**
* @brief Obtains current Walabot advnaced parameter value 
*
* Function returns Walabot advance parameter. 
* \param[in] paramName advance parameter name, can be one of the following:
* \a PARAM_CONFIDENCE_FACTOR  , \a PARAM_DIELECTRIC_CONSTANT
* \param[out] value paramName current value
* @return ::WALABOT_RESULT
* @sa Walabot_SetAdvancedParameter 
*/
WALABOT_API WALABOT_RESULT Walabot_GetAdvancedParameter(char* paramName, double* value);

WALABOT_API WALABOT_RESULT Walabot_GetAntennaLocation(int antennaNum, double& X, double& Y, double& Z);

}

