#pragma once
#include <string>

class hill {
private:
    int size = 0;
    int ant_max_capacity = 100;
    int ant_amount = 0;
    int food_max_capacity = 100;
    int food_amount = 0;
public:
	void size_change();
    void add_food();
};