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
    std::string *role;
    Role* current_role;
public:
    ant(Role*, int, int);
	~ant() {
        delete current_role;
    }
    void performWork();
    void move();
    bool IsAlive();
};


// ant::ant(Role* initial_role, int initial_age=0, int initial_health=100) {
//     cout << "ant constructor" << endl;
//     current_role = initial_role; 
//     age = initial_age;
//     health = initial_health;
// }