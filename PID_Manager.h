#include <iostream>

#define MINPID 300
#define MAXPID 5000

using namespace std;

class PIDmanager{
																																																											public:
	
	bool PIDSbase[MAXPID+1];	//
	bool* PIDS = PIDSbase;
	int walker = MINPID;	//walker always points to the next available boolean in sequence
	int* walkerp = &walker;

	PIDmanager();
	int allocate_map();
	int allocate_pid();
	void release_pid(int);
	int getWalker();
};

PIDmanager::PIDmanager()
{
	allocate_map();
}

int PIDmanager::allocate_map()
{
	for (int i = 0; i < (MAXPID + 1); i++)
	{
		PIDS[i] = true;
	}
	return 0;
}



int PIDmanager:: allocate_pid(){

	std::this_thread::sleep_for(std::chrono::milliseconds(20));

	while (PIDS[*walkerp]==false)	//if the boolean at the current PID value is false (meaning it's already allocated)
	{
		cout << "The PID "<<*walkerp<<" is already allocated. Incrementing and retrying..." << endl;
		++*walkerp;
		if (*walkerp >= MAXPID){ *walkerp = MINPID; }
		if (PIDS[*walkerp] == true)
		{
			cout << "An available PID was found at " << *walkerp << endl;
		}
	}


	PIDS[*walkerp] = false;
	int temp = *walkerp;

	++*walkerp;
	if (*walkerp >= 305){ *walkerp = MINPID; }
	return temp;
}

void PIDmanager::release_pid(int free){
	if (PIDS[free] == true )
	{
		cout << "This boolean was already true. Something probably went wrong somewhere." << endl;
		return;
	}

	cout << "PID " << free << " released!" << endl;
	PIDS[free] = true;
}

int PIDmanager::getWalker()
{
	cout << "*walkerp is currently: " << *walkerp << endl;
	return *walkerp;
}