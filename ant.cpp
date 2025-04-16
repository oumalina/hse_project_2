#include "ant.h"
#include "babysitter.h"
#include "soldier.h"
#include "cleaner.h"
#include "collector.h"

Ant::Ant(float initial_x, float initial_y) {
    current_role = nullptr; 
    age = start_age;
    health = max_health;
    need_to_move = true;
    x = initial_x;
    y = initial_y;
    target_x = initial_x;
    target_y = initial_y;
}

bool Ant::isAlive()
{
    return (health > 0);
}

void Ant::performWork() {
    if (current_role) {
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


void Ant::setRole(Role *new_role) {
    if (current_role != new_role) {
        if (current_role != nullptr) {
            delete current_role;
        }
        current_role = new_role;
        /*
        Написать:
        for (для всех подписчиков) {
            меняем роль;
        }
        */
    }
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

void Ant::updateAge(const float time) {
    last_update_time += time;

    if (last_update_time >= age_update_time_interval) {
        ++age;
        last_update_time = 0;
        updateRole();
    }

    if (age >= max_age) {
        death();
    }
}

void Ant::death() {
    //кровь-кишки-текстурки
    delete current_role;
}

void Ant::lower_health(int damage) {
    health -= damage;
    if (health <= start_age) {
        death();
    }
}

void Ant::increase_health(int health) {
    this->health += health;
    if (this->health > max_age)
        this->health = max_age;
}

void Ant::setTarget(const float x, const float y) {
    target_x = x;
    target_y = y;
}

void Ant::update(const float time) {
    if (!isAlive())
        return;

    updateAge(time);

    if (need_to_move && getRole() != nullptr) {
        need_to_move = false;
        setTarget(rand() % 1200, rand() % 800);
    }

    const float delta_x = target_x - x;
    const float delta_y = target_y - y;
    const float distance = sqrt(delta_x * delta_x + delta_y * delta_y);

    if (distance < 0.0001) {
        need_to_move = true;
        return;
    }

    const float vector_x = delta_x / distance;
    const float vector_y = delta_y / distance;

    float step = speed * time;
    if (step > distance) {
        step = distance;
    }

    x += vector_x * step;
    y += vector_y * step;
}