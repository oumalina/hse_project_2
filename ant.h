#pragma once
#include <string>
#include "role.h"
// #include "child.h"

// #include <iostream>
// using std::cout;
// using std::endl;

class ant {

private:
    bool need_to_move = true;
    int age = 0;
    int health = start_age;
    float x, y;
    float target_x, target_y;
    Role* current_role = nullptr;

    float last_update_time = 0.0f;
    const float update_time_interval = 5.0f;
    const float age_update_time_interval = 20.0f;

public:
    ant(Role*, int, int);
	/*~ant() {
        delete current_role;
    } это то же самое что и death()? */
    void performWork();
    void move();
    bool isAlive();
    void death();

    void updateRole();
    void lower_health(const int damage);
    void increase_health(const int health);
    void update(const float time);
    void updateAge(const float time);
    void setRole(Role *new_role);
    void setTarget(const float x, const float y);
    Role *getRole() const;

    static constexpr int start_age = 0;
    static constexpr int babysitter_age = 2;
    static constexpr int soldier_age = 5;
    static constexpr int collector_age = 8;
    static constexpr int cleaner_age = 10;
    static constexpr int max_age = 12;
    static constexpr int speed = 2;
};


// ant::ant(Role* initial_role, int initial_age=0, int initial_health=100) {
//     cout << "ant constructor" << endl;
//     current_role = initial_role; 
//     age = initial_age;
//     health = initial_health;
// }