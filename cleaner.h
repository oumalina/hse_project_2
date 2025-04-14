#pragma once
#include <string>
#include "role.h"

class GeneralInformer;

class cleaner : public Role, public GeneralObserver
{
private:
    GeneralInformer* geninf;
public:
    void work() override;
    void clean();

    virtual void updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy) override;
};

void cleaner::updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy) {
    enemy_coord_x = enemy_cx;
    enemy_coord_y = enemy_cy;
}
