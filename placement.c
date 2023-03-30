#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "structures.h"
#include "input-output.h"
#include "checks.h"
#include "placement.h"


int placePenguinInPlacementPhase(game* newGame, floe** board, int currentPlayerNumber)
{
#ifndef AUTONOMOUS

	penguin* choosenPenguin = &(newGame->Players[currentPlayerNumber].penguins[PENGUINS - newGame->Players[currentPlayerNumber].penguinsLeft]);

	while (readCoords(&(choosenPenguin->x), &(choosenPenguin->y), newGame->Players[currentPlayerNumber].ID) != 1)
	{
		printf("Coordinates not correct!\n");
	}

#else
	//placing penguins in autonomous modeis done randomly
	srand((unsigned int)time(NULL));
	penguin* choosenPenguin = &(newGame->Players[0].penguins[newGame->Players[0].penguinsLeft - 1]);
	choosenPenguin->y = rand() % newGame->m;
	choosenPenguin->x = rand() % newGame->n;

#endif

	while (isPlacementCorrectInPlacementPhase(*newGame, board, choosenPenguin->x, choosenPenguin->y) != 1)
	{
#ifdef AUTONOMOUS
		//program will try choosing coordinates until it gets to a 1-fish floe
		choosenPenguin->y = rand() % newGame->m;
		choosenPenguin->x = rand() % newGame->n;
#else
		return 0;
#endif
	}
	//setting a penguin on a floe, changing all the neccessary parameters
	newGame->Players[currentPlayerNumber].score++;
	board[choosenPenguin->y][choosenPenguin->x].numberOfFish = 0;
	board[choosenPenguin->y][choosenPenguin->x].penguinID = choosenPenguin->ID;
	board[choosenPenguin->y][choosenPenguin->x].penguinsOwnerID = newGame->Players[currentPlayerNumber].ID;
	newGame->Players[currentPlayerNumber].penguinsLeft--;

	return 1;
}

int placePenguinInMovementPhase(game* newGame, floe** board, int currentPlayerNumber)
{
	//temporary coordinates - in case a penguin cannot be moved 
	int tempx, tempy;

	int choosenPenguinID = 0;
	while ((choosenPenguinID = whichPenguinToMove(currentPlayerNumber)) == 0)
	{
		printf("Cannot choose this penguin!\n");
	}

	penguin* choosenPenguin = &(newGame->Players[currentPlayerNumber].penguins[choosenPenguinID - 1]);

	while (readCoords(&tempx, &tempy, newGame->Players[currentPlayerNumber].ID) != 1)
	{
		printf("Coordinates not correct!\n");
	}

	if (isPlacementCorrectInMovementPhase(*newGame, board, tempx, tempy, currentPlayerNumber, choosenPenguinID - 1) != 1)
		return 0;

	//clearing previous floe
	board[choosenPenguin->y][choosenPenguin->x].penguinsOwnerID = 0;
	board[choosenPenguin->y][choosenPenguin->x].penguinID = 0;

	//changing penguin's coordinates
	choosenPenguin->x = tempx;
	choosenPenguin->y = tempy;

	//adding score and setting number of fish and player and penguin ID on current floe
	newGame->Players[currentPlayerNumber].score += board[tempy][tempx].numberOfFish;
	board[tempy][tempx].numberOfFish = 0;
	board[tempy][tempx].penguinID = choosenPenguinID;
	board[tempy][tempx].penguinsOwnerID = newGame->Players[currentPlayerNumber].ID;

	return 1;
}
