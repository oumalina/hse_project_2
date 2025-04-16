#pragma once
#include <iostream>

class Role {
public:
    // these variables are declared here, not in ObserverGeneral and ObserverRole
    // so that they can be used directly in the Ant class by the Role pointer.
    // RoleObserver
    // TARGET is food for collectors and enemy for soldiers
    int target_coord_x;
    int target_coord_y;
    // GeneralObserver
    int enemy_coord_x;
    int enemy_coord_y;
    int baby_coord_x;
    int baby_coord_y;
    /////////////

    virtual void work() = 0;
    virtual ~Role() = default;
};


class GeneralObserver {
public:
    /* when the anthill is attacked, GeneralInformer use this method
    to send locations of enemies and babies to every Role instance */ 
    virtual void updateGeneral(int enemy_coord_x, int enemy_coord_y, 
                                int baby_coord_x, int baby_coord__y) = 0;
};

class RoleObserver {
public:
    /*  SoldierInformer sends enemy location to every soldier,
        CollectorInformer sends location of a big amout of food to every collector  */
    virtual void update(int targ_x, int targ_y) = 0;
};