#pragma once
#include <string>
#include "role.h"

class soldier : public role
{
public:
    virtual void work();
    void kill();
    void scare();
};