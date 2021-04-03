#include "Creature.h"

void Creature::move(int deltaX, int deltaY){
    this->x += deltaX;
    this->y += deltaY;
}

void Creature::takeDamage(int damage){
    this->hitPoints -= damage;
}
