#pragma once
#include <string>
#include "role.h"

// class GeneralInformer;
#include "general_informer.h"

class Babysitter : public GeneralObserver, public Role
{
private:
    GeneralInformer* geninf;
public:
    void work() override;
    void feed();
    Babysitter(GeneralInformer* ginf);

    virtual void updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy) override;
};

