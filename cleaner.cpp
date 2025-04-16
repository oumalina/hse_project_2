#include "cleaner.h"

void Cleaner::work()
{
    //заменить на реальную работу
    std::cout << "Клининг." << std::endl;
}

void Cleaner::updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy) {
    enemy_coord_x = enemy_cx;
    enemy_coord_y = enemy_cy;
}