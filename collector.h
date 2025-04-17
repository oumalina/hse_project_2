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

    Collector(GeneralInformer*, CollectorInformer*);

    virtual void updateGeneral(int, int, int, int) override;
    virtual void update(int targ_x, int targ_y) override;
};
