#include "ItemView.h"

ItemView::ItemView() {

	hpTexture.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\hpTexture.png");
	bombTexture.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\bombTexture.png");
	jumpTexture.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\jumpTexture.png");

}


void ItemView::setItemTypeId(int itemTypeId)
{
	this->itemTypeId = itemTypeId;
}

sf::Sprite ItemView::getSprite() {
	switch (itemTypeId){
	case 0:
		itemSprite.setTexture(hpTexture);
		break;

	case 1:
		itemSprite.setTexture(jumpTexture);
		break;

	case 2:
		itemSprite.setTexture(bombTexture);
		break;

	default:
		break;
	}

	sf::FloatRect oldFloatRect = itemSprite.getLocalBounds();
	sf::Vector2f newScale = sf::Vector2f(rectSize / oldFloatRect.width, rectSize / oldFloatRect.height);
	itemSprite.setScale(newScale);

	return itemSprite;
}