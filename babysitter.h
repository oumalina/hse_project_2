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
        virtual void updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy) override;
};