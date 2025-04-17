#include "food.h"
#include <stdlib.h>

Food::Food()
{
    x = rand() % 1260;
	y = rand() % 700;
    shape.setRadius(6.f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(sf::Vector2f(6.f, 6.f));              // исправлено
    shape.setPosition(sf::Vector2f(x, y));  
}

void Food::update(float time)
{
    if (last_update_time < 0) return;

    last_update_time += time;

    if (last_update_time >= exp_time_interval) {
        last_update_time = -1;
        expire();
    }
}

void Food::expire()
{
    //изменение текстурки
}

void Food::move(float new_x, float new_y) 
{
    x = new_x;
    y = new_y;
    last_update_time = -1; //потому что переместить можно только в склад, а там ничего не портится
}