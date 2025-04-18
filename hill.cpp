#include "hill.h"
#include "ant.h"

Hill::Hill(float new_x, float new_y) {
    size = 0;
    ant_amount = 0;
    food_amount = 0;
    sticks_amount = 0;
    last_update_time = 0.0f;

    food_max_capacity = 0;
    ant_max_capacity = 1;

    x = new_x;
    y = new_y;
}

void Hill::size_up() {
    food_max_capacity += 10;
    ant_max_capacity += 10;
    //текстурка больше
}

void Hill::shrink() {
    food_max_capacity += 10;
    ant_max_capacity += 10;
    //текстурка меньше
}

void Hill::update(float time) {
    last_update_time += time;

    if (last_update_time >= update_time_interval) {
        last_update_time = 0;
        shrink();
    }

    if (ant_amount < ant_max_capacity) {
        Ant(x, y);
        ant_amount += 1;
    }
}