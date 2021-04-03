#ifndef POLICY_H
#define POLICY_H

#include "../Player.h"

class Policy {
public:
    virtual void operator+(Player* player) = 0;
};

#endif