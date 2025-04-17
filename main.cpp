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

#include "role_enum.h"
#include <SFML/Graphics.hpp>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed для rand()

    const int ANT_COUNT = 5;
    const int FIELD_WIDTH = 1200;
    const int FIELD_HEIGHT = 800;

    std::vector<std::unique_ptr<Ant>> ants;
    std::vector<Food> foods;

    // Создание муравьёв
    for (int i = 0; i < ANT_COUNT; ++i) {
        float x = static_cast<float>(std::rand() % FIELD_WIDTH);
        float y = static_cast<float>(std::rand() % FIELD_HEIGHT);
        ants.push_back(std::make_unique<Ant>(x, y, BABYSITTER));
        ants.push_back(std::make_unique<Ant>(x, y, SOLDIER));
        ants.push_back(std::make_unique<Ant>(x, y, COLLECTOR));
        ants.push_back(std::make_unique<Ant>(x, y));
    }

    Hill hill(FIELD_WIDTH / 2, FIELD_HEIGHT / 2);

    // Создание окна
    sf::RenderWindow window(sf::VideoMode({FIELD_WIDTH, FIELD_HEIGHT}), "Ant Simulation");
    window.setFramerateLimit(60);

    // Визуальный объект для муравейника
    sf::CircleShape hillShape(30.f);
    hillShape.setFillColor(sf::Color(139, 69, 19)); // коричневый
    hillShape.setOrigin(sf::Vector2f(30.f, 30.f));
    hillShape.setPosition(sf::Vector2f(hill.getX(), hill.getY()));

    // Главный цикл
    sf::Clock clock; // Часы для отслеживания времени
    int tick_counter = 0;
    int next_food_spawn_tick = 600 + rand() % 120;
    while (window.isOpen()) {
        // sf::Event event; //vlad
        // Работа с событиями
        while (auto event = window.pollEvent()) {
        // while (window.pollEvent(event)) { //vlad
            // if (event.type == sf::Event::Closed) { //vlad
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Вычисляем дельту времени
        float delta_time = clock.restart().asSeconds();

        bool any_alive = false;

        // Обновление муравьев
        for (auto& ant : ants) {
            if (ant->isAlive()) {
                ant->update(delta_time); // Здесь муравей обновляет свои координаты
                any_alive = true;
            }
        }

        for (auto it = foods.begin(); it != foods.end(); ) {
            it->update(delta_time);
            if (it->isExpired()) {
                it = foods.erase(it);
            } else {
                ++it;
            }
        }

        for (auto &ant_f : ants) {
            if (ant_f->isAlive() && ant_f->get_curr_role() == COLLECTOR)
            {
                if (!ant_f->carry_food)
                {
                    if (!foods.empty())
                    {
                        auto curr_food = foods.front();
                        float tempx = curr_food.getX();
                        float tempy = curr_food.getY();
                        ant_f->setTarget(tempx, tempy);
                        ant_f->is_busy = true;

                        float delta_x = ant_f->getX() - tempx;
                        float delta_y = ant_f->getY() - tempy;
                        float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
                        if (distance < 0.1)
                        {
                            // ant_f->is_busy = false;
                            ant_f->carry_food = true;
                            ant_f->setTarget(FIELD_WIDTH / 2, FIELD_HEIGHT / 2);
                            foods.erase(foods.begin()); // yдаление еды
                        }
                    }
                    else
                    {
                        ant_f->is_busy = false;
                    }
                }
                else {
                    float delta_x = ant_f->getX() - FIELD_WIDTH / 2;
                    float delta_y = ant_f->getY() - FIELD_HEIGHT / 2;
                    float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
                    if (distance < 0.1)
                    {
                        ant_f->is_busy = false;
                        ant_f->carry_food = false;
                    }
                }
            }
        }

        hill.update(delta_time); // Если требуется, обновляем муравейник

        tick_counter++;
        if (tick_counter >= next_food_spawn_tick) {
            foods.emplace_back(); // создаём еду
            tick_counter = 0;
            next_food_spawn_tick = 600 + rand() % 300; // заново выбираем интервал
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
                // Основной чёрный кружок муравья
                sf::CircleShape antShape(5.f);
                antShape.setFillColor(sf::Color::Black);
                antShape.setOrigin(sf::Vector2f(5.f, 5.f));
                antShape.setPosition(sf::Vector2f(ant->getX(), ant->getY()));
                window.draw(antShape);
        
                // Цветная точка, обозначающая роль
                sf::CircleShape roleDot(2.f);
                roleDot.setOrigin(sf::Vector2f(2.f, 2.f));
                roleDot.setPosition(sf::Vector2f(ant->getX(), ant->getY()));
        
                switch (ant->get_curr_role()) {
                    case 0: roleDot.setFillColor(sf::Color::Blue); break;      // CHILD
                    case 1: roleDot.setFillColor(sf::Color::Magenta); break;   // BABYSITTER
                    case 2: roleDot.setFillColor(sf::Color::Red); break;       // SOLDIER
                    case 3: roleDot.setFillColor(sf::Color::Green); break;     // COLLECTOR
                    case 4: roleDot.setFillColor(sf::Color::Cyan); break;      // CLEANER
                    case 5: roleDot.setFillColor(sf::Color::White); break;     // DEAD
                    default: roleDot.setFillColor(sf::Color::Yellow); break;   // непредвиденные случаи
                }
        
                window.draw(roleDot);
                if (ant->get_curr_role() == COLLECTOR && ant->carry_food) {
                    sf::CircleShape foodDot(2.f);
                    foodDot.setFillColor(sf::Color::Green);
                    foodDot.setOrigin(sf::Vector2f(2.f, 2.f));
                    foodDot.setPosition(sf::Vector2f(ant->getX() - 4.f, ant->getY() - 4.f));
                    window.draw(foodDot);
                }
            }
        }
        

        window.display();
    }

    return 0;
}