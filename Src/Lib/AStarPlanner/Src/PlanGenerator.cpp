#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "PlanGenerator.h"
#include <assert.h>

using namespace std;

#ifdef _WIN32
#include <windows.h>
HANDLE print_lock = NULL;
HANDLE stat_lock = NULL;
#else
#include <pthread.h>
pthread_mutex_t print_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t stat_lock = PTHREAD_MUTEX_INITIALIZER;
#endif

clock_t total_elapsed_clock = 0;
clock_t total_elapsed_clock_ext = 0;
int total_num_calculations = 0;
int total_num_calculations_ext = 0;
int total_length_of_path = 0;

bool GenerateMotionPlanFor(int robotid,
    WorkspaceInfo* WSInfo,
    int startLocation,
    int endLocation,
    vector<int> obstacleLocations,
    vector< vector<WS_Coord> > avoidPositions,
    int sequenceOfSteps[1000],
    int* stepsSize
    )
{
#ifdef _WIN32
	if(!print_lock) {
		print_lock = CreateMutex(NULL, FALSE, NULL);
	}
	if(!stat_lock) {
		stat_lock = CreateMutex(NULL, FALSE, NULL);
	}
#endif

	RobotPosition_Vector obstacles;
	int count;
	WS_Coord coord;
	WS_Coord pos_start, pos_end, pos_obs;
   	int ***obsmap;

    coord = WSInfo->ConvertGridLocationToCoord(startLocation);
    pos_start = coord;

    coord = WSInfo->ConvertGridLocationToCoord(endLocation);
    pos_end = coord;


    printf("====================================================\n");
    printf("Robot %d\n", robotid);

    vector<int> obstList = WSInfo->GetObstaclesLocations();
    /*cout << "Obstacles:: ";
    for(int i = 0; i< obstList.size();i++)
    {
        cout<< obstList.at(i) << " ";
    }
    cout<< endl;*/

    //check that the start and end locations are not in obstacles list
    for(int i = 0; i< obstList.size();i++)
    {
        if(startLocation == obstList[i] || endLocation == obstList[i])
        {
            cout << "Start or end location is in the obstacles list";
            assert(false);
        }
    }

    for (count = 0; count < obstacleLocations.size(); count++)
	{
        coord = WSInfo->ConvertGridLocationToCoord(obstacleLocations.at(count));
		//cout << "x = " << x << " " << "y = " << y << endl;
        pos_obs = coord;
		obstacles.push_back(pos_obs);
	}

    CAstar astar;
    astar.SetDimension(WSInfo->dimension);
    astar.SetObstacleMap(WSInfo->dimension, obstacles);
 	astar.SetSEpoint(pos_start, pos_end);
    astar.SetAvoidPositions(WSInfo->dimension, avoidPositions);
		
	clock_t begin = clock();
    RobotPosition_Vector path;
    bool success = astar.FindCollisionFreePath(path);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	total_elapsed_clock += end - begin;

#ifdef _WIN32
	WaitForSingleObject(stat_lock, INFINITE);
#else
	pthread_mutex_lock(&stat_lock);
#endif
	total_num_calculations++;
	if(success) {
		total_elapsed_clock_ext += end - begin;
		total_num_calculations_ext++;
		total_length_of_path += path.size();
	}
#ifdef _WIN32
	ReleaseMutex(stat_lock);
#else
	pthread_mutex_unlock(&stat_lock);
#endif

	if(!success) {
		return false;
	}

#ifdef _WIN32
	WaitForSingleObject(print_lock, INFINITE);
#else
	pthread_mutex_lock(&print_lock);
#endif


    astar.PrintAvoidPositions();
	printf("traj calculation takes %f\n", elapsed_secs);

    *stepsSize = path.size();
	for (count = 0; count < *stepsSize; count++)
	{
		//cout << path[count] << " " << (path[count] << endl;
        sequenceOfSteps[count] = WSInfo->ConvertCoordToGridLocation(path[count]);;
	}

    obsmap = astar.GetObstacleMap();
  	astar.printTrajectory(obsmap, path);

	printf("Trajectory:");
	for (int i = 0; i < *stepsSize; i++)
	{
		printf("%d ", sequenceOfSteps[i]);
	}
	printf("\n\n");
	assert(elapsed_secs < 2.0);
	printf("====================================================\n");

#ifdef _WIN32
	ReleaseMutex(print_lock);
#else
	pthread_mutex_unlock(&print_lock);
#endif

#ifdef CHECK_ASTAR_TRAJ
	//assert that the traj generated is correct
	for (count = 0; count < *stepsSize; count++)
	{
		for (int x = 0; x < WSInfo.obstacles.size; x++)
		{
			if (WSInfo.obstacles.locations[x] == sequenceOfSteps[count])
			{
				cout << "Trajectory crashes with a static obstacle" << endl;
				exit(0);
			}
		}
		for (int y = 0; y < avoidPositions.size(); y++)
		{
			if(count < avoidPositions[y].size())
			{
				if (ConvertCoordToGridLocation(avoidPositions[y][count], WSInfo.dimension) == sequenceOfSteps[count])
				{
					cout << "Trajectory crashes with a robot " << y<< " trajectory at time "<< count << "and location " << sequenceOfSteps[count] << endl;
					exit(0);
				}
			}
			else
			{
				if (ConvertCoordToGridLocation(avoidPositions[y][avoidPositions[y].size() - 1], WSInfo.dimension) == sequenceOfSteps[count])
				{
					cout << "Trajectory crashes with a robot " << y << " stationary at time " << count << "and location " << sequenceOfSteps[count] << endl;
					exit(0);
				}
			}
		}
	}
#endif

	return true;
}

void ConvertToGotos(
        int seqOfLocations[1000],
        int stepsSize,
        int seqOfGotos[1000],
        int *gotosSize
)
{
    assert(stepsSize >= 2);
    int currentLocation, nextLocation;
    int diff;
    currentLocation = seqOfLocations[0];
    nextLocation = seqOfLocations[1];

    diff = nextLocation - currentLocation;
    int i = 0;
    *gotosSize = 0;
    while(i < stepsSize - 1)
    {
        currentLocation = seqOfLocations[i];
        nextLocation = seqOfLocations[i+1];

        if(nextLocation - currentLocation == diff)
        {
            //goto next location
            i = i + 1;
            continue;
        }
        else
        {
            diff = nextLocation - currentLocation;
            seqOfGotos[*gotosSize] = currentLocation;
            *gotosSize = *gotosSize + 1;
            i = i + 1;
        }
    }
    seqOfGotos[*gotosSize] = nextLocation;
    *gotosSize = *gotosSize + 1;

}
