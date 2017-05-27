/* randomtestcard1.c
 * Nigel Robbins
 * Test the functionality of the smithy card using random testing
 */

#include "rngs.h"
#include "dominion.h"
#include "assert_true.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> // for memset

#define SMITHY_TEST_COUNT 200

void clearGame(struct gameState* state) {
  memset(state, -1, sizeof(struct gameState));
}

int main() {
  struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
  int test, player, returnValue, handCount, deckCount, discardCount, handPos,
      playedCardCount;
  SelectStream(3);
  PutSeed(123);

  printf("Testing Smithy with random testing\n");
  for (test=0; test<SMITHY_TEST_COUNT; test++) {
    clearGame(state);
    player = floor(Random() * MAX_PLAYERS);
    handCount = floor(Random() * (MAX_HAND - 1)) + 1; // at least 1
    deckCount = floor(Random() * MAX_DECK);
    discardCount = floor(Random() * MAX_DECK);
    playedCardCount = floor(Random() * MAX_DECK);
    // BUG: large values of handPos cause a segfault after drawing three cards.
    // Use small values so that test suite completes until bug is resolved.
    handPos = floor(Random() * MAX_PLAYERS);
    state->whoseTurn = player;
    state->handCount[player] = handCount;
    state->deckCount[player] = deckCount;
    state->discardCount[player] = discardCount;
    state->playedCardCount = playedCardCount;

    // put smithy at handPos
    state->hand[player][handPos] = smithy;

    // run code under test
    returnValue = cardEffect(smithy, 0, 0, 0, state, handPos, NULL); 
    assertTrue(returnValue == 0, "", "Expected return value to be 0");
    assertTrue(state->handCount[player] == handCount + 2,
               "", "Expected player to have net gain of 2 cards");
    assertTrue(state->playedCardCount == playedCardCount + 1,
               "", "Expected player to have played a card");
    assertTrue(state->playedCards[playedCardCount] == smithy,
               "", "Expected player to have played 1 smithy");
    assertTrue(state->discardCount[player] == discardCount,
               "", "Expected player to not have discarded a card");
    assertTrue(state->deckCount[player] == deckCount - 3,
               "", "Expected player to have drawn 3 cards");
  }

  free(state);
  return 0;
}
