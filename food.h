#pragma once
#include <SFML/Graphics.hpp>

enum FoodType { FOOD, STICK };

class Food {
public:
    Food(FoodType type = FOOD);
    float getX() const { return x; }
    float getY() const { return y; }
    const sf::Drawable& getShape() const; // универсальный доступ к drawable
    void expire();
    void move(float, float);
    void update(float time);
    bool isExpired() const { return expired; }
    FoodType getType() const { return type; }

    static constexpr float exp_time_interval = 30.0f;

private:
    float x, y;
    float last_update_time;
    bool expired = false;
    FoodType type;

    sf::CircleShape foodShape;
    sf::RectangleShape stickShape;
};
