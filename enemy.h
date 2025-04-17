#pragma once

#include "ant.h"
class Enemy {
    int health;
    int age;
    const int max_age = 6;
    const int power = 10;
public:
    void hit(Ant* ant) {
        ant->lower_health(power);
    }
    Enemy(int init_healh=100, int init_age=1):health(init_healh), age(init_age) {}
    void ageUp() {
        if (++age >= max_age) {
            death();
        }
    }
    void death() {}
};