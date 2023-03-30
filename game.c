#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "structures.h"
#include "game.h"
#include "boardChecks.h"


int createBoard(game* newGame, floe*** newBoard
#ifdef AUTONOMOUS
	, FILE* boardfile, int phase
#endif
)
{
	srand((unsigned int)time(NULL));

#ifdef AUTONOMOUS
	if (isBoardCorrect(*newGame, boardfile) == 0)
		return 0;
	if (checkPlayerInfoInFile(newGame, boardfile) == 0)
		return 0;
	rewind(boardfile);
	char row[60];
	fgets(row, sizeof(row), boardfile);
#endif

	//generating dynamic array
	* newBoard = malloc((newGame->m) * sizeof(floe*));
	for (int i = 0; i < newGame->m; i++)
	{

#ifdef AUTONOMOUS
		fgets(row, sizeof(row), boardfile);
#endif

		(*newBoard)[i] = malloc((newGame->n) * sizeof(floe));
		for (int j = 0; j < newGame->n; j++)
		{

#ifdef AUTONOMOUS
			//filling the board with the data from the file
			(*newBoard)[i][j].numberOfFish = row[3 * j] - '0';
			(*newBoard)[i][j].penguinID = 0;
			(*newBoard)[i][j].penguinsOwnerID = row[3 * j + 1] - '0';
#else
			//setting initial values and generating pseudorandom number of fish
			(*newBoard)[i][j].numberOfFish = rand() % 4;
			(*newBoard)[i][j].penguinID = 0;
			(*newBoard)[i][j].penguinsOwnerID = 0;
#endif

		}
	}

#ifdef AUTONOMOUS
	if (checkFloesCorrectness(newGame, *newBoard, phase) == 0)
		return 0;
#else
	isThereEnoughOneFishFloes(*newGame, *newBoard);
#endif
	return 1;
}


void freeBoard(game newGame, floe** newBoard)
{
	for (int i = 0; i < newGame.m; i++)
		free(newBoard[i]);
	free(newBoard);
}


void generatePenguins(game* newGame, int numberOfPenguins, int playerID)
{
	newGame->Players[playerID - 1].penguins = malloc(sizeof(penguin) * numberOfPenguins);
	for (int i = 0; i < numberOfPenguins; i++)
	{
		newGame->Players[playerID - 1].penguins[i].anyMovesLeft = 1;
		newGame->Players[playerID - 1].penguins[i].ID = i + 1;
		newGame->Players[playerID - 1].penguins[i].playerID = playerID;
		newGame->Players[playerID - 1].penguins[i].x = -1;
		newGame->Players[playerID - 1].penguins[i].y = -1;
	}
}


void switchPlayer(int* currentPlayerNumber)
{
	if (*currentPlayerNumber == 0)
		*currentPlayerNumber = 1;
	else if (*currentPlayerNumber == 1)
		*currentPlayerNumber = 0;
}


void findPlayerID(game* newGame, FILE* inputboard)
{
	char temp[256];
	int counter = 0;
	rewind(inputboard);
	//first line
	fgets(temp, sizeof(temp), inputboard);

	//going through board
	for (int i = 0; i < newGame->m; i++)
		fgets(temp, sizeof(temp), inputboard);

	//looking for players
	while (feof(inputboard) == 0)
	{
		fgets(temp, sizeof(temp), inputboard);
		counter++;
		if (strncmp(temp, newGame->Players[0].playerName, strlen(newGame->Players[0].playerName)) == 0)
		{
			newGame->Players[0].ID = temp[strlen(newGame->Players[0].playerName) + 1] - '0';
			newGame->Players[0].score = atoi(temp + strlen(newGame->Players[0].playerName) + 3);
			return;
		}
	}
	newGame->Players[0].ID = counter + 1;
}


int howManyPenguinsDoesAPlayerHave(game newGame, floe** board, int currentPlayerNumber)
{
	int counter = 0;
	for (int i = 0; i < newGame.m; i++)
		for (int j = 0; j < newGame.n; j++)
			if (board[i][j].penguinsOwnerID == newGame.Players[currentPlayerNumber].ID)
				counter++;

	return counter;
}


void findPenguins(game newGame, floe** board, int currentPlayerNumber)
{
	int counter = 1;
	for (int i = 0; i < newGame.m; i++)
		for (int j = 0; j < newGame.n; j++)
			if (board[i][j].penguinsOwnerID == currentPlayerNumber)
			{
				newGame.Players[0].penguins[newGame.numberOfPenguins - counter].x = j;
				newGame.Players[0].penguins[newGame.numberOfPenguins - counter].y = i;
				counter++;
			}

}
