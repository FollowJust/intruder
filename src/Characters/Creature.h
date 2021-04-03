#ifndef CREATURE_H
#define CREATURE_H


class Creature{
protected:
    int x, y;
    int hitPoints;
    bool isAlive;

public:
    int getHP() {return hitPoints;}
    int getX() { return x; }
    int getY() { return y; }

    void move(int deltaX, int deltaY);

    void takeDamage(int damage);

};

#endif
