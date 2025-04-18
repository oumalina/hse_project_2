#include "food.h"
#include <stdlib.h>
#include <algorithm>

Food::Food(FoodType type) : type(type)
{
    x = rand() % 1260;
    y = rand() % 700;
    last_update_time = 0;

    if (type == FOOD) {
        foodShape.setRadius(6.f);
        foodShape.setFillColor(sf::Color::Green);
        foodShape.setOrigin(sf::Vector2f(6.f, 6.f));
        foodShape.setPosition(sf::Vector2f(x, y));
    } else {
        stickShape.setSize(sf::Vector2f(20.f, 8.f)); // увеличено
        stickShape.setFillColor(sf::Color(139, 69, 19));
        stickShape.setOrigin(sf::Vector2f(10.f, 4.f)); // центр
        stickShape.setPosition(sf::Vector2f(x, y));
    }
}

void Food::update(float time)
{
    if (last_update_time < 0 || expired) return;
    last_update_time += time;

    float decay_ratio = std::min(last_update_time / exp_time_interval, 1.0f);

    if (type == FOOD) {
        sf::Color color(
            static_cast<unsigned char>(0 + decay_ratio * 139),
            static_cast<unsigned char>(255 - decay_ratio * 186),
            static_cast<unsigned char>(0 + decay_ratio * 19)
        );
        foodShape.setFillColor(color);
    } else if (type == STICK) {
        float height = 8.f * (1.f - decay_ratio);
        height = std::max(height, 1.f);
        stickShape.setSize(sf::Vector2f(20.f, height));
        stickShape.setOrigin(sf::Vector2f(10.f, height / 2));

    }

    if (last_update_time >= exp_time_interval) {
        last_update_time = -1;
        expire();
    }
}

void Food::expire()
{
    expired = true;
    if (type == FOOD) {
        foodShape.setRadius(0.f);
    } else {
        stickShape.setSize(sf::Vector2f(0.f, 0.f));
    }
}

void Food::move(float new_x, float new_y)
{
    x = new_x;
    y = new_y;
    if (type == FOOD) {
        foodShape.setPosition(sf::Vector2f(x, y));
    } else {
        stickShape.setPosition(sf::Vector2f(x, y));
    }
    last_update_time = -1;
}

const sf::Drawable& Food::getShape() const {
    return (type == FOOD) ? static_cast<const sf::Drawable&>(foodShape)
                          : static_cast<const sf::Drawable&>(stickShape);
}
