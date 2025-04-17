#pragma once
#include <SFML/Graphics.hpp>

class Food {
public:
    Food();
    float getX() const { return x; }
    float getY() const { return y; }
    const sf::CircleShape& getShape() const { return shape; }

    void expire();              // потемнение и установка флага "протухло"
    void move(float, float);    // перемещение еды (например, в муравейник)
    void update(float time);    // обновление состояния по времени

    bool isExpired() const { return expired; } // для удаления из вектора

    static constexpr float exp_time_interval = 30.0f;

private:
    float x, y;
    float last_update_time = 0.0f;
    bool expired = false;              // признак, что еда испорчена
    sf::CircleShape shape;
};
