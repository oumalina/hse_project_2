#pragma once
#include <string>
#include "role.h"

class babysitter : public Role
{
public:
    virtual void work();
    void feed();
};