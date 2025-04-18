#pragma once
#include <string>

class Hill {
private:

    
    float last_update_time = 0.0f;
    

    float x;
    float y;
public:
    int ant_amount = 0;
    int ant_max_capacity = 1;
    int food_max_capacity = 0;
    int sticks_amount = 0;
    int size = 0;
    int food_amount = 0;
    float getX() const { return x; }
    float getY() const { return y; }

    static constexpr float update_time_interval = 10.0f;
    Hill(float, float);
	void size_up();
    void shrink();
    void update(float time);
};