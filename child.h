#pragma once
#include "role.h"
#include <iostream>
class Child: public Role {
public:
    virtual void work() override { }
};