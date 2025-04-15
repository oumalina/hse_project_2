#pragma once
#include <string>
#include "role.h"
// #include "child.h"

// #include <iostream>
// using std::cout;
// using std::endl;

class ant {
private:
    int age = 0;
    int health = 0;
    int x, y;

    float last_update_time = 0.0f;
    const float update_time_interval = 5.0f;
    const int babysitter_age = 2;
    const int soldier_age = 5;
    const int collector_age = 8;
    const int cleaner_age = 10;
    const int max_age = 12;

    std::string *role;
    Role* current_role;
public:
    ant(Role*, int, int);
	/*~ant() {
        delete current_role;
    } это то же самое что и death()? */
    void performWork();
    void move();
    bool IsAlive();
    void updateRole(const float time);
    void death();
};


// ant::ant(Role* initial_role, int initial_age=0, int initial_health=100) {
//     cout << "ant constructor" << endl;
//     current_role = initial_role; 
//     age = initial_age;
//     health = initial_health;
// }