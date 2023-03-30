#pragma once


/**
* Reads coordinates from the user.
*
* @param  x
*         x coordinate
* @param  y
*         y coordinate
* @param  currentPlayerID
*         ID number of the current player
*
* @return {@code 1} if coordinates were read correctly, {@code 0} otherwise
*/

int readCoords(int*, int*, int);


/**
* Reads board dimensions from the user.
* @param  newGame
*         information about the game (game structure)
* @param  boardfile
*         input board file (only in autonomous mode)
*
* @return {@code 1} if dimensions were read correctly, {@code 0} otherwise
*/

int readBoardDimensions(game* board
#ifdef AUTONOMOUS
	, FILE*
#endif
);


/**
* Displays board on screen, taking into account number of fish and if there's
* a player on that floe.
*
* @param  newGame
*         information about the game (game structure)
* @param  board
*         game board
*
* @return {@code 1} if any problem occurs, {@code 0} otherwise
*/

int showBoard(game, floe**);


/**
* Asks which penguin should be moved and checks if its index
* (given by the player) is correct.
*
* @return {@code indexOfPenguin} if the index is correct,
*         {@code 0} otherwise
*/

int whichPenguinToMove(int);


/*
* Writes game board modified by the program into an output file.
*
* @param  newGame
*         information about the game (game structure)
* @param  board
*         game board
* @param  outputboard
*         output board file (only in autonomous mode)
* @param  inputboard
*         input board file (only in autonomous mode)
*/

void writeGameStateIntoFile(game*, floe**, FILE*, FILE*);
