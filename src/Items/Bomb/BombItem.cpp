#include "BombItem.h"
#include <iostream>

void BombItem::operator+(Player& player){
    player.addBomb();
}

void BombItem::print(std::ostream& out) const {
    out << "BombItem";
}
