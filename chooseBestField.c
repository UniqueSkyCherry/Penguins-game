#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "checks.h"
#include "chooseBestField.h"


typedef struct smartlyChosenCoords
{
	int x, y;
	int goodnessIndex, risk, opportunity;
} smartCoords;

int calculateRisk(game newGame, floe** board, int x, int y, int penguinNumber)
{
	//risk index is based on how many flows are currently blocked and how far from desired floe
	int riskIndex = 0;
	for (int j = 3; j > 0; j--)
	{
		if (x + j < newGame.n && isPlacementCorrectInMovementPhase(newGame, board, x + j, y, 0, penguinNumber) == 0 && board[y][x + j].penguinsOwnerID != newGame.Players[0].ID)
			riskIndex += 3 - j;
		if (x - j >= 0 && isPlacementCorrectInMovementPhase(newGame, board, x - j, y, 0, penguinNumber) == 0 && board[y][x - j].penguinsOwnerID != newGame.Players[0].ID)
			riskIndex += 3 - j;
		if (y + j < newGame.m && isPlacementCorrectInMovementPhase(newGame, board, x, y + j, 0, penguinNumber) == 0 && board[y + j][x].penguinsOwnerID != newGame.Players[0].ID)
			riskIndex += 3 - j;
		if (y - j >= 0 && isPlacementCorrectInMovementPhase(newGame, board, x, y - j, 0, penguinNumber) == 0 && board[y - j][x].penguinsOwnerID != newGame.Players[0].ID)
			riskIndex += 3 - j;
		if (x + j >= newGame.n || x - j < 0 || y + j >= newGame.m || y - j < 0)
			riskIndex += 3;
	}
	return riskIndex;
}

int calculateOpportunities(game newGame, floe** board, int x, int y, int penguinNumber)
{
	//opportunity index is based on the number of fish on checked floe and number of fish 3 floes in each direction of the checked one
	int opportunityIndex = board[y][x].numberOfFish * 4;
	for (int j = 3; j > 0; j--)
	{
		if (isPlacementCorrectInMovementPhase(newGame, board, x + j, y, 0, penguinNumber) == 1 && board[y][x + j].penguinsOwnerID != newGame.Players[0].ID)
			opportunityIndex += board[y][x + j].numberOfFish + 2;
		if (isPlacementCorrectInMovementPhase(newGame, board, x - j, y, 0, penguinNumber) == 1 && board[y][x - j].penguinsOwnerID != newGame.Players[0].ID)
			opportunityIndex += board[y][x - j].numberOfFish + 2;
		if (isPlacementCorrectInMovementPhase(newGame, board, x, y + j, 0, penguinNumber) == 1 && board[y + j][x].penguinsOwnerID != newGame.Players[0].ID)
			opportunityIndex += board[y + j][x].numberOfFish + 2;
		if (isPlacementCorrectInMovementPhase(newGame, board, x, y - j, 0, penguinNumber) == 1 && board[y - j][x].penguinsOwnerID != newGame.Players[0].ID)
			opportunityIndex += board[y - j][x].numberOfFish + 2;
	}
	return opportunityIndex;
}

smartCoords chooseBestFloe(game newGame, floe** board, int currentx, int currenty, int penguinNumber) {
	smartCoords floeGoodness[80];
	for (int i = 0; i < 38; i++) {
		floeGoodness[i].x = -1;
		floeGoodness[i].y = -1;
		floeGoodness[i].goodnessIndex = -100;
		floeGoodness[i].risk = 100;
		floeGoodness[i].opportunity = -100;
	}

	if (newGame.Players[0].penguins[penguinNumber].anyMovesLeft == 0) return floeGoodness[0];

	smartCoords bestFloe;
	int j = 0; //index used to navigate in floeGoodness array

	//checking goodness of floes in x-axis
	for (int i = currentx - 1; i >= 0; i--) {
		if (isPlacementCorrectInMovementPhase(newGame, board, i, currenty, 0, penguinNumber) == 0)
			break;
		else {
			floeGoodness[j].x = i;
			floeGoodness[j].y = currenty;
			floeGoodness[j].opportunity = calculateOpportunities(newGame, board, floeGoodness[j].x, floeGoodness[j].y, penguinNumber);
			floeGoodness[j].risk = calculateRisk(newGame, board, floeGoodness[j].x, floeGoodness[j].y, penguinNumber);
			floeGoodness[j].goodnessIndex = floeGoodness[j].opportunity - floeGoodness[j].risk;
			j++;
		}
	}

	for (int i = currentx + 1; i < newGame.n; i++) {
		if (isPlacementCorrectInMovementPhase(newGame, board, i, currenty, 0, penguinNumber) == 0)
			break;
		else {
			floeGoodness[j].x = i;
			floeGoodness[j].y = currenty;
			floeGoodness[j].opportunity = calculateOpportunities(newGame, board, floeGoodness[j].x, floeGoodness[j].y, penguinNumber);
			floeGoodness[j].risk = calculateRisk(newGame, board, floeGoodness[j].x, floeGoodness[j].y, penguinNumber);
			floeGoodness[j].goodnessIndex = floeGoodness[j].opportunity - floeGoodness[j].risk;
			j++;
		}
	}

	//checking goodness of floes in y-axis
	for (int i = currenty - 1; i >= 0; i--) {
		if (isPlacementCorrectInMovementPhase(newGame, board, currentx, i, 0, penguinNumber) == 0)
			break;
		else {
			floeGoodness[j].x = currentx;
			floeGoodness[j].y = i;
			floeGoodness[j].opportunity = calculateOpportunities(newGame, board, floeGoodness[j].x, floeGoodness[j].y, penguinNumber);
			floeGoodness[j].risk = calculateRisk(newGame, board, floeGoodness[j].x, floeGoodness[j].y, penguinNumber);
			floeGoodness[j].goodnessIndex = floeGoodness[j].opportunity - floeGoodness[j].risk;
			j++;
		}
	}

	for (int i = currenty + 1; i < newGame.m; i++) {
		if (isPlacementCorrectInMovementPhase(newGame, board, currentx, i, 0, penguinNumber) == 0)
			break;
		else {
			floeGoodness[j].x = currentx;
			floeGoodness[j].y = i;
			floeGoodness[j].opportunity = calculateOpportunities(newGame, board, floeGoodness[j].x, floeGoodness[j].y, penguinNumber);
			floeGoodness[j].risk = calculateRisk(newGame, board, floeGoodness[j].x, floeGoodness[j].y, penguinNumber);
			floeGoodness[j].goodnessIndex = floeGoodness[j].opportunity - floeGoodness[j].risk;
			j++;
		}
	}

	//choosing best floe
	bestFloe = floeGoodness[0];

	for (int i = 1; i < 38; i++) {
		if (floeGoodness[i].goodnessIndex > bestFloe.goodnessIndex
			|| (floeGoodness[i].goodnessIndex == bestFloe.goodnessIndex && floeGoodness[i].risk < bestFloe.risk))
			bestFloe = floeGoodness[i];
	}

	return bestFloe;
}

void smartlyChooseAndMovePenguin(game* newGame, floe** board)
{
	smartCoords penguinsBestFloe[9];
	int bestGoodnessIndex = -100, lowestRisk = 100, penguinWithBestGoodnessIndex = -1;

	//choosing best floe for every penguin
	for (int i = 0; i < newGame->numberOfPenguins; i++)
		penguinsBestFloe[i] = chooseBestFloe(*newGame, board, newGame->Players[0].penguins[i].x, newGame->Players[0].penguins[i].y, i);

	//finding penguin with best floe
	for (int i = 0; i < newGame->numberOfPenguins; i++)
	{
		if (penguinsBestFloe[i].x != -1 && (penguinsBestFloe[i].goodnessIndex > bestGoodnessIndex || (penguinsBestFloe[i].goodnessIndex == bestGoodnessIndex && penguinsBestFloe[i].risk < lowestRisk))) {
			bestGoodnessIndex = penguinsBestFloe[i].goodnessIndex;
			lowestRisk = penguinsBestFloe[i].risk;
			penguinWithBestGoodnessIndex = i;
		}
	}

	if (penguinWithBestGoodnessIndex == -1)
		return;

	//clearing previous floe
	board[newGame->Players[0].penguins[penguinWithBestGoodnessIndex].y][newGame->Players[0].penguins[penguinWithBestGoodnessIndex].x].penguinsOwnerID = 0;
	board[newGame->Players[0].penguins[penguinWithBestGoodnessIndex].y][newGame->Players[0].penguins[penguinWithBestGoodnessIndex].x].penguinID = 0;

	//placing new penguin
	int newx = penguinsBestFloe[penguinWithBestGoodnessIndex].x;
	int newy = penguinsBestFloe[penguinWithBestGoodnessIndex].y;
	newGame->Players[0].penguins[penguinWithBestGoodnessIndex].x = newx;
	newGame->Players[0].penguins[penguinWithBestGoodnessIndex].y = newy;

	//adding score and setting number of fish and player and penguin ID on current floe
	newGame->Players[0].score += board[newy][newx].numberOfFish;
	board[newy][newx].numberOfFish = 0;
	board[newy][newx].penguinID = penguinWithBestGoodnessIndex;
	board[newy][newx].penguinsOwnerID = newGame->Players[0].ID;
}
