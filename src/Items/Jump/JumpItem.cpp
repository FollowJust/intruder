#include "JumpItem.h"

void JumpItem::operator+(Player& player){
    player.addJump();
}

void JumpItem::print(std::ostream& out) const {
    out << "JumpItem";
}