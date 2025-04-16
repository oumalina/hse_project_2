#include "ant.h"
#include "child.h"
#include "babysitter.h"
#include "soldier.h"
#include "cleaner.h"
#include "collector.h"

#include "role_enum.h"

// Ant::Ant(float initial_x, float initial_y) {
//     current_role = nullptr; 
//     age = start_age;
//     health = max_health;
//     need_to_move = true;
//     x = initial_x;
//     y = initial_y;
//     target_x = initial_x;
//     target_y = initial_y;
// }

/////////
Role* Ant::new_role_by_enum(int role_enum, 
        GeneralInformer* g=nullptr, SoldierInformer* s=nullptr, CollectorInformer* c=nullptr) {
    switch (role_enum)
    {
    case CHILD:
        return new Child;
        break;
    case BABYSITTER:
        return new Babysitter(g);
    case SOLDIER:
        return new Soldier(s);
    case COLLECTOR:
        return new Collector(g, c);
    case CLEANER:
        return new Cleaner(g);
    default:
        break;
    }
}
/////////

Ant::Ant(/*Role* initial_role,*/ int role_from_enum=0, int initial_age=0, int initial_health=100, int coord_x, int coord_y) {
    // cout << "ant constructor" << endl;

    current_role = new_role_by_enum(role_from_enum);
    role_name = role_from_enum;
    age = initial_age;
    health = initial_health;
    x = coord_x;
    y = coord_y;
}

Ant::~Ant()
{
    delete current_role;
}

bool Ant::isAlive()
{
    return (health > 0);
}

void Ant::performWork() {
    if (current_role != nullptr) {
        current_role->work();
    }
}

void Ant::move() {
    x += (rand() % 3) - 1;
    y += (rand() % 3) - 1;
}

Role *Ant::getRole() const {
    return current_role;
}

// void Ant::ageUp(void)
// {
//     this->age++;
//     updateRole();
// }

void Ant::setRole(Role *new_role) {
    if (current_role != nullptr) {
        delete current_role;
    }
    current_role = new_role;
    /*
    Напис)ать:
    for (для всех подписчиков) {
        меняем роль;
    }
    */
}

void Ant::updateRole() {
    switch (age) {
        case babysitter_age:
            setRole(new Babysitter());
            break;

        case soldier_age:
            setRole(new Soldier());
            break;

        case collector_age:
            setRole(new Collector());
            break;

        case cleaner_age:
            setRole(new Cleaner());
            break;

        default:
            break;
    }
}

// void Ant::updateAge(const float time) {
//     last_update_time += time;

//     if (last_update_time >= age_update_time_interval) {
//         ++age;
//         last_update_time = 0;
//         updateRole();
//     }

//     if (age >= max_age) {
//         death();
//     }
// }

void Ant::death() {
    //кровь-кишки-текстурки
    delete current_role;
}

void Ant::lower_health(int damage) {
    health -= damage;
    if (health <= 0) {
        death();
    }
}

void Ant::increase_health(int health) {
    this->health += health;
    if (this->health > max_health)
        this->health = max_health;
}

void Ant::setTarget(const float x, const float y) {
    target_x = x;
    target_y = y;
}

// void Ant::update(const float time) {
//     if (!isAlive())
//         return;

//     updateAge(time);

//     if (need_to_move && getRole() != nullptr) {
//         need_to_move = false;
//         setTarget(rand() % 1200, rand() % 800);
//     }

//     const float delta_x = target_x - x;
//     const float delta_y = target_y - y;
//     const float distance = sqrt(delta_x * delta_x + delta_y * delta_y);

//     if (distance < 0.0001) {
//         need_to_move = true;
//         return;
//     }

//     const float vector_x = delta_x / distance;
//     const float vector_y = delta_y / distance;

//     float step = speed * time;
//     if (step > distance) {
//         step = distance;
//     }

//     x += vector_x * step;
//     y += vector_y * step;
// }