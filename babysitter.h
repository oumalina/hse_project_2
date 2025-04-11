#pragma once
#include <string>
#include "role.h"

class babysitter : public role
{
public:
    virtual void work();
    void feed();
};