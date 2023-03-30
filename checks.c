#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "checks.h"
#include "structures.h"


int checkForCorrectDataFormat(char* input)
{
	int spaceCount = 0;
	for (int i = 0; i < (int)strlen(input); i++)
		if ((isdigit(input[i]) == 0 && input[i] != ' ' && input[i] != '\n') || spaceCount > 1)
			return 0;
		else if (input[i] == ' ')
			spaceCount++;

	return 1;
}


int isANumber(char* input)
{
	for (int i = 0; i < (int)strlen(input); i++)
		if ((isdigit(input[i]) == 0 && input[i] != '\n'))
			return 0;

	return 1;
}


int isPlacementCorrectInPlacementPhase(game newGame, floe** board, int x, int y)
{
	if (x < 0 || y < 0 || y >= newGame.m || x >= newGame.n || board[y][x].numberOfFish != 1 || board[y][x].penguinID != 0)
		return 0;

	return 1;
}


int isPlacementCorrectInMovementPhase(game newGame, floe** board, int xdestination, int ydestination, int currentPlayerNumber, int currentPenguin)
{
	int a, b;
#ifdef AUTONOMOUS
	//currentPlayerNumber -= 1;
#endif

	if (
		newGame.Players[currentPlayerNumber].ID != newGame.Players[currentPlayerNumber].ID ||
		ydestination >= newGame.m || xdestination >= newGame.n || ydestination < 0 || xdestination < 0 ||
		(ydestination != newGame.Players[currentPlayerNumber].penguins[currentPenguin].y && xdestination != newGame.Players[currentPlayerNumber].penguins[currentPenguin].x) ||
		(ydestination == newGame.Players[currentPlayerNumber].penguins[currentPenguin].y && xdestination == newGame.Players[currentPlayerNumber].penguins[currentPenguin].x) ||
		board[ydestination][xdestination].numberOfFish == 0 ||
		board[ydestination][xdestination].penguinID != 0
		)
		return 0;

	//checking for any gaps or penguins in current penguin's way
	if (ydestination != newGame.Players[currentPlayerNumber].penguins[currentPenguin].y)
	{
		if (newGame.Players[currentPlayerNumber].penguins[currentPenguin].y > ydestination)
		{
			a = newGame.Players[currentPlayerNumber].penguins[currentPenguin].y;
			b = ydestination;
		}
		else
		{
			b = newGame.Players[currentPlayerNumber].penguins[currentPenguin].y + 1;
			a = ydestination + 1;
		}

		for (b; b < a; b++)
			if (board[b][xdestination].numberOfFish == 0 || board[b][xdestination].penguinID != 0)
				return 0;
	}
	else
	{
		if (newGame.Players[currentPlayerNumber].penguins[currentPenguin].x > xdestination) {
			a = newGame.Players[currentPlayerNumber].penguins[currentPenguin].x;
			b = xdestination;
		}
		else
		{
			b = newGame.Players[currentPlayerNumber].penguins[currentPenguin].x + 1;
			a = xdestination + 1;
		}

		for (b; b < a; b++)
			if (board[ydestination][b].numberOfFish == 0 || board[ydestination][b].penguinID != 0)
				return 0;
	}

	return 1;
}


int anyMovesLeftForAPenguin(game newGame, floe** board, int currentPenguinNumber, int currentPlayerNumber)
{
	int x = newGame.Players[currentPlayerNumber].penguins[currentPenguinNumber].x;
	int y = newGame.Players[currentPlayerNumber].penguins[currentPenguinNumber].y;

	//checking if a penguin has a move to at least 1 floe in any direction from its current position
	if (
		isPlacementCorrectInMovementPhase(newGame, board, x + 1, y, currentPlayerNumber, currentPenguinNumber) ||
		isPlacementCorrectInMovementPhase(newGame, board, x - 1, y, currentPlayerNumber, currentPenguinNumber) ||
		isPlacementCorrectInMovementPhase(newGame, board, x, y + 1, currentPlayerNumber, currentPenguinNumber) ||
		isPlacementCorrectInMovementPhase(newGame, board, x, y - 1, currentPlayerNumber, currentPenguinNumber)
		)
		return 1;

	return 0;
}


int isThereAnyPenguinWithMoves(game newGame, floe** board, int currentPlayerNumber)
{
#ifdef AUTONOMOUS
	for (int i = 0; i < newGame.numberOfPenguins; i++)
#else
	for (int i = 0; i < PENGUINS; i++)
#endif
		newGame.Players[currentPlayerNumber].penguins[i].anyMovesLeft = anyMovesLeftForAPenguin(newGame, board, i, currentPlayerNumber);

#ifdef AUTONOMOUS
	for (int i = 0; i < newGame.numberOfPenguins; i++)
#else
	for (int i = 0; i < PENGUINS; i++)
#endif
		if (newGame.Players[currentPlayerNumber].penguins[i].anyMovesLeft == 1)
			return 1;

	return 0;
}
