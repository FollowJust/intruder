#ifndef CONTROL_CENTER_H
#define CONTROL_CENTER_H

#include "SFML/Graphics.hpp"

#include "../Command/GameCommands/StartMenuCommand.h"
#include "../Command/GameCommands/StartGameCommand.h"
#include "../Command/GameCommands/EndGameCommand.h"

#include "../Command/GameCommands/SaveLoadCommands/SaveGameCommand.h"
#include "../Command/GameCommands/SaveLoadCommands/LoadGameCommand.h"

#include "../Command/MoveCommands/MoveUpCommand.h"
#include "../Command/MoveCommands/MoveDownCommand.h"
#include "../Command/MoveCommands/MoveLeftCommand.h"
#include "../Command/MoveCommands/MoveRightCommand.h"
#include "../Command/ItemCommands/JumpCommand.h"
#include "../Command/ItemCommands/BombCommand.h"

class ControlCenter {
private:
	int windowSizeX = 800;
	int windowSizeY = 800;
	int rectSize = 50;
	int bottomMenuSizeY = 50;

	GameManager* gameManager;
	Caretaker* caretaker;

	Command* startMenuCommand;
	Command* startGameCommand;
	Command* endGameCommand;

	Command* saveGameCommand;
	Command* loadGameCommand;

	Command* moveUpCommand;
	Command* moveDownCommand;
	Command* moveLeftCommand;
	Command* moveRightCommand;
	Command* bombCommand;
	Command* jumpCommand;

	void runMenu(sf::RenderWindow& gameWindow);
	void runGame(sf::RenderWindow& gameWindow);
	void runEndMenu(sf::RenderWindow& gameWindow);

	void keyHandler(sf::Event event);
public:
	ControlCenter();
	~ControlCenter();
};

#endif
