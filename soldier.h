#pragma once
#include <string>
#include "role.h"

class SoldierInformer;

class soldier : public RoleObserver, public Role
{
private:
    SoldierInformer* sold_inform;
public:
    virtual void work();
    void kill();
    void scare();

    virtual void update(int targ_x, int targ_y) override;
};


void soldier::update(int targ_x, int targ_y) {
    target_coord_x = targ_x;
    target_coord_y = targ_y;
}