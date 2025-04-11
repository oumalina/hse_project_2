#pragma once
#include <string>
#include "role.h"

class cleaner : public role
{
public:
    virtual void work();
    void clean();
};