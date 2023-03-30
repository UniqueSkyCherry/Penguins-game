#pragma once

#include "structures.h"

/*
* Checks if the format of coordinates and board dimensions are correct.
*
* @param  input
*         checked input
*
* @return {@code 1} if data format is correct, {@code 0} otherwise
*/

int checkForCorrectDataFormat(char*);


/*
* Checks if given input is a number.
*
* @param  input
*         checked input
*
* @return {@code 1} if it is, {@code 0} otherwise
*/

int isANumber(char* input);


/**
* Checks if a penguin can be placed on a floe with selected coordinates.
*
* <p> The function checks the following conditions: if there's exactly 1 fish and no player
* on the selected floe and if the penguin will be placed within the board.
*
* @param  newGame
*         information about the game (game structure)
* @param  board
*         game board
* @param  x
*         x coordinate of the selected floe
* @param  y
*         y coordinate of the selected floe
*
* @returns {@code 0} if penguin cannot be placed on the selected floe, {@code 1}
*          otherwise
*/

int isPlacementCorrectInPlacementPhase(game, floe**, int, int);


/**
* Checks if a penguin can be moved to a floe with selected coordinates.
*
* <p> The function checks the following conditions: if player is trying
* to move their penguin, if there's fish and no player on the selected floe
* and if the penguin will be moved and the move will be done within the board
* and in straight line.
*
* <p> If the conditions mentioned above are fulfilled, the function will check
* for any gaps or other player's penguins way.
*
* @param  newGame
*         information about the game (game structure)
* @param  board
*         game board
* @param  xdestination
*         x coordinate of the selected floe
* @param  ydestination
*         y coordinate of the selected floe
* @param  currentPlayerNumber
*         current player's number
* @param  currentPenguin
*         number of a penguin that's being moved
*
* @returns {@code false} if penguin cannot be moved to the selected floe, {@code true}
*          otherwise
*/

int isPlacementCorrectInMovementPhase(game, floe**, int, int, int, int);


/**
* Checks if there are any moves left for current player's penguin
* using {@code isPlacementCorrectInMovementPhase} function. If there are no moves
* left, the function will assign 0 in a certain field in a structure
* with penguin data (to be created) so that this penguin will not be
* checked again.
*
* @param  newGame
*         information about the game (game structure)
* @param  board
*         game board
* @param  currentPenguinNumber
*         number of a penguin that's being checked
* @param  currentPlayerNumber
*         current player's number
*
* @return {@code 1} if there are moves for the penguin, {@code 0} otherwise
*
* @see    #isPlacementCorrectInMovementPhase(int, int, int, int, int)
*/

int anyMovesLeftForAPenguin(game, floe**, int, int);


/**
* Checks if any of the player's penguins can make any move.
*
* @param  newGame
*         information about the game (game structure)
* @param  board
*         game board
* @param  currentPlayerNumber
*         current player's number
*
* @return {@code 1} if there is at least 1 penguin that can make moves, {@code 0} otherwise
*/

int isThereAnyPenguinWithMoves(game, floe**, int);
