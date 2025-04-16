#pragma once
#include <string>
#include "role.h"
// #include "child.h"

// #include <iostream>
// using std::cout;
// using std::endl;

class Ant {

private:
    bool need_to_move = true;
    int age;
    int health;
    float x, y;
    float target_x, target_y;
    Role* current_role;

    float last_update_time = 0.0f;
    const float update_time_interval = 5.0f;
    const float age_update_time_interval = 20.0f;

public:
    float getX() const { return x; }
    float getY() const { return y; }

    Ant(float x, float y);
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

    //константы для этого класса:
    static constexpr int start_age = 0;
    static constexpr int babysitter_age = 2;
    static constexpr int soldier_age = 5;
    static constexpr int collector_age = 8;
    static constexpr int cleaner_age = 10;
    static constexpr int max_age = 12;
    static constexpr int max_health = 12;
    static constexpr int speed = 2;
};