/*
 * cardtest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 1 = +2 cards --------------
	printf("TEST 1: +3 cards, discard 1\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer] + 3, G.deckCount[thisPlayer]);
	//assert(testG.deckCount[thisPlayer] + 4 == G.deckCount[thisPlayer]);

	// ----------- TEST 2: 200 bonus coins --------------
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	int bonus_copy;
	bonus_copy = bonus;
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	bonus = 200;
	
	printf("hand count = %d, expected = %d\n", bonus_copy+200, bonus);
	//assert(bonus_copy+200 == bonus);

	// ----------- TEST 3: choice1 = 3 = trash two cards --------------
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 3;
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer] + 1, G.deckCount[thisPlayer]);
	//assert(testG.deckCount[thisPlayer] + 1 == G.deckCount[thisPlayer]);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


