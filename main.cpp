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
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    const int ANT_COUNT = 3;
    const int FIELD_WIDTH = 1200;
    const int FIELD_HEIGHT = 800;

    std::vector<std::unique_ptr<Ant>> ants;
    std::vector<Food> foods;

    for (int i = 0; i < ANT_COUNT; ++i) {
        // float x = static_cast<float>(std::rand() % FIELD_WIDTH);
        // float y = static_cast<float>(std::rand() % FIELD_HEIGHT);

        float x = static_cast<float>(FIELD_WIDTH / 2);
        float y = static_cast<float>(FIELD_HEIGHT / 2);
        ants.push_back(std::make_unique<Ant>(x, y, 0)); // CHILD
        ants.push_back(std::make_unique<Ant>(x, y, 1)); // BABYSITTER
        ants.push_back(std::make_unique<Ant>(x, y, 2)); // SOLDIER
        ants.push_back(std::make_unique<Ant>(x, y, 3)); // COLLECTOR
        ants.push_back(std::make_unique<Ant>(x, y, 4)); // CLEANER
    }

    Hill hill(FIELD_WIDTH / 2, FIELD_HEIGHT / 2);

    sf::RenderWindow window(sf::VideoMode({FIELD_WIDTH, FIELD_HEIGHT}), "Ant Simulation");
    window.setFramerateLimit(60);

    sf::Clock clock;
    int tick_counter = 0;
    int next_food_spawn_tick = 500 + rand() % 100;
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

        for (auto it = foods.begin(); it != foods.end();) {
            it->update(delta_time);
            if (it->isExpired()) {
                it = foods.erase(it);
            } else {
                ++it;
            }
        }

        hill.ant_amount = 0;
        for (auto& ant_f : ants) {
            if (ant_f->isAlive() && ant_f->get_curr_role() == 0) {
                hill.ant_amount += 1;
            }
        }

        std::vector<std::unique_ptr<Ant>> newborn_ants;

        for (auto& ant_f : ants) {
            if (!ant_f->isAlive()) continue;

            int role = ant_f->get_curr_role();
            if ((role == 3 || role == 1) && !ant_f->carry_food) {
                for (auto& f : foods) {
                    if ((role == 3 && f.getType() == 1) || (role == 1 && f.getType() == 0)) {
                        float tempx = f.getX();
                        float tempy = f.getY();
                        ant_f->setTarget(tempx, tempy);
                        ant_f->is_busy = true;

                        float delta_x = ant_f->getX() - tempx;
                        float delta_y = ant_f->getY() - tempy;
                        float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
                        if (distance < 0.1) {
                            ant_f->carry_food = true;
                            ant_f->carried_food_type = f.getType();
                            ant_f->setTarget(FIELD_WIDTH / 2, FIELD_HEIGHT / 2);
                            f.expire();
                            break;
                        }
                    }
                }
            } else if (ant_f->carry_food) {
                float delta_x = ant_f->getX() - FIELD_WIDTH / 2;
                float delta_y = ant_f->getY() - FIELD_HEIGHT / 2;
                float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
                if (distance < 0.1) {
                    ant_f->is_busy = false;
                    ant_f->carry_food = false;
                    if (ant_f->carried_food_type == 1) {
                        hill.sticks_amount += 1;
                        if (hill.sticks_amount >= 3) {
                            hill.size += 1;
                            hill.sticks_amount = 0;
                            hill.ant_max_capacity = (hill.size + 1);
                        }
                    } else if (ant_f->carried_food_type == 0) {
                        hill.food_amount += 1;
                        if (hill.food_amount >= 2 && hill.ant_amount < hill.ant_max_capacity) {
                            hill.food_amount = 0;
                            float newborn_x = hill.getX() + static_cast<float>(std::rand() % (15 * (hill.size + 1))) - (15 * hill.size / 2);
                            float newborn_y = hill.getY() + static_cast<float>(std::rand() % (15 * (hill.size + 1))) - (15 * hill.size / 2);
                            newborn_ants.push_back(std::make_unique<Ant>(newborn_x, newborn_y));
                        }
                    }
                }
            }
        }

        for (auto& new_ant : newborn_ants) {
            ants.push_back(std::move(new_ant));
        }
        std::vector<Ant*> ants_to_bury;

for (auto& ant_cleaner : ants) {
    if (!ant_cleaner->isAlive()) continue;

    if (ant_cleaner->get_curr_role() == CLEANER) {
        for (const auto& target_ant : ants) {
            if (target_ant.get() == ant_cleaner.get()) continue;
            if (target_ant->get_curr_role() == DEAD) {
                float dx = ant_cleaner->getX() - target_ant->getX();
                float dy = ant_cleaner->getY() - target_ant->getY();
                float distance = std::sqrt(dx * dx + dy * dy);

                ant_cleaner->setTarget(target_ant->getX(), target_ant->getY());
                ant_cleaner->is_busy = true;

                if (distance < 0.1f) {
                    ants_to_bury.push_back(target_ant.get()); // <= вот это правильная версия
                    ant_cleaner->is_busy = false;
                }

                break;
            }
        }
    }
}

for (Ant* buried : ants_to_bury) {
    for (auto it = ants.begin(); it != ants.end(); ++it) {
        if (it->get() == buried) {
            ants.erase(it);
            break;  // нашли и удалили — выходим из внутреннего цикла
        }
    }
}

       

        hill.update(delta_time);

        tick_counter++;
        if (tick_counter >= next_food_spawn_tick) {
            int type = (rand() % 4 != 0) ? 0 : 1;
            foods.emplace_back(static_cast<FoodType>(type));
            tick_counter = 0;
            next_food_spawn_tick = 500 + rand() % 100;
        }

        if (!any_alive) {
            std::cout << "Все муравьи умерли. Конец симуляции." << std::endl;
            break;
        }

        window.clear(sf::Color::White);

        float sizeHill = 15.f * (1 + hill.size);
        sf::CircleShape hillShape(sizeHill);
        hillShape.setFillColor(sf::Color(139, 69, 19));
        hillShape.setOrigin(sf::Vector2f(sizeHill, sizeHill));
        hillShape.setPosition(sf::Vector2f(hill.getX(), hill.getY()));
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

                sf::CircleShape roleDot(2.f);
                roleDot.setOrigin(sf::Vector2f(2.f, 2.f));
                roleDot.setPosition(sf::Vector2f(ant->getX(), ant->getY()));

                switch (ant->get_curr_role()) {
                    case 0: roleDot.setFillColor(sf::Color::Blue); break;
                    case 1: roleDot.setFillColor(sf::Color::Magenta); break;
                    case 2: roleDot.setFillColor(sf::Color::Red); break;
                    case 3: roleDot.setFillColor(sf::Color::Green); break;
                    case 4: roleDot.setFillColor(sf::Color::Cyan); break;
                    case 5: roleDot.setFillColor(sf::Color::White); break;
                    default: roleDot.setFillColor(sf::Color::Yellow); break;
                }

                window.draw(roleDot);

                int role = ant->get_curr_role();
                if ((role == 3 || role == 1) && ant->carry_food) {
                    if (ant->carried_food_type == 0 && role == 1) {
                        sf::CircleShape foodDot(2.f);
                        foodDot.setFillColor(sf::Color::Green);
                        foodDot.setOrigin(sf::Vector2f(2.f, 2.f));
                        foodDot.setPosition(sf::Vector2f(ant->getX() - 4.f, ant->getY() - 4.f));
                        window.draw(foodDot);
                    } else if (ant->carried_food_type == 1 && role == 3) {
                        sf::RectangleShape stickShape(sf::Vector2f(8.f, 4.f));
                        stickShape.setFillColor(sf::Color(139, 69, 19));
                        stickShape.setOrigin(sf::Vector2f(2.f, 1.f));
                        stickShape.setPosition(sf::Vector2f(ant->getX() - 4.f, ant->getY() - 4.f));
                        window.draw(stickShape);
                    }
                }
            }
        }

        window.display();
    }

    return 0;
}
