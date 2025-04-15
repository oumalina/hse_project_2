#include "hill.h"

void hill::size_up() {
    food_max_capacity += 10;
    ant_max_capacity += 10;
    //текстурка больше
}

void hill::shrink() {
    food_max_capacity += 10;
    ant_max_capacity += 10;
    //текстурка меньше
}

void hill::update(float time) {
    last_update_time += time;

    if (last_update_time >= update_time_interval) {
        last_update_time = 0;
        shrink();
    }
}