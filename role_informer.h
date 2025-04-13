#pragma once
#include "role.h"

#include <vector>
#include <algorithm> // need for std::remove

class RoleInformer {
protected:
    std::vector<RoleObserver*> observers;
public:
    void attach(RoleObserver* rl);
    void detach(RoleObserver* rl);
};


void RoleInformer::attach(RoleObserver* rl) {
    observers.push_back(rl);
}

void RoleInformer::detach(RoleObserver* rl) {
    observers.erase(std::remove(observers.begin(), observers.end(), rl), 
                                observers.end());
}
