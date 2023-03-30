#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "structures.h"
#include "input-output.h"
#include "placement.h"
#include "checks.h"
#include "game.h"
#include "chooseBestField.h"

int main(
#ifdef AUTONOMOUS
	int argc, char** argv
#endif
)
{
#ifdef AUTONOMOUS
	char name[] = "InsertCoolNameHere";
#endif

	floe** board = NULL;
	game newGame;

#ifdef AUTONOMOUS

	switch (argc)
	{
	case 2:
	{
		if (strcmp(argv[1], "name") == 0)
		{
			printf("%s", name);
			return 0;
		}
		else
		{
			printf("Not enought arguments!");
			return 2;
		}
	}
	case 5:
	{
		if (strcmp(argv[1], "phase=placement") == 0)
		{
			FILE* inputboardfile = fopen(argv[3], "r");
			FILE* outputboardfile = fopen(argv[4], "w");

			if (inputboardfile == NULL)
			{
				printf("Input file doesn't exist.");
				fclose(outputboardfile);
				return 2;
			}
			newGame.numberOfPenguins = atoi(argv[2] + 9);

			if (readBoardDimensions(&newGame, inputboardfile) == 0)
			{
				printf("Incorrect board dimensions!");
				fclose(inputboardfile);
				fclose(outputboardfile);
				return 2;
			}

			if (createBoard(&newGame, &board, inputboardfile, 0) == 0)
			{
				printf("Incorrectly generated board!");
				fclose(inputboardfile);
				fclose(outputboardfile);
				return 2;
			}

			newGame.Players[0] =
				(player){
				.ID = 0,
				.playerName = name,
				.score = 0,
				.penguinsLeft = 0,
				.penguins = NULL,
				.anyMovesLeftForAnyPenguin = 1 };

			findPlayerID(&newGame, inputboardfile);

			newGame.Players[0].penguinsLeft = newGame.numberOfPenguins - howManyPenguinsDoesAPlayerHave(newGame, board, 0);

			if (newGame.Players[0].penguinsLeft == 0)
			{
				writeGameStateIntoFile(&newGame, board, outputboardfile, inputboardfile);
				fclose(inputboardfile);
				fclose(outputboardfile);
				freeBoard(newGame, board);
				free(newGame.Players[0].penguins);
				return 1;
			}

			generatePenguins(&newGame, newGame.numberOfPenguins, 1);

			if (placePenguinInPlacementPhase(&newGame, board, 0))
			{
				writeGameStateIntoFile(&newGame, board, outputboardfile, inputboardfile);
				fclose(inputboardfile);
				fclose(outputboardfile);
				freeBoard(newGame, board);
				free(newGame.Players[0].penguins);

				return 0;
			}

			writeGameStateIntoFile(&newGame, board, outputboardfile, inputboardfile);
			fclose(inputboardfile);
			fclose(outputboardfile);
			freeBoard(newGame, board);
			free(newGame.Players[0].penguins);

			printf("Couldn't place a penguin although there are some unplaced left");
			return 3;
		}
		else
		{
			printf("Not enough arguments!");
			return 3;
		}
	}
	case 4:
	{
		if (strcmp(argv[1], "phase=movement") == 0)
		{
			FILE* inputboardfile = fopen(argv[2], "r");
			if (inputboardfile == NULL)
			{
				printf("Input file doesn't exist.");
				return 2;
			}
			FILE* outputboardfile = fopen(argv[3], "w");

			if (readBoardDimensions(&newGame, inputboardfile) == 0)
			{
				printf("Incorrect board dimensions! (line 1)");
				fclose(inputboardfile);
				fclose(outputboardfile);
				return 2;
			}

			if (createBoard(&newGame, &board, inputboardfile, 1) == 0)
			{
				fclose(inputboardfile);
				return 2;
			}

			newGame.Players[0] =
				(player){
				.ID = 0,
				.playerName = name,
				.score = 0,
				.penguinsLeft = 0,
				.penguins = NULL,
				.anyMovesLeftForAnyPenguin = 1 };

			findPlayerID(&newGame, inputboardfile);

			generatePenguins(&newGame, newGame.numberOfPenguins, 1);
			findPenguins(newGame, board, newGame.Players[0].ID);

			if (isThereAnyPenguinWithMoves(newGame, board, 0) == 0)
			{
				writeGameStateIntoFile(&newGame, board, outputboardfile, inputboardfile);
				fclose(inputboardfile);
				fclose(outputboardfile);
				free(newGame.Players[0].penguins);
				return 1;
			}

			smartlyChooseAndMovePenguin(&newGame, board);
			writeGameStateIntoFile(&newGame, board, outputboardfile, inputboardfile);
			fclose(inputboardfile);
			fclose(outputboardfile);
			free(newGame.Players[0].penguins);
			return 0;
		}
		else
		{
			printf("Too many arguments!");
			return 3;
		}
	}
	default:
	{
		printf("Incorrect number of arguments!");
		return 3;
	}
	}

#else

	newGame.Players[0] =
		(player){ .ID = 1, .playerName = NULL, .score = 0, .penguinsLeft = PENGUINS,
		.penguins = NULL, .anyMovesLeftForAnyPenguin = 1 };
	newGame.Players[1] =
		(player){ .ID = 2, .playerName = NULL, .score = 0, .penguinsLeft = PENGUINS,
		.penguins = NULL, .anyMovesLeftForAnyPenguin = 1 };

	generatePenguins(&newGame, 3, 1);
	generatePenguins(&newGame, 3, 2);

	int currentPlayerNumber = 0;


	while (readBoardDimensions(&newGame) != 1)
	{
		printf("Incorrect values of dimensions!\n");
	}

	createBoard(&newGame, &board);
	showBoard(newGame, board);

	printf("\nPlacement phase\nPlace penguins on floes that have 1 fish one them by entering the\ncoordinates of that floe (expected data format: x y).\n");
	printf("Penguins are marked in the following way: Pnm, where n is player ID \nand m is penguin ID.\n\n");

	do
	{
		while (placePenguinInPlacementPhase(&newGame, board, currentPlayerNumber) != 1)
		{
			printf("A penguin cannot be placed here!\n");
		}

		switchPlayer(&currentPlayerNumber);
		//clear screen?
		showBoard(newGame, board);
	} while (newGame.Players[0].penguinsLeft != 0 || newGame.Players[1].penguinsLeft != 0);

	printf("\nMovement phase\nPenguins can move in straight line only, to a floe with fish on it\n(marked by number). Penguin cannot jump over floes with no fish\nor over another penguin.");
	printf("\n(expected data format for coordinates is: x y)\n\n");

	do
	{
		while (placePenguinInMovementPhase(&newGame, board, currentPlayerNumber) != 1)
		{
			printf("A penguin cannot be moved to this floe!\n");
		}

		//clear screen?
		showBoard(newGame, board);

		newGame.Players[0].anyMovesLeftForAnyPenguin = isThereAnyPenguinWithMoves(newGame, board, 0);
		newGame.Players[1].anyMovesLeftForAnyPenguin = isThereAnyPenguinWithMoves(newGame, board, 1);

		if (newGame.Players[1 - currentPlayerNumber].anyMovesLeftForAnyPenguin == 1)
			switchPlayer(&currentPlayerNumber);

	} while (newGame.Players[0].anyMovesLeftForAnyPenguin != 0 || newGame.Players[1].anyMovesLeftForAnyPenguin != 0);

	if (newGame.Players[0].score > newGame.Players[1].score)
		printf("Player 1 won!");
	else if (newGame.Players[0].score < newGame.Players[1].score)
		printf("Player 2 won!");
	else
		printf("Tie!");

	freeBoard(newGame, board);
	free(newGame.Players[0].penguins);
	free(newGame.Players[1].penguins);

	getchar();

	return 0;
#endif
}
