#include "soldier.h"
#include "soldier_informer.h"

Soldier::Soldier(SoldierInformer *p_soldinf)
{
    this->sold_inform = p_soldinf;
    this->sold_inform->attach(this);
}

void Soldier::update(int targ_x, int targ_y)
{
    target_coord_x = targ_x;
    target_coord_y = targ_y;
}