/* randomtestcdventurer.c
 * Nigel Robbins
 * Test the functionality of the adventurer card using random testing
 */

#include "rngs.h"
#include "dominion.h"
#include "assert_true.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> // for memset

#define ADV_TEST_COUNT 200
#define SMALL_DECK 50
#define SMALL_HAND 10


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

int main(int argc, char* argv[]) {
  struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
  int test, player, returnValue, handCount, deckCount, discardCount, handPos,
      playedCardCount, deckLoss, discardGain, firstDrawnCard, secondDrawnCard,
      deckSize, handSize;

  SelectStream(3);
  PutSeed(123);

  printf("Testing Adventurer with random testing\n");
  for (test=0; test<ADV_TEST_COUNT; test++) {
    // Weight the random tests toward reasonable values every other tests
    // There is a bug which is more likely for small hands and decks, and with
    // MAX_DECK values it takes ~200000 tests to uncover.
    deckSize = (test % 2) ? MAX_DECK : SMALL_DECK;
    handSize = (test % 2) ? MAX_HAND : SMALL_HAND;
    clearGame(state);

    player = floor(Random() * MAX_PLAYERS);
    handCount = floor(Random() * (handSize - 1)) + 1; // at least 1
    deckCount = floor(Random() * deckSize);
    discardCount = floor(Random() * deckSize);
    playedCardCount = floor(Random() * deckSize);
    handPos = floor(Random() * handCount);
    state->handCount[player] = handCount;
    state->deckCount[player] = deckCount;
    state->discardCount[player] = discardCount;
    state->playedCardCount = playedCardCount;


    // add valid kingdom cards to player piles
    fillCards(state->hand[player], handCount);
    fillCards(state->deck[player], deckCount);
    fillCards(state->discard[player], discardCount);
    fillCards(state->playedCards, playedCardCount);

    // put the adventurer at handPos
    state->hand[player][handPos] = adventurer;

    // run code under test
    returnValue = performAdventurerCardEffect(player, handPos, state);
    deckLoss = deckCount - state->deckCount[player];
    discardGain = state->discardCount[player] - discardCount;
    firstDrawnCard = state->hand[player][handCount];
    secondDrawnCard = state->hand[player][handPos]; // will have been swapped with Adventurer

    // test things that are always true
    assertTrue(returnValue == 0, "", "Expected return value to be 0");
    assertTrue(state->playedCardCount == playedCardCount + 1,
               "", "Expected played cards to have increased by 1");

    // Depending on how many cards were drawn, different behavior is expected
    switch(state->handCount[player] - handCount) {
      case 1: {
        // Typical case: 2 treasures drawn, Adventurer discarded for a net gain of 1
        assertTrue(discardGain == deckLoss - 2, // this is valid through shuffling
                   "", "Expected player to have discarded every drawn card except the two treasures");
        assertTrue(firstDrawnCard == copper || firstDrawnCard == silver || firstDrawnCard == gold,
                   "", "Expected the first card to have been treasure");
        assertTrue(secondDrawnCard == copper || secondDrawnCard == silver || secondDrawnCard == gold,
                   "", "Expected the second card to have been treasure");
        break;
      }
      case 0: {
        // Only 1 treasure drawn and Adventurer discarded for a net gain of 0
        assertTrue(discardGain == deckLoss - 1,
                   "", "Expected player to have discarded every drawn card except the treasure");
        // the "second" card is the last card drawn and gets swapped with Adventurer
        assertTrue(secondDrawnCard == copper || secondDrawnCard == silver || secondDrawnCard == gold,
                   "", "Expected the drawn card to have been treasure");
        break;
      }
      case -1: {
        // No treasures drawn and Adventurer discarded for a net gain of -1
        assertTrue(discardGain == deckLoss,
                   "", "Expected player to have discarded every drawn card");
        break;
      }
      default: {
        assertTrue(0, "", "Expected the player to have drawn 0, 1, or 2 cards");
      }
    }
  }

  free(state);
  return 0;
}
