#include "CreatureView.h"

CreatureView::CreatureView() {
	playerTexture.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\playerTexture.png");
	beatEnemyTexture.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\beatEnemyTexture.png");
	robEnemyTexture.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\robEnemyTexture.png");
	shockEnemyTexture.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\shockEnemyTexture.png");
}


void CreatureView::setCreatureType(CreatureType creatureType){
	
	this->creatureType = creatureType;
}

sf::Sprite CreatureView::getSprite() {
	
	switch (creatureType) {
	case CreatureType::PLAYER:
		creatureSprite.setTexture(playerTexture);
		break;

	case CreatureType::BEATENEMY:
		creatureSprite.setTexture(beatEnemyTexture);
		break;

	case CreatureType::ROBENEMY:
		creatureSprite.setTexture(robEnemyTexture);
		break;

	case CreatureType::SHOCKENEMY:
		creatureSprite.setTexture(shockEnemyTexture);
		break;

	default:
		break;
	}
	
	sf::FloatRect oldFloatRect = creatureSprite.getLocalBounds();
	sf::Vector2f newScale = sf::Vector2f(rectSize / oldFloatRect.width, rectSize / oldFloatRect.height);
	creatureSprite.setScale(newScale);

	return creatureSprite;
}