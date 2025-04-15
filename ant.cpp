#include "ant.h"

bool ant::IsAlive()
{
    return (health > 0);
}

void ant::performWork() {
    if (current_role) {
        current_role->work();
    }
}

void ant::move() {
    x += (rand() % 3) - 1;
    y += (rand() % 3) - 1;
}

void ant::updateRole(float time) {
    last_update_time += time;

    if (last_update_time >= update_time_interval) {
        ++age;
        last_update_time = 0;
        updateRole(time);
    }

    if (age >= max_age) {
        death();
    }
}

void ant::death() {
    //кровь-кишки-текстурки
    delete current_role;
}