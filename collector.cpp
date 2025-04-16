#include "collector.h"

void Collector::work()
{
    //заменить на реальную работу
    std::cout << "Коллектор коллекторит." << std::endl;
}

void Collector::updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy) {
    enemy_coord_x = enemy_cx;
    enemy_coord_y = enemy_cy;
}

void Collector::update(int targ_x, int targ_y) {
    target_coord_x = targ_x;
    target_coord_y = targ_y;
}