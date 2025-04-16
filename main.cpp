#include <iostream>
#include <time.h>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

#include "ant.h"
#include "hill.h"

#include "role.h"

#include "role_enum.h"

#include "child.h"
#include "babysitter.h"
#include "cleaner.h"
#include "collector.h"
#include "soldier.h"

#include "general_informer.h"
#include "soldier_informer.h"
#include "collector_informer.h"


#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif // _WIN32

using namespace std;

void sleepcp(int milliseconds);

void sleepcp(int milliseconds) // Cross-platform sleep function
{
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif // _WIN32
}

const int FIELD_X = 600;
const int FIELD_Y = 600;

int main()
{
    bool flag = true;
    int loop = 0; 
    int year = 0;
    const int LOOPS_PER_YEAR = 4;
    const int SLEEP_FOR_MS = 250;
    vector <Ant*> array_ants;
    
    Ant *a1 = new Ant(new Babysitter, BABYSITTER, 3, 100, 20, 20);
    cout << "creating ant..." << endl;
    array_ants.push_back(a1);
    while (flag)
    {

        loop++;
        if (loop % LOOPS_PER_YEAR == 0) {
            year++;
        }
        if (year == 50) {
            flag = false;
        }
        usleep(SLEEP_FOR_MS);
    }

    delete a1;
    return 0;
}