// FallDetector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "WalabotAPI.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <stdlib.h>
#include <algorithm>    // std::max
#include<string>
#include <list>
#include <time.h> 
#pragma warning(disable:4996)


#define CONFIG_FILE_PATH "C:\\Program Files\\Walabot\\WalabotSDK\\bin\\.config"

enum Placement
{
	EMPTY = 0, UP = 1, DOWN = 2, FALLEN = 3
};

enum State
{
	Idle = 0, Bi = 1, Fi = 2, Bo = 3, Fo = 4
};

#define CHECK_WALABOT_RESULT(result, func_name)					\
{																\
	if (result != WALABOT_SUCCESS)								\
	{															\
		const char* errorStr = Walabot_GetErrorString();		\
		std::cout << std::endl << func_name << " error: "       \
                  << errorStr << std::endl;                     \
		std::cout << "Press enter to continue ...";				\
		std::string dummy;										\
		std::getline(std::cin, dummy);							\
		return;													\
                                                                \
	}                                                           \
                                                                \
}
void PrintTrackerTargets(TrackerTarget* targets, int numTargets)
{
	int targetIdx;

#ifdef __LINUX__
	printf("\033[2J\033[1;1H");
#else
	//system("cls");
#endif

	if (numTargets > 0)
	{
		
		{
			printf("Num of targets: %d  Target #0: \nY = %lf \n\n\n ",
				numTargets,
				targets[0].yPosCm);
		}
	}
}
class FallDetector
{
public:
	std::map< State, std::map<Placement, State>> stateMachine;
	State state;
	Placement placement;
	int numTargets;
	FallDetector() {
		this->placement = EMPTY;
		this->state = Idle;
		numTargets = 0;

		stateMachine[Idle][EMPTY] = Idle;
		stateMachine[Idle][UP] = Bi;
		stateMachine[Idle][DOWN] = Idle;
		stateMachine[Idle][FALLEN] = Idle;

		stateMachine[Bi][EMPTY] = Idle;
		stateMachine[Bi][UP] = Bi;
		stateMachine[Bi][DOWN] = Fi;
		stateMachine[Bi][FALLEN] = Fi;

		stateMachine[Fi][EMPTY] = Idle;
		stateMachine[Fi][UP] = Bi;
		stateMachine[Fi][DOWN] = Fi;
		stateMachine[Fi][FALLEN] = Fo;

		stateMachine[Fo][EMPTY] = Idle;
		stateMachine[Fo][UP] = Bi;
		stateMachine[Fo][DOWN] = Fo;
		stateMachine[Fo][FALLEN] = Fo;

		stateMachine[Bo][EMPTY] = Idle;
		stateMachine[Bo][UP] = Bo;
		stateMachine[Bo][DOWN] = Fo;
	
	};
	~FallDetector() {
		
	}
	void GetCount(TrackerTarget *targets, int count) {
		time_t now = time(0);

		// Convert now to tm struct for local timezone
		
		placement = GetPlacement(targets, count);
		State prevState = state;
		state = stateMachine[state][placement];

		if (prevState == Fi && state == Fo) {
		std::cout << " ****** Emergency: A fall has occurred ******" <<std::endl;
		tm* localtm = localtime(&now);
		std::cout << "The local date and time is: " << asctime(localtm) << std::endl;
		PrintTrackerTargets(targets, count);
		}

	}

	Placement GetPlacement(TrackerTarget* targets, int count) {
		if (count == 0) 
			return EMPTY;
		if (targets[0].yPosCm >= 80)
			return FALLEN;
		if (targets[0].yPosCm > 40 && targets[0].yPosCm<80)
			return DOWN;
		if (targets[0].yPosCm <=40 )
			return UP;
	}

};


TrackerTarget* SortTargets(TrackerTarget* targets, int count) {
	int j, i;
	for (i = 0; i <= count; i++)
	{
		for (j = i + 1; j < count; j++)
		{
			if (targets[i].yPosCm > targets[j].yPosCm)
			{
				TrackerTarget tempTarget = targets[j];
				targets[j] = targets[i];
				targets[i] = tempTarget;
			}
		}
	}
	return targets;
}

void FallDetectorApp() {
	WALABOT_RESULT res;
	APP_STATUS appStatus;
	TrackerTarget * targets;
	FallDetector fallDetector;


	double calibrationProcess; // Percentage of calibration completed, if status is STATUS_CALIBRATING


	// ------------------------
	// Initialize configuration
	// ------------------------

	// Walabot_SetArenaR - input parameters,
	double minInCm = 5;
	double maxInCm = 400;
	double resICm = 5;
	int numOfTargets;
	// Walabot_SetArenaTheta - input parameters
	double minIndegrees = -90;
	double maxIndegrees = 90;
	double resIndegrees = 10;

	// Walabot_SetArenaPhi - input parameters
	double minPhiInDegrees = -90;
	double maxPhiInDegrees = 90;
	double resPhiInDegrees = 3;

	// ----------------------
	// Sample Code Start Here
	// ----------------------

	/*
		For an image to be received by the application, the following need to happen :
		1) Connect
		2) Configure
		3) Calibrate
		4) Start
		5) Trigger
		6) Get action
		7) Stop/Disconnect
	*/

	bool mtiMode = true;

	res = Walabot_Initialize(CONFIG_FILE_PATH);
	CHECK_WALABOT_RESULT(res, "Walabot_Initialize");


	//	1) Connect : Establish communication with Walabot.
	//	==================================================
	res = Walabot_ConnectAny();
	CHECK_WALABOT_RESULT(res, "Walabot_ConnectAny");

	//  2) Configure : Set scan profile and arena
	//	=========================================

	// Set Profile - to Tracker. 
	//			Walabot recording mode is configure with the following attributes:
	//			-> Distance scanning through air; 
	//			-> high-resolution images
	//			-> slower capture rate 
	res = Walabot_SetProfile(PROF_TRACKER);
	CHECK_WALABOT_RESULT(res, "Walabot_SetProfile");

	res = Walabot_SetThreshold(30);
	CHECK_WALABOT_RESULT(res, "Walabot_SetThreshold");

	// Setup arena - specify it by Cartesian coordinates(ranges and resolution on the x, y, z axes); 
	//	In Tracker mode there is need to specify Spherical coordinates(ranges and resolution along radial distance and Theta and Phi angles).
	res = Walabot_SetArenaR(minInCm, maxInCm, resICm);
	CHECK_WALABOT_RESULT(res, "Walabot_SetArenaR");

	// Sets polar range and resolution of arena (parameters in degrees).
	res = Walabot_SetArenaTheta(minIndegrees, maxIndegrees, resIndegrees);
	CHECK_WALABOT_RESULT(res, "Walabot_SetArenaTheta");

	// Sets azimuth range and resolution of arena.(parameters in degrees).
	res = Walabot_SetArenaPhi(minPhiInDegrees, maxPhiInDegrees, resPhiInDegrees);
	CHECK_WALABOT_RESULT(res, "Walabot_SetArenaPhi");

	FILTER_TYPE filterType = mtiMode ?
		FILTER_TYPE_MTI :		//Moving Target Identification: standard dynamic-imaging filter
		FILTER_TYPE_NONE;

	res = Walabot_SetDynamicImageFilter(filterType);
	CHECK_WALABOT_RESULT(res, "Walabot_SetDynamicImageFilter");

	//	3) Start: Start the system in preparation for scanning.
	//	=======================================================
	res = Walabot_Start();
	CHECK_WALABOT_RESULT(res, "Walabot_Start");

	//  4) Start Calibration - only if MTI mode is not set - (there is no sense 
	//	executing calibration when MTI is active)
	//	========================================================================
	if (!mtiMode)
	{
		// calibrates scanning to ignore or reduce the signals
		res = Walabot_StartCalibration();
		CHECK_WALABOT_RESULT(res, "Walabot_StartCalibration");
	}
	std::cout << "Walabot has started tracking" << std::endl;
	bool recording = true;
	while (recording)
	{
		// calibrates scanning to ignore or reduce the signals
		res = Walabot_GetStatus(&appStatus, &calibrationProcess);
		CHECK_WALABOT_RESULT(res, "Walabot_GetStatus");

		//	5) Trigger: Scan(sense) according to profile and record signals to be 
		//	available for processing and retrieval.
		//	====================================================================
		res = Walabot_Trigger();
		CHECK_WALABOT_RESULT(res, "Walabot_Trigger");

		//	6) 	Get action : retrieve the last completed triggered recording 
		//	================================================================
		
		
		res = Walabot_GetTrackerTargets(&targets, &numOfTargets);
		CHECK_WALABOT_RESULT(res, "Walabot_GetTrackerTargets");
		 
		if (numOfTargets > 1)
			targets = SortTargets(targets, numOfTargets);	
//		if (numOfTargets > 0)
	//		PrintTrackerTargets(targets, numOfTargets);
		fallDetector.GetCount(targets, numOfTargets);
	

	}
	res = Walabot_Stop();
	CHECK_WALABOT_RESULT(res, "Walabot_Stop");

	res = Walabot_Disconnect();
	CHECK_WALABOT_RESULT(res, "Walabot_Disconnect");

	Walabot_Clean();
	CHECK_WALABOT_RESULT(res, "Walabot_Clean");
}

int main()
{
	FallDetectorApp();
}

