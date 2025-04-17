#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

#include "ant.h"
#include "ant.cpp"
#include "hill.h"
#include "hill.cpp"
#include "food.h"
#include "food.cpp"

#include "cleaner.cpp"
#include "babysitter.cpp"
#include "soldier.cpp"
#include "collector.cpp"

#include <SFML/Graphics.hpp>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed для rand()

    const int ANT_COUNT = 10;
    const int FIELD_WIDTH = 1200;
    const int FIELD_HEIGHT = 800;

    std::vector<std::unique_ptr<Ant>> ants;
    std::vector<Food> foods;

    // Создание муравьёв
    for (int i = 0; i < ANT_COUNT; ++i) {
        float x = static_cast<float>(std::rand() % FIELD_WIDTH);
        float y = static_cast<float>(std::rand() % FIELD_HEIGHT);
        ants.push_back(std::make_unique<Ant>(x, y));
    }

    Hill hill(FIELD_WIDTH / 2, FIELD_HEIGHT / 2);

    sf::RenderWindow window(sf::VideoMode({FIELD_WIDTH, FIELD_HEIGHT}), "Ant Simulation");
    window.setFramerateLimit(60);

    sf::CircleShape hillShape(30.f);
    hillShape.setFillColor(sf::Color(139, 69, 19));
    hillShape.setOrigin(sf::Vector2f(30.f, 30.f));
    hillShape.setPosition(sf::Vector2f(hill.getX(), hill.getY()));

    sf::Clock clock;
    int tick_counter = 0;
    int next_food_spawn_tick = 60 + rand() % 120; // случайно от 1 до 3 секунд при 60 FPS

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        float delta_time = clock.restart().asSeconds();
        bool any_alive = false;

        for (auto& ant : ants) {
            if (ant->isAlive()) {
                ant->update(delta_time);
                any_alive = true;
            }
        }

        hill.update(delta_time);

        // Создание еды с интервалом
        tick_counter++;
        if (tick_counter >= next_food_spawn_tick) {
            foods.emplace_back(); // создаём еду
            tick_counter = 0;
            next_food_spawn_tick = 60 + rand() % 120; // заново выбираем интервал
        }

        if (!any_alive) {
            std::cout << "Все муравьи умерли. Конец симуляции." << std::endl;
            break;
        }

        // Отрисовка
        window.clear(sf::Color::White);
        window.draw(hillShape);

        for (const auto& food : foods) {
            window.draw(food.getShape());
        }

        for (const auto& ant : ants) {
            if (ant->isAlive()) {
                sf::CircleShape antShape(5.f);
                antShape.setFillColor(sf::Color::Black);
                antShape.setOrigin(sf::Vector2f(5.f, 5.f));
                antShape.setPosition(sf::Vector2f(ant->getX(), ant->getY()));
                window.draw(antShape);
            }
        }

        window.display();
    }

    return 0;
}
