#ifndef CELL_VIEW_H
#define CELL_VIEW_H

#include <SFML/Graphics.hpp>
#include "../Cell/Cell.h"
#include <iostream>

class CellView {
private:
	CellType cellType;

	sf::RectangleShape rectangle;
	int rectSize;

	sf::Texture startTexture;
	sf::Texture finishTexture;

	sf::Texture floorTexture;

	sf::Texture wallTexture;

	sf::Texture bombPlantedTexture;
	sf::Texture datacenterTexture;
public:
	CellView();
	void setCellType(CellType cellType);
	sf::RectangleShape getRectShape();
	void setRectSize(int newRectSize) { this->rectSize = newRectSize; };
};

#endif
