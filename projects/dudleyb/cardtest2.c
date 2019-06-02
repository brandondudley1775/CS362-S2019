/*
 * cardtest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
    int newCards = 0;
    int discarded = 1;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int xtraCoins;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 1 = +2 cards --------------
	printf("TEST 1: choice1 = 1\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 3;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);

	// ----------- TEST 2: choice1 = 2 = +2 coins --------------
	printf("TEST 2: choice1 = 2 = +2 coins\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 2;
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 3;
	xtraCoins = 0;
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assert(testG.coins == G.coins + xtraCoins);

	// ----------- TEST 3: choice1 = 3 = trash two cards --------------
	printf("TEST 3: choice1 = 3 = trash two cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 3;
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 3;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);

	// ----------- TEST 4: choice1 = -1 = invalid option --------------
	printf("TEST 3: choice1 = -1 = invalid option, should be fine\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = -1;
	int res;
	res = cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("error received = %d, error expected = %d\n", res, 0);
	assert(res == 0);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


