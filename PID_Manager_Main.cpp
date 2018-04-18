#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <chrono>

#define THREADCOUNT 10 		//To change number of threads just alter this number


#include "PID_Manager.h"

using namespace std;
void operate(PIDmanager&, int);


int main()
{
	PIDmanager manager;		//creates an instance of the manager object
	//manager.allocate_map();	//initializes the structure for PID management

	thread threads[THREADCOUNT];	

	for (int i = 0; i < THREADCOUNT; i++)
	{
		threads[i] = thread(operate, manager, i);
	}

	for (int i = 0; i < THREADCOUNT; i++)
	{
		threads[i].join();
	}

	system("pause");
	cout << "\n\nafter execution..." << endl;	manager.getWalker();
	

	system("pause");
	return 0;
}


void operate(PIDmanager& manager, int index)
{
	int mintime = 0, maxtime = 1000; //time values in milliseconds

	srand(time(NULL));  

	int random = rand() % maxtime + mintime;
	

	//-----These lines add debugging phrases to the output window. Uncommenting them doesn't affect program performance, but since the threads are all running simultaneously,
	//				they're never in order and they don't serve much purpose
	/*
	for (int i = 0; i < 5; i++)			//debugging line to see the PIDS array at every step. hoewever, since everything threads together, it becomes incoherent in command prompt
	{
		cout << "PIDS array looks like: " << endl;
		cout << "manager.PIDS[" << i << "] == " << manager.PIDS[i] << endl;
	}

	cout << "Status report on Thread " << index << endl;
	*/

	int myPID = manager.allocate_pid();		//PID is allocated here
	cout << "my thread number: " << index << endl;
	cout << "myPID = " << myPID << endl;


	std::this_thread::sleep_for(std::chrono::milliseconds(random));

	manager.release_pid(myPID);
}

