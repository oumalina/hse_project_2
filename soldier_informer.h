#pragma once
#include "role.h"
#include "role_informer.h"

class SoldierInformer: public RoleInformer {
private:
    int enemy_pos_x, enemy_pos_y;
public:
    void notify(void);
    // void setContext();
};

void SoldierInformer::notify(void) {
    for (auto obs: observers) {
        obs->update(enemy_pos_x, enemy_pos_y);
    }
}


