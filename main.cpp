#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

#include "ant.h"
#include "hill.h"
#include "food.h"

//весь main писал chatgpt так что вопросы к нему
int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed для rand()

    const int ANT_COUNT = 10;
    std::vector<std::unique_ptr<Ant>> ants;

    // Создание муравьёв
    for (int i = 0; i < ANT_COUNT; ++i) {
        ants.push_back(std::make_unique<Ant>());
    }

    Hill hill;

    float delta_time = 0.1f; // Симуляция времени: 0.1 условной секунды за итерацию

    // Главный цикл
    while (true) {
        bool any_alive = false;

        for (auto& ant : ants) {
            if (ant->isAlive()) {
                ant->update(delta_time);
                any_alive = true;
            }
        }

        hill.update(delta_time);

        if (!any_alive) {
            std::cout << "Все муравьи умерли. Конец симуляции." << std::endl;
            break;
        }

        new Food();

        // Подождем немного, чтобы "плавно" шло (имитируем FPS)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}