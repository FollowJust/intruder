#include "Display.h"
#include "windows.h"
#include "stdio.h"


Display::Display(int windowSizeX, int windowSizeY, int bottomMenuSizeY, int rectSize){
	fieldPointer = Field::getInstance();
	fieldSizeX = fieldPointer->getWidth();
	fieldSizeY = fieldPointer->getHeight();
	this->windowSizeX = windowSizeX;
	this->windowSizeY = windowSizeY;
	this->bottomMenuSizeY = bottomMenuSizeY;
	this->rectSize = rectSize;

	cellView.setRectSize(this->rectSize);
	itemView.setRectSize(this->rectSize);
	creatureView.setRectSize(this->rectSize);

}

void Display::displayField(sf::RenderWindow& gameWindow){
	for (auto fieldIterator = fieldPointer->begin(); fieldIterator != fieldPointer->end(); fieldIterator++) {
		cellView.setCellType((*fieldIterator).getType());
		sf::RectangleShape rect = cellView.getRectShape();
		rect.setPosition(fieldIterator.getX() * rectSize, fieldIterator.getY() * rectSize);
		gameWindow.draw(rect);
	}
}


void Display::displayItems(sf::RenderWindow& gameWindow){
	for (auto fieldIterator = fieldPointer->begin(); fieldIterator != fieldPointer->end(); fieldIterator++) {
		if (!(*fieldIterator).getItem()) {
			continue;
		}
		itemView.setItemTypeId((*fieldIterator).getItem()->getIndex());
		sf::Sprite sprite = itemView.getSprite();
		sprite.setPosition(fieldIterator.getX() * rectSize, fieldIterator.getY() * rectSize);
		gameWindow.draw(sprite);
	}
}

void Display::displayCreatures(sf::RenderWindow& gameWindow){
	for (auto fieldIterator = fieldPointer->begin(); fieldIterator != fieldPointer->end(); fieldIterator++) {
		if ((*fieldIterator).isOccupiedByPlayer()) {
			creatureView.setCreatureType(CreatureType::PLAYER);
			sf::Sprite sprite = creatureView.getSprite();
			sprite.setPosition(fieldIterator.getX() * rectSize, fieldIterator.getY() * rectSize);
			gameWindow.draw(sprite);
		}
		else if ((*fieldIterator).isOccupiedByEnemy()) {
			
			switch ((*fieldIterator).getEnemyType()){
			case EnemyType::BEAT:
				creatureView.setCreatureType(CreatureType::BEATENEMY);
				
				break;

			case EnemyType::ROB:
				creatureView.setCreatureType(CreatureType::ROBENEMY);

				break;

			case EnemyType::SHOCK:
				creatureView.setCreatureType(CreatureType::SHOCKENEMY);

				break;

			default:
				std::cout << "wrong enemytype\n";
				break;
			}
			sf::Sprite sprite = creatureView.getSprite();
			sprite.setPosition(fieldIterator.getX() * rectSize, fieldIterator.getY() * rectSize);
			gameWindow.draw(sprite);
		}
	}
}

void Display::displayBottomStats(sf::RenderWindow& gameWindow, Player* player)
{
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(windowSizeX, bottomMenuSizeY));
	background.setFillColor(sf::Color(55, 54, 66));
	background.setPosition(0, windowSizeY);
	gameWindow.draw(background);


	sf::Text text;
	sf::Font font;

	font.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\statsFont.otf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color(237, 205, 61));

	text.setPosition(marginLeft, windowSizeY);
	text.setString("Health: " + std::to_string(player->getHP()));
	gameWindow.draw(text);

	text.setPosition(marginLeft + windowSizeX * 1 / 3, windowSizeY);
	text.setString("Bombs: " + std::to_string(player->getAmountBombs()));
	gameWindow.draw(text);

	text.setPosition(marginLeft + windowSizeX * 2 / 3, windowSizeY);
	text.setString("Jumps: " + std::to_string(player->getAmountJumps()));
	gameWindow.draw(text);
}

void Display::drawStartMenu(sf::RenderWindow& gameWindow) {
	int x = windowSizeX / 4 - windowSizeX / 10;
	int y = windowSizeY / 2 - windowSizeY / 10;
	sf::Text text;
	sf::Font font;

	font.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\statsFont.otf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color(237, 205, 61));
	text.setPosition(x, y);
	text.setString("To start a game press Enter...");

	sf::Text text2;
	text2.setFont(font);
	text2.setCharacterSize(20);
	text2.setFillColor(sf::Color(237, 205, 61));
	text2.setPosition(x, y + 50);
	text2.setString("Use arrows to control your hero");

	sf::Text text3;
	text3.setFont(font);
	text3.setCharacterSize(20);
	text3.setFillColor(sf::Color(237, 205, 61));
	text3.setPosition(x, y + 100);
	text3.setString("Use LShift to jump through walls");

	sf::Text text4;
	text4.setFont(font);
	text4.setCharacterSize(20);
	text4.setFillColor(sf::Color(237, 205, 61));
	text4.setPosition(x, y + 150);
	text4.setString("Use Space to plant bombs");

	sf::Text text5;
	text5.setFont(font);
	text5.setCharacterSize(20);
	text5.setFillColor(sf::Color(237, 205, 61));
	text5.setPosition(x, y + 200);
	text5.setString("RCtrl - Save, RShift - Load");

	gameWindow.draw(text);
	gameWindow.draw(text2);
	gameWindow.draw(text3);
	gameWindow.draw(text4);
	gameWindow.draw(text5);
}

void Display::drawGame(sf::RenderWindow& gameWindow, Player* player) {
	displayField(gameWindow);
	displayItems(gameWindow);
	displayCreatures(gameWindow);
	displayBottomStats(gameWindow, player);
}

void Display::drawEndMenu(sf::RenderWindow& gameWindow) {
	int x = windowSizeX / 4;
	int y = windowSizeY / 2;
	sf::Text text;
	sf::Font font;

	font.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\statsFont.otf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color(237, 205, 61));
	text.setPosition(x, y);
	text.setString("Well Played!");
	gameWindow.draw(text);
}