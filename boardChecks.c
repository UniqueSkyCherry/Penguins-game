#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#include "boardChecks.h"
#include "checks.h"
#include "structures.h"


void isThereEnoughOneFishFloes(game newGame, floe** board)
{
	int counter = 0;
	srand((unsigned int)time(NULL));

	//looking for 1-fish floes
	for (int i = 0; i < newGame.m; i++)
		for (int j = 0; j < newGame.n; j++)
			if (board[i][j].numberOfFish == 1)
				counter++;

	//changing number of fish on floes so that there are enough of them 
	while (counter < 2 * PENGUINS)
	{
		int a = rand() % newGame.m;
		int b = rand() % newGame.n;

		if (board[a][b].numberOfFish != 1)
		{
			board[a][b].numberOfFish = 1;
			counter++;
		}
	}
}

int isBoardCorrect(game newGame, FILE* inputboard)
{
	char temp[256];
	rewind(inputboard);

	fgets(temp, sizeof(temp), inputboard);

	for (int j = 0; j < newGame.m; j++)
	{
		if (fgets(temp, sizeof(temp), inputboard) == NULL)
			return 0;
		//going through the lines where board is supposed to be
		if ((int)strlen(temp) == 3 * newGame.n || (int)strlen(temp) == 3 * newGame.n - 1)
			//checking if the rows have correct length
		{
			for (int i = 0; i < 3 * newGame.n - 1; i++)
				//checking if the rows have correct format
			{
				if ((i % 3 == 2 && temp[i] != ' ') || (i % 3 != 2 && isdigit(temp[i]) == 0))
				{
					printf("Error in line %d\n", j + 1);
					return 0;
				}
			}
		}
		else
		{
			printf("Error in board size!\n");
			return 0;
		}
	}

	while (feof(inputboard) == 0)
		//checking if the board is followed by players info only
	{
		fgets(temp, sizeof(temp), inputboard);
		if (isdigit(temp[0]) != 0 && isdigit(temp[1]) != 0 && temp[2] != ' ' && isdigit(temp[3]) == 0 && isdigit(temp[4]) == 0)
			//checking first 5 characters as it's impossible to have a combination of "two digits (space) two digits" in player line)
			return 0;
	}

	return 1;
}

int checkPlayerInfoInFile(game* newGame, FILE* inputboard)
{
	char temp[255];
	char* str;
	int fieldCount;
	int playerCount = 0;

	rewind(inputboard);
	for (int i = 0; i < newGame->m + 1; i++)
		fgets(temp, sizeof(temp), inputboard);

	while (feof(inputboard) == 0)
	{
		fieldCount = 1;
		fgets(temp, sizeof(temp), inputboard);
		str = strtok(temp, " ");
		while (str != NULL)
		{
			switch (fieldCount)
			{
			case 1: break;
			case 2:
			{
				if (strlen(str) != 1 || (isdigit(str[0]) == 0 || str[0] - '0' > 9 || str[0] - '0' < 1))
				{
					printf("Error in players' information!\n");
					return 0;
				}
				break;
			}
			case 3:
			{
				if (isANumber(str) == 0)
				{
					printf("Error in player %d's information!\n", playerCount + 1);
					return 0;
				}
				break;
			}
			default:
			{
				printf("Error in player %d's information!\n", playerCount + 1);
				return 0;
				break;
			}
			}

			str = strtok(NULL, " ");
			fieldCount++;
		}
		playerCount++;
	}

	newGame->numberOfPlayers = playerCount;

	return 1;
}

int checkFloesCorrectness(game* newGame, floe** board, int phase)
{
	int numberOfPlayersPenguins[9] = { 0 };
	int k;

	for (int i = 0; i < newGame->m; i++)
		for (int j = 0; j < newGame->n; j++)
		{
			if (board[i][j].penguinsOwnerID != 0 && board[i][j].numberOfFish != 0)
			{
				printf("Incorrect data in one of the floes!\n");
				return 0;
			}

			if (board[i][j].penguinsOwnerID == 0)
				continue;

			if (board[i][j].penguinsOwnerID < 0 || board[i][j].penguinsOwnerID > 9)
			{
				printf("Incorrect data in one of the floes!\n");
				return 0;
			}

			k = board[i][j].penguinsOwnerID;
			numberOfPlayersPenguins[k - 1]++;
		}

	if (phase == 1)
	{
		for (int i = 1; i < newGame->numberOfPlayers; i++)
			if (numberOfPlayersPenguins[0] != numberOfPlayersPenguins[i])
			{
				printf("Players don't have the same amount of penguins!\n");
				return 0;
			}
		newGame->numberOfPenguins = numberOfPlayersPenguins[0];
	}

	return 1;
}