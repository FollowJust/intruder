#include "Player.h"

Player::Player(int x, int y){
    this->x = x;
    this->y = y;


    isAlive = true;
    hitPoints = 10;
    amountBombs = 0;
    amountJumps = 0;
    canSkipWalls = false;
}

void Player::heal(int healHP){
    this->hitPoints += healHP;
}

void Player::placeBomb(){
    amountBombs--;
}

void Player::useJump() {
    amountJumps--;
    canSkipWalls = true;
}

void Player::jumped() {
    canSkipWalls = false;
}

std::ostream& operator<< (std::ostream& out, Player const* player){
    out << "Player: ";
    out << "x:" << player->x << " y: " << player->y << " ";

    return out;
}

std::ostream& operator<< (std::ostream& out, const Player& player) {
    out << "Player's Inventory: ";
    out << "HP: " << player.hitPoints << " ";
    out << "Bombs: " << player.amountBombs << " Jumps: " << player.amountJumps;

    return out;
}