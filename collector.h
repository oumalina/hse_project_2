#pragma once
#include <string>
#include "role.h"

class CollectorInformer;
class GeneralInformer;

class collector : public GeneralObserver, public RoleObserver, public Role
{
private:
    GeneralInformer* geninf;
    CollectorInformer* colinf;
public:
    void work() override;
    void collect();

    virtual void updateGeneral(int, int, int, int) override;
    virtual void update(int targ_x, int targ_y) override;
};

void collector::updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy) {
    enemy_coord_x = enemy_cx;
    enemy_coord_y = enemy_cy;
}

void collector::update(int targ_x, int targ_y) {
    target_coord_x = targ_x;
    target_coord_y = targ_y;
}