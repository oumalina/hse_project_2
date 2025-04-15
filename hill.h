#pragma once
#include <string>

class hill {
private:
    int size = 0;
    int ant_amount = 0;
    int food_amount = 0;
    float last_update_time = 0.0f;

    int food_max_capacity = 100;
    int ant_max_capacity = 100;

    const float update_time_interval = 10.0f;
public:
	void size_up();
    void shrink();
    void update(float time);
};