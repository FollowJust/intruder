#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>

#include "../Field/Field.h"
#include "CellView.h"
#include "ItemView.h"
#include "CreatureView.h"







class Display
{
private:

	
	Field* fieldPointer;

	int windowSizeX, windowSizeY;
	int bottomMenuSizeY;
	int rectSize;

	int marginLeft = 50;

	int fieldSizeX, fieldSizeY;


	ItemView itemView;
	CellView cellView;
	CreatureView creatureView;

	void displayField(sf::RenderWindow& gameWindow);
	void displayItems(sf::RenderWindow& gameWindow);

	void displayCreatures(sf::RenderWindow& gameWindow);

	void displayBottomStats(sf::RenderWindow& gameWindow, Player* player);

public:
	Display(int windowSizeX, int windowSizeY, int bottomMenuSizeY, int rectSize);
	
	void drawStartMenu(sf::RenderWindow& gameWindow);
	void drawGame(sf::RenderWindow& gameWindow, Player* player);
	void drawEndMenu(sf::RenderWindow& gameWindow);

};

#endif