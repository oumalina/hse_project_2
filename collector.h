#pragma once
#include <string>
#include "role.h"

class collector : public Role
{
public:
    virtual void work();
    void collect();
};