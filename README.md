# Intruder
## _A Simple SFML Game Project_
<img src="https://github.com/FollowJust/intruder/blob/main/images/gamescreen.png" width="400">

This was originally a part of my university coursework, but then I've decided to load post it here.

- Graphics - [SFML](https://www.sfml-dev.org/)
- Visual Studio 19
- A lot of coffee

## Features

- Randomly-generated labyrinths
- Intelligent ~~or not really~~ enemies
- 10 programming patterns

## Patterns

There is a list of patterns that we were used throughout the code and their usage. Most of them are implemented correctly while some may seem a bit odd.

- [Singleton](https://en.wikipedia.org/wiki/Singleton_pattern) - to have only one object of Field class.
- [Iterator](https://en.wikipedia.org/wiki/Iterator_pattern) - to iterate over the Field object.
- [Abstract Factory](https://en.wikipedia.org/wiki/Abstract_factory_pattern) - for creating the items.
- [Strategy](https://en.wikipedia.org/wiki/Strategy_pattern) - to change how player interact with the items during the game.
- [Observer](https://en.wikipedia.org/wiki/Observer_pattern) - to make logs.
- [Bridge](https://en.wikipedia.org/wiki/Bridge_pattern) - to separate Logging classes abstractions and implementations.
- [Commands](https://en.wikipedia.org/wiki/Command_pattern) - for performing game actions.
- [Facade](https://en.wikipedia.org/wiki/Facade_pattern) - for separating game logic class.
- [State](https://en.wikipedia.org/wiki/State_pattern) - to change turns between player and enemies.
- [Memento](https://en.wikipedia.org/wiki/Memento_pattern) - to make a Save/Load function.

## Algorithms

- [Eller's Algorithm](http://www.neocomputer.org/projects/eller.html) - used to generate random labyrinths.
- [Lee Algorithm](https://en.wikipedia.org/wiki/Lee_algorithm) - used to find the optimal path for the enemies.

## Screenshots

![Game Progress Screenshot 1](/images/game_process1.png =200x200)]
![Game Progress Screenshot 2](/images/game_process2.png =200x200)]
![Game Progress Screenshot 3](/images/game_process3.png =200x200)]


### _Different sizes, different ways..._
![Game Progress Screenshot 4](/images/game_random_1.png =200x200)]
![Game Progress Screenshot 5](/images/game_random_2.png =200x200)]
![Game Progress Screenshot 6](/images/game_random_3.png =200x200)]
![Game Progress Screenshot 7](/images/game_random_4.png =200x200)]
