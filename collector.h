#pragma once
#include <string>
#include "role.h"

class CollectorInformer;
class GeneralInformer;

class Collector : public GeneralObserver, public RoleObserver, public Role
{
private:
    GeneralInformer* geninf;
    CollectorInformer* colinf;
public:
    void work() override;

    virtual void updateGeneral(int, int, int, int) override;
    virtual void update(int targ_x, int targ_y) override;
};

void Collector::updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy) {
    enemy_coord_x = enemy_cx;
    enemy_coord_y = enemy_cy;
}

void Collector::update(int targ_x, int targ_y) {
    target_coord_x = targ_x;
    target_coord_y = targ_y;
}