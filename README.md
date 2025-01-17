# Space Invaders ASCII Game

This project is a simple implementation of a Space Invaders-like game using ASCII graphics. The game allows players to control a character and shoot down enemy invaders.

## Project Structure

```
space-invaders
├── src
│   ├── main.cpp        # Entry point of the game
│   ├── game.cpp        # Game logic implementation
│   ├── game.hpp        # Game class declaration
│   ├── player.cpp      # Player character implementation
│   ├── player.hpp      # Player class declaration
│   ├── enemy.cpp       # Enemy invaders implementation
│   ├── enemy.hpp       # Enemy class declaration
│   └── utils
│       ├── graphics.cpp # ASCII graphics utility functions
│       └── graphics.hpp # Graphics utility function declarations
├── Makefile             # Build instructions
└── README.md            # Project documentation
```

## Building the Project

To build the project, navigate to the project directory and run the following command:

```
make
```

This will compile the source files and create the executable.

## Running the Game

After building the project, you can run the game using the following command:

```
./space-invaders
```

## Gameplay

- Use the arrow keys to move the player character.
- Press the spacebar to shoot at the enemy invaders.
- The objective is to eliminate all enemies before they reach the bottom of the screen.

Enjoy the game!