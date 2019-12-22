# WalabotProjects
This are projects that are built using the Walabot Sensor. 
There are three different projects in this repository: 
A) Breathing Detection: This is a python project that uses a radio frequency device called walabot, in addition to the machine learning algorithm Random Forrests,
  in order to detect breathing action and record data. A hue light is being used as an indicator,  being triggered when there is breathing action.

  Software: pyCharm, Random Forrests algorithm, Hue API
  Hardware: Walabot developer, Hue light 
  ------------------------------------------------------------------------
  
  Running instructions:

  1- Locate the python script with the name Predictions.py and open it with IDLE 3.4 or your preferred python IDE/ editor.
  2- Make sure the Walabot API is installed and placed in the correct directory as coded in the "Predictions.py" file.
  3- Update Hue light information in the code if needed
  4- Connect your Walabot Device through USB
  5- Hang your walabot device to an adjacent wall and secure it to where its stationary, with the Z+ access facing towards the breathing person
  6- Run the "Predictions.py" and the breathing predictions will start occuring.
------------------------------------------------------------------------------
B) Fall Detection: This is a python project that uses a radio frequency device by the name Walabot in order to detect emergency falls and alert a care giver
  through an SMS.

  Software Used: Visual Studio, Walabot API, Twilio API
  Hardware Used: Walabot Developer
  ------------------------------------------------------------------------------------------------------------

  Running Instructions:

  1-Locate the python script with the name FallDetection.py and open it with IDLE 3.4 or your preferred python IDE/ editor.
  2-Make sure the Walabot API is installed and placed in the correct directory as coded in the "FallDetection.py" file.
  3-Update the height of your ceiling and your preferred caregiver's number in the "FallDetection.py" file
  4-Connect your Walabot Device through USB
  5-Hang your walabot device and secure it tightly on the ceiling wall, with the Z+ access facing towards the floor. 
  6- Run the Program from VS: Debug-->"Start Without Debugging"
--------------------------------------------------------------------------------------------------------------
C) People Counter: This is a C++ program that uses a radio frequency device called Walabot in order to keep count of the number of people in a room.
  The project uses the Walabot API, along an algorithm used to localize and keep count of the people. 
  
  Software Used: Visual Studio 2019, Walabot API
  Hardware Used: Walabot Developer 
  --------------------------------------------------------------------------------------------
  
  Running Instructions:

  1-Locate the VS solution file under the name PeopleCounter.sln and open it with visual studio
  2-Make sure the Walabot API is installed and placed in the correct directory as coded in the "PeopleCounter.cpp" file.
  3-Connect your Walabot Device through USB
  5-Place the Walabot sensor by the door entrance with the positive Y axis being towards the room and the negative Y axis pointing out.
  4- Run the Program from VS: Debug-->"Start Without Debugging"


Disclaimer: All of these projects in this repository have been developed during my co-op rotations at GE Appliances, A Haier 
Company, and is thus property of the company. 
