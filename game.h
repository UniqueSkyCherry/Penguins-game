#pragma once

/**
* Creates board: in interactive mode generates it, in autonomous:
* copies the data from file.
*
* @param  newGame
*         information about the game (game structure)
* @param  newBoard
*         game board
* @param  boardfile
*         input board file (only in autonomous mode)
* @param  phase
*         number indicating in which phase is the game currently
*         (only in autonomous mode)
* @retun
*/

int createBoard(game*, floe***
#ifdef AUTONOMOUS
	, FILE*, int
#endif
);


/**
* Frees the memory taken by the board.
*
* @param  newGame
*         information about the game (game structure)
* @param  board
*         game board
*/

void freeBoard(game, floe**);


/*
* Generates penguins dynamically.
*
* @param  newGame
*         information about the game (game structure)
* @param  numberOfPenguins
*         number of penguins a player have
* @param  playerID
*         current player's ID
*/

void generatePenguins(game*, int, int);


/**
* Switches current player number to the other player's number.
*
* @param  currentPlayerNumber
*         the number used to identify current player
*
*/

void switchPlayer(int*);


/*
* Finds player's ID in input file.
*
* @param  newGame
*         information about the game (game structure)
* @param  inputboard
*         input board file
*/

void findPlayerID(game*, FILE*);


/*
* Calculates how many penguins a player has.
*
* @param  newGame
*         information about the game (game structure)
* @param  board
*         game board
* @param  currentPlayerNumber
*         current player's number
*
* @return counter
*         number of player's penguins
*/

int howManyPenguinsDoesAPlayerHave(game, floe**, int);


/*
* Finds location of penguins on board.
*
* @param  newGame
*         information about the game (game structure)
* @param  board
*         game board
* @param  currentPlayerNumber
*         current player's number
*/

void findPenguins(game, floe**, int);
