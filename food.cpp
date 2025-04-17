#include "food.h"
#include <stdlib.h>

Food::Food()
{
    x = rand() % 1260;
    y = rand() % 700;
    shape.setRadius(6.f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(sf::Vector2f(6.f, 6.f));
    shape.setPosition(sf::Vector2f(x, y));
    last_update_time = 0;
}

void Food::update(float time)
{
    if (last_update_time < 0) return;

    last_update_time += time;

    // Обновляем цвет в зависимости от степени порчи
    float decay_ratio = std::min(last_update_time / exp_time_interval, 1.0f);
    sf::Color color(
        static_cast<unsigned char>(0 + decay_ratio * 139),    // R: от 0 до 139
        static_cast<unsigned char>(255 - decay_ratio * 186),  // G: от 255 до 69
        static_cast<unsigned char>(0 + decay_ratio * 19)      // B: от 0 до 19
    );
    shape.setFillColor(color);

    if (last_update_time >= exp_time_interval) {
        last_update_time = -1;
        expire();
    }
}

void Food::expire()
{
    // Скрываем еду, когда она испорчена
    shape.setRadius(0.f);  // можно заменить на удаление или отключение
}

void Food::move(float new_x, float new_y) 
{
    x = new_x;
    y = new_y;
    shape.setPosition(sf::Vector2f(x, y));
    last_update_time = -1; // перемещённая еда не портится
}
