#pragma once
#include "role.h"
#include <iostream>

class Child: public Role {
    public:
        void work() override { }
};