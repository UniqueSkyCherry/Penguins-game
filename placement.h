#pragma once

/**
* Tries to place a penguin on desired floe in placement phase by using
* {@code readCoords} and {@code isPlacementCorrectInPlacementPhase}
* functions and adds points to player's total score, removes fish from
* the choosen floe and sets appropriate values in floe structure.
*
* @param  newGame
*         information about the game (game structure)
* @param  board
*         game board
* @param  currentPlayer
*         information about player who is currently playing
*
* @return {@code 1} if a penguin can be placed on desired floe, {@code 0} otherwise
*
* @see    #readCoords(int, int)
* @see    #isPlacementCorrectInPlacementPhase(int, int, int, int, int)
*/

int placePenguinInPlacementPhase(game*, floe**, int);


/**
*Tries to place a penguin on desired floe in movement phase by using
* {@code readCoords} and {@code isPlacementCorrectInMovementPhase} functions and adds
* points to player's total score, removes fish from floe and sets
* appropriate values in both previous and current floe structures.
* Works only in interactive mode.
*
* @param  newGame
*         information about the game (game structure)
* @param  **board
*         game board
* @param  *currentPlayer
*         information about player who is currently playing
*
* @return {@code 1} if a penguin can be moved to a desired floe,
*         {@code 0} otherwise
*
* @see    #readCoords(int, int)
* @see    #isPlacementCorrectInMovementPhase(int, int, int, int, int)
*/

int placePenguinInMovementPhase(game*, floe**, int);
