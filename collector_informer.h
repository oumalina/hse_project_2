#pragma once
#include "role.h"
#include "role_informer.h"

class CollectorInformer: public RoleInformer {
private:
    int food_pos_x, food_pos_y;
public:
    void notify(void);
    // void setContext();
};

void CollectorInformer::notify(void) {
    for (auto obs: observers) {
        obs->update(food_pos_x, food_pos_y);
    }
}