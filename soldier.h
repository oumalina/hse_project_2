#pragma once
#include <string>
#include "role.h"

class soldier : public Role
{
public:
    virtual void work();
    void kill();
    void scare();
};