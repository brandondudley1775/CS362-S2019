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

#define TESTCARD "sea hag"

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

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

	// ----------- TEST 1: choice1 = 1 = +0 cards --------------
	printf("TEST 1: choice1 = 1 = +0 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(sea_hag, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 3;
	xtraCoins = 0;
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);

	// ----------- TEST 2: choice1 = 2 = +0 coins --------------
	printf("TEST 2: choice1 = 2 = +0 coins\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 2;
	cardEffect(sea_hag, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 0;
	xtraCoins = 0;
 
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assert(testG.coins == G.coins + xtraCoins);

	// ----------- TEST 3: choice1 = 3 = check for curse --------------

	printf("TEST 4: choice1 = 3 = check for curse, should be present\n");
	choice1 = 3;

	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 3;
	cardEffect(sea_hag, choice1, choice2, choice3, &testG, handpos, &bonus);
	int j;
	int cursed;
	cursed = 0;
	// make sure one of the cards is now a curse
	for(j=0; j<25; j++){
		if(G.deck[1][j]!=testG.deck[1][j]){
			cursed = 1;
		}
	}
	printf("Expected curse card to be present: %d\n", cursed);
	assert(cursed);

	// ----------- TEST 4: choice1 = 3 = check for curse --------------

	printf("TEST 4: choice1 = 3 = check for curse, player should not be cursed\n");
	choice1 = 3;

	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 3;
	cardEffect(sea_hag, choice1, choice2, choice3, &testG, handpos, &bonus);
	int not_cursed;
	not_cursed = 1;
	// make sure one of the cards is now a curse
	for(j=0; j<25; j++){
		if(G.deck[0][j]!=testG.deck[0][j]){
			not_cursed = 0;
		}
	}
	printf("Expected curse card to be present: %d\n", cursed);
	assert(not_cursed);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


