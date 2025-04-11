#pragma once
#include <string>
#include "role.h"

class collector : public role
{
public:
    virtual void work();
    void collect();
};