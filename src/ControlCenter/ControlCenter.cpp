#include "ControlCenter.h"

ControlCenter::ControlCenter() {
	this->gameManager = new GameManager(windowSizeX, windowSizeX, bottomMenuSizeY, rectSize);
    this->caretaker = new Caretaker(this->gameManager);

    startMenuCommand = new StartMenuCommand(this->gameManager);
	startGameCommand = new StartGameCommand(this->gameManager);
    endGameCommand = new EndGameCommand(this->gameManager);

    saveGameCommand = new SaveGameCommand(this->gameManager, this->caretaker);
    loadGameCommand = new LoadGameCommand(this->gameManager, this->caretaker);

	moveUpCommand = new MoveUpCommand(this->gameManager);
    moveDownCommand = new MoveDownCommand(this->gameManager);
    moveLeftCommand = new MoveLeftCommand(this->gameManager);
    moveRightCommand = new MoveRightCommand(this->gameManager);
    bombCommand = new BombCommand(this->gameManager);
    jumpCommand = new JumpCommand(this->gameManager);

    sf::RenderWindow gameWindow(sf::VideoMode(windowSizeX, windowSizeY + bottomMenuSizeY), "Very Cool Game");


	this->runMenu(gameWindow);
}

void ControlCenter::runMenu(sf::RenderWindow& gameWindow) {
    startMenuCommand->execute();
    
    bool startGame = false;

    while (gameWindow.isOpen())
    {
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            switch (event.type)
            {

            case sf::Event::Closed:
                gameWindow.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Enter) {
                    startGame = true;
                }
                break;
            default:
                break;
            }
        }
        gameWindow.clear(sf::Color(55, 54, 66));
        this->gameManager->draw(gameWindow);
        if (startGame) {
            break;
        }
        gameWindow.display();
    }
    if (startGame) {
        runGame(gameWindow);
    }
}

void ControlCenter::runGame(sf::RenderWindow& gameWindow) {
    startGameCommand->execute();

    bool gameEnded = false;

    while (gameWindow.isOpen())
    {
        gameManager->updateState();
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            switch (event.type)
            {

            case sf::Event::Closed:
                gameWindow.close();
                break;
            case sf::Event::KeyPressed:
                keyHandler(event);
                break;
            default:
                break;
            }
        }
        gameWindow.clear(sf::Color(55, 54, 66));
        this->gameManager->draw(gameWindow);
        gameWindow.display();
        if (gameManager->checkGameOver()) {
            gameEnded = true;
            break;
        }
    }
    if (gameEnded) {
        runEndMenu(gameWindow);
    }
}

void ControlCenter::runEndMenu(sf::RenderWindow& gameWindow) {
    endGameCommand->execute();

    bool startGame = false;
    while (gameWindow.isOpen())
    {
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            switch (event.type)
            {

            case sf::Event::Closed:
                gameWindow.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Enter) {
                    startGame = true;
                }
                break;
            default:
                break;
            }
        }
        gameWindow.clear(sf::Color(55, 54, 66));
        this->gameManager->draw(gameWindow);
        if (startGame) {
            break;
        }
        gameWindow.display();
    }
    if (startGame) {
        //gameManager->setState(GameState::Game);
        //startGameCommand->execute();
        //runGame(gameWindow);
    }
}

void ControlCenter::keyHandler(sf::Event event) {
    switch (event.key.code)
    {
    case sf::Keyboard::Up:
        moveUpCommand->execute();
        break;

    case sf::Keyboard::Down:
        moveDownCommand->execute();
        break;

    case sf::Keyboard::Left:
        moveLeftCommand->execute();
        break;

    case sf::Keyboard::Right:
        moveRightCommand->execute();
        break;

    case sf::Keyboard::Space:
        bombCommand->execute();
        break;

    case sf::Keyboard::LShift:
        jumpCommand->execute();
        break;

    case sf::Keyboard::RControl:
        saveGameCommand->execute();
        break;

    case sf::Keyboard::RShift:
        loadGameCommand->execute();
        break;

    default:
        break;
    }
}


ControlCenter::~ControlCenter() {
    if (gameManager) {
        delete gameManager;
    }

    if (caretaker) {
        delete caretaker;
    }

    if (saveGameCommand) {
        delete saveGameCommand;
    }

    if (loadGameCommand) {
        delete loadGameCommand;
    }

    if (startGameCommand) {
        delete startGameCommand;
    }

    if (moveUpCommand) {
        delete moveUpCommand;
    }

    if (moveDownCommand) {
        delete moveDownCommand;
    }

    if (moveLeftCommand) {
        delete moveLeftCommand;
    }

    if (moveRightCommand) {
        delete moveRightCommand;
    }

    if (bombCommand) {
        delete bombCommand;
    }

    if (jumpCommand) {
        delete jumpCommand;
    }
}