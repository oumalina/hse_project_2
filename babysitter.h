#pragma once
#include <string>
#include "role.h"

class GeneralInformer;

class babysitter : public GeneralObserver, public Role
{
private:
    GeneralInformer* geninf;
public:
    virtual void work();
    void feed();

    void updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy);
};

void babysitter::updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy) {
    baby_coord_x = baby_cx;
    enemy_coord_y = baby_cy;
}
