#pragma once
#include <string>
#include "role.h"

class GeneralInformer;

class Babysitter : public GeneralObserver, public Role
{
private:
    GeneralInformer* geninf;
public:
    void work() override;
    void feed();

    virtual void updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy) override;
};

void Babysitter::updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy) {
    baby_coord_x = baby_cx;
    enemy_coord_y = baby_cy;
}
