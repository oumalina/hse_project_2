#pragma once
#include <string>
#include "role.h"

class cleaner : public Role
{
public:
    virtual void work();
    void clean();
};