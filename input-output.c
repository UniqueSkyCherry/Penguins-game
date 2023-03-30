#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "structures.h"
#include "checks.h"


int readCoords(int* x, int* y, int currentPlayerID)
{
	char str[255];
	printf("[PLAYER %d] Enter the coordinates x and y: ", currentPlayerID);
	fgets(str, 255, stdin);
	if (checkForCorrectDataFormat(str) == 0)
		return 0;

	if (sscanf(str, "%d %d", x, y) != 2 || *x < 0 || *y < 0)
		return 0;
	return 1;
}


int readBoardDimensions(game* board
#ifdef AUTONOMOUS
	, FILE* boardfile
#endif
)
{
	char str[255];
#ifdef AUTONOMOUS
	rewind(boardfile);
	if (fgets(str, 255, boardfile) == NULL)
		return 0;
#else
	printf("Enter dimension for board (expected data format: x y): ");
	fgets(str, 255, stdin);
#endif
	if (checkForCorrectDataFormat(str) == 0)
		return 0;
	if (sscanf(str, "%d %d", &(board->m), &(board->n)) != 2 || board->m < 1 || board->n < 1 || board->m > 20 || board->n > 20 || ((board->m) * (board->n) <= 6))
		return 0;
	return 1;
}


int showBoard(game newGame, floe** board)
{
	printf("   y\\x");
	for (int i = 0; i < newGame.n; i++)
	{
		//if a number has 1 digit, an extra " " is added
		if (i < 10)
			printf(" ");
		printf("(%d) ", i);
	}

	printf("\n");
	for (int i = 0; i < newGame.m; i++)
	{
		//if a number has 1 digit, an extra " " is added
		if (i < 10)
			printf(" ");
		printf(" (%d) ", i);

		for (int j = 0; j < newGame.n; j++)
		{
			//the way of displaying the floe changes if there's no fish or a penguin there
			if (board[i][j].penguinID != 0)
				printf(" P%d%d ", board[i][j].penguinsOwnerID, board[i][j].penguinID);
			else if (board[i][j].numberOfFish == 0)
				printf("     ");
			else
				printf("  %d  ", board[i][j].numberOfFish);
		}
		printf("\n");
	}
	return 1;
}


int whichPenguinToMove(int currentPlayerNumber)
{
	int choosenPenguin;
	char str[255];

	printf("[PLAYER %d] Which penguin to move? ", currentPlayerNumber + 1);
	fgets(str, 255, stdin);

	for (int i = 0; i < (int)strlen(str); i++)
		if (isdigit(str[i]) == 0 && str[i] != '\n')
			return 0;

	if (sscanf(str, "%d", &choosenPenguin) != 1 || choosenPenguin < 1 || choosenPenguin > PENGUINS)
		return 0;

	return choosenPenguin;
}


void writeGameStateIntoFile(game* newGame, floe** board, FILE* outputboard, FILE* inputboard)
{
	char temp[256];
	int wasThePlayerAddedToTheFile = 0;
	rewind(inputboard);
	fprintf(outputboard, "%d %d\n", newGame->m, newGame->n);
	fgets(temp, sizeof(temp), inputboard);

	//writing board
	for (int i = 0; i < newGame->m; i++)
	{
		fgets(temp, sizeof(temp), inputboard);
		for (int j = 0; j < newGame->n; j++)
		{
			fprintf(outputboard, "%d%d", board[i][j].numberOfFish, board[i][j].penguinsOwnerID);
			if (j != newGame->n - 1)
				fprintf(outputboard, " ");
		}
		fprintf(outputboard, "\n");
	}

	//writing players
	for (int i = 0; i < newGame->numberOfPlayers; i++)
	{
		fgets(temp, sizeof(temp), inputboard);
		if (strncmp(temp, newGame->Players[0].playerName, strlen(newGame->Players[0].playerName)) == 0)
		{
			fprintf(outputboard, "%s %d %d", newGame->Players[0].playerName, newGame->Players[0].ID, newGame->Players[0].score);
			wasThePlayerAddedToTheFile = 1;
			if (i != newGame->numberOfPlayers - 1)
				fprintf(outputboard, "\n");
		}
		else
			fputs(temp, outputboard);
	}

	//adding player info to file if it's not already there
	if (wasThePlayerAddedToTheFile == 0)
	{
		if (newGame->numberOfPlayers > 0)
			fprintf(outputboard, "\n");
		fprintf(outputboard, "%s %d %d", newGame->Players[0].playerName, newGame->Players[0].ID, newGame->Players[0].score);
	}
}
