#pragma once
#include <SFML/Graphics.hpp>

class Food {
    public:
        Food();
        float getX() const { return x; }
        float getY() const { return y; }
        const sf::CircleShape& getShape() const { return shape; }
        void expire();
        void move(float, float);
        void update(float time);

        static constexpr int exp_time_interval = 30.0f;
    private:
        float x, y;
        float last_update_time;
        sf::CircleShape shape;
};