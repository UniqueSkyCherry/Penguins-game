#pragma once

#include "structures.h"


/*
* Checks if there's enough 1-fish floes on board in interactive mode
* and places more if needed.
*
* @param  newGame
*         information about the game (game structure)
* @param  board
*         game board
*/

void isThereEnoughOneFishFloes(game, floe**);


/*
* Checks if the board was written correctly.
*
* @param  newGame
*         information about the game (game structure)
* @param  inputboard
*         input board file
*
* @return {@code 1} if board is correct, {@code 0} otherwise
*/

int isBoardCorrect(game, FILE*);


/*
* Checks if the players' info was written correctly.
*
* @param  newGame
*         information about the game (game structure)
* @param  inputboard
*         input board file
*
* @return {@code 1} if player's info section is correct, {@code 0} otherwise
*/

int checkPlayerInfoInFile(game*, FILE*);


/*
* Checks for any errors in floes.
*
* @param  newGame
*         information about the game (game structure)
* @param  inputboard
*         input board file
* @param  phase
*         number indicating which phase is currently played (only
*         in autonomous mode)
*
* @return {@code 1} if all floes are correct, {@code 0} otherwise
*/

int checkFloesCorrectness(game*, floe**, int);
