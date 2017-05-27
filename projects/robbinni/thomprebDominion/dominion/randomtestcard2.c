/* randomtestcard2.c
 * Nigel Robbins
 * Test the functionality of the village card using random testing
 */

#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "assert_true.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> // for memset

#define VILLAGE_TEST_COUNT 200
#define TRUE 1
#define FALSE 0

void clearGame(struct gameState* state) {
  memset(state, -1, sizeof(struct gameState));
}

void fillCards(int* pile, int size) {
  int i;
  for (i=0; i<size; i++) {
    // fill the pile with any kingdom card. Not all are possible in every game.
    pile[i] = Random() * (treasure_map + 1);
  }
}

int main() {
  struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
  int test, player, returnValue, handCount, deckCount, discardCount, handPos,
      playedCardCount, actionCount, expectedDeck, expectedDiscard, drawFailed;
  SelectStream(3);
  PutSeed(123);

  printf("Testing Village with random testing\n");
  for (test=0; test<VILLAGE_TEST_COUNT; test++) {
    clearGame(state);
    player = floor(Random() * MAX_PLAYERS);
    handCount = floor(Random() * (MAX_HAND - 1)) + 1; // at least 1
    deckCount = floor(Random() * MAX_DECK);
    discardCount = floor(Random() * MAX_DECK);
    playedCardCount = floor(Random() * MAX_DECK);
    handPos = floor(Random() * (handCount - 1)); // valid hand index
    // test negative values in case a bug let a player play too many actions
    actionCount = floor(Random() * 10) - 5;

    state->whoseTurn = player;
    state->handCount[player] = handCount;
    state->deckCount[player] = deckCount;
    state->discardCount[player] = discardCount;
    state->playedCardCount = playedCardCount;
    state->numActions = actionCount;
    // add valid kingdom cards to player piles
    fillCards(state->hand[player], handCount);
    fillCards(state->deck[player], deckCount);
    fillCards(state->discard[player], discardCount);
    fillCards(state->playedCards, playedCardCount);
    // put village in players hand
    state->hand[player][handPos] = village;

    // special case for attempting to draw from an empty deck
    expectedDeck = deckCount - 1;
    expectedDiscard = discardCount;
    drawFailed = FALSE;
    if (deckCount == 0) {
      expectedDiscard = 0; // we will shuffle
      expectedDeck = discardCount - 1;
      if (discardCount == 0) {
        expectedDeck = 0;
        drawFailed = TRUE; // can't draw if there are no cards!
      }
    }

    // run code under test
    returnValue = cardEffect(village, 0, 0, 0, state, handPos, NULL); 
    assertTrue(returnValue == 0, "", "Expected return value to be 0");
    assertTrue(state->handCount[player] == drawFailed ? handCount - 1 : handCount,
               "", "Expected player to have net gain of 0 cards");
    assertTrue(state->playedCardCount,
               "", "Expected player to have played a card");
    assertTrue(state->playedCards[playedCardCount] == village,
               "", "Expected the last played card to be village");
    assertTrue(state->discardCount[player] == expectedDiscard,
               "", "Expected player to not have discarded a card");
    assertTrue(state->deckCount[player] == expectedDeck,
               "", "Expected player to have drawn 1 card");
    assertTrue(state->numActions == actionCount + 2,
               "", "Expected player to have gained 2 actions");
  }

  free(state);
  return 0;
}
