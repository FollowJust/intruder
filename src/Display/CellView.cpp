#include "CellView.h"

CellView::CellView() {

	startTexture.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\startTexture.png");
	finishTexture.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\finishTexture.png");

    floorTexture.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\floorTexture.png");

    wallTexture.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\wallTexture.png");

	bombPlantedTexture.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\bombPlantedTexture.png");
	datacenterTexture.loadFromFile("H:\\VisualProjects\\OOP_game\\src\\Assets\\datacenterTexture.png");

}

void CellView::setCellType(CellType cellType) {
    this->cellType = cellType;
}

sf::RectangleShape CellView::getRectShape(){
	
	rectangle = sf::RectangleShape(sf::Vector2f(rectSize, rectSize));
	switch (cellType){

	case CellType::START:
		rectangle.setTexture(&startTexture);
		break;

	case CellType::FINISH:
		rectangle.setTexture(&finishTexture);
		break;

	case CellType::WALL:
		rectangle.setTexture(&wallTexture);
		break;

	case CellType::BOMBPLANTED:
		rectangle.setTexture(&bombPlantedTexture);
		break;

	case CellType::DATACENTER:
		rectangle.setTexture(&datacenterTexture);
		break;

	case CellType::PASS:
		rectangle.setTexture(&floorTexture);
		break;

	default:
		break;
	}

	return rectangle;
}