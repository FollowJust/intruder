#ifndef ITEM_VIEW_H
#define ITEM_VIEW_H

#include <SFML/Graphics.hpp>
#include "../Cell/Cell.h"
#include <iostream>

class ItemView {
private:
	int itemTypeId;

	sf::Sprite itemSprite;
	int rectSize;

	sf::Texture hpTexture;
	sf::Texture bombTexture;
	sf::Texture bombPlantedTexture;
	sf::Texture jumpTexture;
	
public:
	ItemView();
	sf::Sprite getSprite();
	void setItemTypeId(int itemTypeId);
	void setRectSize(int newRectSize) { this->rectSize = newRectSize; };
};

#endif
