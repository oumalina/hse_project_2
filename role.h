#pragma once

class Role {
public:
    virtual void work() = 0;
    virtual ~Role() = default;
};