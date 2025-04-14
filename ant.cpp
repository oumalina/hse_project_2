#include "ant.h"

bool ant::IsAlive()
{
    return (health > 0);
}

void ant::performWork() {
    if (current_role) {
        current_role->work();
    }
}

void ant::move() {
    x += (rand() % 3) - 1;
    y += (rand() % 3) - 1;
}