#pragma once
#include <string>
#include "role.h"

class SoldierInformer;

class Soldier : public RoleObserver, public Role
{
private:
    SoldierInformer* sold_inform;
public:
    void work() override;
    void kill();
    void scare();

    virtual void update(int targ_x, int targ_y) override;
};


void Soldier::update(int targ_x, int targ_y) {
    target_coord_x = targ_x;
    target_coord_y = targ_y;
}