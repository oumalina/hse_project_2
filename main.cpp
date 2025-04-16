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


void createAnt(vector <Ant*>& array, int role_from_enum, int pos_x, int pos_y, int init_age, int init_health, 
                GeneralInformer* geninf=nullptr, SoldierInformer* soldinf=nullptr, CollectorInformer* collinf=nullptr) {
    Ant *a1 = new Ant(role_from_enum, init_age, init_health, pos_x, pos_y);
    cout << "creating ant..." << endl;
    array.push_back(a1);
    if (geninf)
        geninf->attach(reinterpret_cast<GeneralObserver*>(a1->getRole())); // cast Role* to GeneralObserver*
    if (collinf)
        collinf->attach(reinterpret_cast<RoleObserver*>(a1->getRole())); // cast Role* to RoleObserver*
    if (soldinf)
        collinf->attach(reinterpret_cast<RoleObserver*>(a1->getRole()));
}


int main(void) {
    bool flag = true;
    int loop = 0; 
    int year = 0;
    const int LOOPS_PER_YEAR = 4;
    const int SLEEP_FOR_MS = 250;

    vector <Ant*> array_ants;
    GeneralInformer GENINF;
    SoldierInformer SOLDINF;
    CollectorInformer COLDINF;

    createAnt(array_ants, BABYSITTER, 20, 20, 3, 100, &GENINF);

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
 
    for (Ant* c_ant: array_ants) {
        if (c_ant) delete c_ant;
    }

    return 0;
}