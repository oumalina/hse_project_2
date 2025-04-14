#pragma once
#include "role.h"

#include <vector>
#include <algorithm> // need for std::remove

class GeneralInformer {
private:
    std::vector<GeneralObserver*> observers;
    int enemy_pos_x, enemy_pos_y;
    int baby_pos_x, baby_pos_y;
public:
    void attach(GeneralObserver* rl);
    void detach(GeneralObserver* rl);
    void notify(void);
    // void setContext();
};

void GeneralInformer::attach(GeneralObserver* rl) {
    observers.push_back(rl);
}

void GeneralInformer::detach(GeneralObserver* rl) {
    observers.erase(std::remove(observers.begin(), observers.end(), rl), 
                                observers.end());
}

void GeneralInformer::notify(void) {
    for (auto obs: observers) {
        obs->updateGeneral(enemy_pos_x, enemy_pos_y, baby_pos_x, baby_pos_y);
    }
}