#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
private:
    float x, y;
    float speed = 50.0f;
    bool alive = true;
    sf::CircleShape shape;

public:
    Enemy(float startX, float startY)
        : x(startX), y(startY), shape(10.f) {
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin(10.f, 10.f);
    }

    void update(float deltaTime, float targetX, float targetY) {
        if (!alive) return;

        float dx = targetX - x;
        float dy = targetY - y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance > 1.0f) {
            x += dx / distance * speed * deltaTime;
            y += dy / distance * speed * deltaTime;
        }
        shape.setPosition(x, y);
    }

    float getX() const { return x; }
    float getY() const { return y; }
    bool isAlive() const { return alive; }
    void kill() { alive = false; }
    const sf::CircleShape& getShape() const { return shape; }
};
