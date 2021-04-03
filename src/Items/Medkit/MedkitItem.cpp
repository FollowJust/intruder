#include "MedkitItem.h"

void MedkitItem::operator+(Player& player){
    player.heal(1);
}

void MedkitItem::print(std::ostream& out) const {
    out << "MedkitItem";
}