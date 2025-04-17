#pragma once
#include <string>
#include "role.h"

class GeneralInformer;

class Cleaner : public Role, public GeneralObserver
{
private:
    GeneralInformer* geninf;
public:
    void work() override;
    void clean();

    Cleaner(GeneralInformer *p_geninf);

    virtual void updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy) override;
};
