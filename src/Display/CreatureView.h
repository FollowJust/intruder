#ifndef CREATURE_VIEW_H
#define CREATURE_VIEW_H

#include <SFML/Graphics.hpp>
#include "../Cell/Cell.h"
#include <iostream>

enum class CreatureType {
	PLAYER,
	BEATENEMY,
	ROBENEMY,
	SHOCKENEMY
};

class CreatureView {
private:
	CreatureType creatureType;

	sf::Sprite creatureSprite;
	int rectSize;

	sf::Texture playerTexture;
	sf::Texture beatEnemyTexture;
	sf::Texture robEnemyTexture;
	sf::Texture shockEnemyTexture;

public:
	CreatureView();
	void setCreatureType(CreatureType creatureType);
	sf::Sprite getSprite();
	void setRectSize(int newRectSize) { this->rectSize = newRectSize; };
};

#endif
