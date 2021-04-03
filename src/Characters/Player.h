#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include <SFML\Graphics.hpp>
#include <iostream>

class Player: public Creature{
private:
    int amountBombs;
    int amountJumps;
    bool canSkipWalls;

    bool isShocked = false;
    

public:
    Player(int x, int y);
    int getAmountJumps() { return amountJumps; };
    int getAmountBombs() { return amountBombs; };
    bool getCanSkipWalls() { return canSkipWalls; };
    void useJump();
    void jumped();

    void setHP(int newHP) { hitPoints = newHP; };
    void setAmountBombs(int newAmountBombs) { amountBombs = newAmountBombs; };
    void setAmountJumps(int newAmountJumps) { amountJumps = newAmountJumps; };
    void setCanSkipWalls(bool newState) { canSkipWalls = newState; };

    void heal(int healHP);
    void addJump() { amountJumps++; };
    void addBomb() { amountBombs++; };
    void removeJump() { if(amountJumps > 0) amountJumps--; };
    void removeBombs() { if(amountBombs > 0) amountBombs--; };

    void placeBomb();

    bool getShocked() { return isShocked; };
    void setIsShocked(bool newState) { isShocked = newState; };

    friend std::ostream& operator<<(std::ostream& out, Player const* player);
    friend std::ostream& operator<<(std::ostream& out, const Player& player);
};

#endif
