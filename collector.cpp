#include "collector.h"
#include "general_informer.h"
#include "collector_informer.h"


Collector::Collector(GeneralInformer * p_geninf, CollectorInformer * p_collinf)
{
    this->geninf = p_geninf;
    this->geninf->attach(this);

    this->colinf = p_collinf;
    this->colinf->attach(this);
}

void Collector::updateGeneral(int enemy_cx, int enemy_cy, int baby_cx, int baby_cy)
{
    enemy_coord_x = enemy_cx;
    enemy_coord_y = enemy_cy;
}

void Collector::update(int targ_x, int targ_y) {
    target_coord_x = targ_x;
    target_coord_y = targ_y;
}