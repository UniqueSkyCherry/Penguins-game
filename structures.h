#pragma once

#define AUTONOMOUS
#define PENGUINS 3

/**
* Holds information about a penguin.
*/

typedef struct PenguinInfo
{
	int ID;
	int playerID;
	int x, y;
	int anyMovesLeft;
} penguin;


/**
* Holds information about a player.
*/

typedef struct PlayerInfo
{
	int ID;
	char* playerName;
	int score;
	int penguinsLeft;
	penguin* penguins;
	int anyMovesLeftForAnyPenguin;
} player;


/**
* Holds information about a floe.
*/

typedef struct FloeInfo
{
	int numberOfFish;
	int penguinID;
	int penguinsOwnerID;
} floe;


/**
* Holds information about the game: boarddimensions, players, floes.
*/

typedef struct GameInfo
{
	int m, n;
	player Players[2];
	int numberOfPenguins;
	int numberOfPlayers;
} game;
