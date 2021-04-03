#ifndef SHOCK_POLICY_H
#define SHOCK_POLICY_H

#include "Policy.h"

class ShockPolicy : public Policy {
public:
    void operator+(Player* player);
};

#endif