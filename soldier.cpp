#include "soldier.h"

void Soldier::work()
{
    //заменить на реальную работу
    std::cout << "Солдат солдатит." << std::endl;
}

void Soldier::update(int targ_x, int targ_y) {
    target_coord_x = targ_x;
    target_coord_y = targ_y;
}