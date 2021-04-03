#ifndef ROB_POLICY_H
#define ROB_POLICY_H

#include "Policy.h"

class RobPolicy : public Policy {
public:
    void operator+(Player* player);
};

#endif