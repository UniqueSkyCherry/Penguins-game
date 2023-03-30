#pragma once

#include "structures.h"


/*
* Calculates how risky the move is, based on fields
* in 3-floes radius. Works in autonomous mode only.
*
* @param newGame
*        information about the game (game structure)
* @param board
*        game board
* @param x
*        x-coordinate of currently checked floe
* @param y
*        y-coordinate of currently checked floe
* @param penguinNumber
*        penguin ID for which function calculates risk
*
* @return riskIndex
*         calculated risk
*/

int calculateRisk(game, floe**, int, int, int);


/*
* Calculates how good the move is (without taking risk
* into account), based on fields in 3-floes radius.
* Works in autonomous mode only.
*
* @param newGame
*        information about the game (game structure)
* @param board
*        game board
* @param x
*        x-coordinate of currently checked floe
* @param y
*        y-coordinate of currently checked floe
* @param penguinNumber
*        penguin ID for which function calculates opportunity
*
* @return opportunityIndex
*         calculated opportunity index
*/

int calculateOpportunities(game, floe**, int, int, int);


/*
* Looks for best floe for a penguin in every direction from
* its current position. Works in autonomous mode only.
*
* @param newGame
*        information about the game (game structure)
* @param board
*        game board
* @param currentx
*        x-coordinate of current floe
* @param currenty
*        y-coordinate of current floe
* @param penguinNumber
*        penguin ID for which function looks for a floe
*
* @return bestFloe
*        structure with the data about floe that was choosen
*        as the best one for current penguin
*/

struct smartlyChosenCoords chooseBestFloe(game, floe**, int, int, int);


/*
* Chooses a penguin with best move and moves it.
*
* @param newGame
*        information about the game (game structure)
* @param board
*        game board
*/

void smartlyChooseAndMovePenguin(game*, floe**);
