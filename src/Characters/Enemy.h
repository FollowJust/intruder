#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>

#include "Creature.h"

#define ACTION_COOLDOWN 3;
#define ALARM_DISTANCE 3;

template<class TAttackPolicy> //seeker and warden //attack - bomb or just minus 1 hp
class Enemy : public Creature {
private:
    int id;
    int alarmDistance = ALARM_DISTANCE;
    int actionCooldown = 0; //in turns
    TAttackPolicy attackPolicy;

public:
    Enemy(int x, int y, int enemyId) {
        this->x = x;
        this->y = y;
        this->id = enemyId;
    }


    void action() {
        Field* field = Field::getInstance();
        Player* player = field->getPlayer(x, y);
        if (player) {
            if (actionCooldown == 0) {
                actionCooldown = ACTION_COOLDOWN;
                attackPolicy + player;
            }
            else {
                actionCooldown--;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& out, Enemy<TAttackPolicy> const* enemy) {
        out << "Enemy " << enemy->id << " ";
        out << "x:" << enemy->x << " y: " << enemy->y << "";
        return out;
    }

};


#endif
