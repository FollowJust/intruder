#ifndef BEAT_POLICY_H
#define BEAT_POLICY_H

#include "Policy.h"

class BeatPolicy: public Policy {
public:
    void operator+(Player* player);
};

#endif