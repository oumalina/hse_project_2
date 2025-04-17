#include "babysitter.h"

Babysitter::Babysitter(GeneralInformer *ginf)
{
    this->geninf = ginf;
    ginf->attach(this);
}

void Babysitter::updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy)
{
    baby_coord_x = baby_cx;
    baby_coord_y = baby_cy;
}

void Babysitter::work()
{
    //заменить на реальную работу
    std::cout << "Слежу за малышами." << std::endl;
}
