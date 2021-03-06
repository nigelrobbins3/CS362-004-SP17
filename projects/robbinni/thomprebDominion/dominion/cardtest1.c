/* cardtest1.c
 * Nigel Robbins
 * Test functionality of the adventurer card
 */

#include"dominion.h"
#include"dominion_helpers.h"
#include"rngs.h"
#include"assert_true.h"
#include<stdio.h>
#include<stdlib.h>

void resetGame(struct gameState* state) {
  int numPlayers = 2;
  int* cards = kingdomCards(
    feast,
    adventurer,
    council_room,
    smithy,
    village,
    steward,
    gardens,
    mine,
    treasure_map,
    great_hall
  );
  initializeGame(numPlayers, cards, 12345, state);
}

void testAdventurer() {
  struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
  if (!state) return;
  int returnValue;
  int player = 0;
  int bonus = 0; // only to give cardEffect the right signature

  // Test that if the first two cards are copper, adventurer draws them and stops.
  printf("**********\n");
  printf("Play adventurer with two copper on top of the deck\n");
  resetGame(state);
  state->discardCount[player] = 0;
  state->deckCount[player] = 5;
  state->deck[player][3] = copper;
  state->deck[player][4] = copper;
  state->handCount[player] = 1;
  state->hand[player][0] = adventurer;
  returnValue = cardEffect(adventurer, 0, 0, 0, state, 0, &bonus);

  assertTrue(returnValue == 0, "", "Expected adventurer effect to return 0");
  assertTrue(state->handCount[player] == 2,
             "", "Expected player to have two cards in hand");
  assertTrue(state->hand[player][0] == copper,
             "", "Expected the player to have copper in position 0");
  assertTrue(state->hand[player][1] == copper,
             "", "Expected the player to have copper in position 1");
  assertTrue(state->deckCount[player] == 3,
             "", "Expected deckCount to have decreased by 2");
  assertTrue(state->discardCount[player] == 1, // adventurer is discarded
             "", "Expected discard to have 1 card");

  // Test that the same works with gold and silver
  printf("**********\n");
  printf("Play adventurer with a gold and silver on top of the deck\n");
  resetGame(state);
  state->discardCount[player] = 0;
  state->deckCount[player] = 5;
  state->deck[player][3] = silver;
  state->deck[player][4] = gold;
  state->handCount[player] = 2; // test different hand sizes in each scenario
  state->hand[player][0] = adventurer;
  state->hand[player][1] = curse; // an irrelevant card
  returnValue = cardEffect(adventurer, 0, 0, 0, state, 0, &bonus);

  assertTrue(returnValue == 0, "", "Expected adventurer effect to return 0");
  assertTrue(state->handCount[player] == 3,
             "", "Expected player to have three cards in hand");
  assertTrue(state->hand[player][0] == curse,
             "", "Expected the player to have curse in position 0");
  assertTrue(state->hand[player][1] == gold,
             "", "Expected the player to have gold in position 1");
  assertTrue(state->hand[player][2] == silver,
             "", "Expected the player to have silver in position 2");
  assertTrue(state->deckCount[player] == 3,
             "", "Expected deckCount to have decreased by 2");
  assertTrue(state->discardCount[player] == 1, // adventurer is discarded
             "", "Expected discard to have 1 card");

  // Test that adventurer ignores non-treasure cards
  printf("**********\n");
  printf("Play adventurer with 3 curses and 2 copper in the deck\n");
  resetGame(state);
  state->discardCount[player] = 0;
  state->deckCount[player] = 5;
  state->deck[player][0] = copper;
  state->deck[player][1] = copper;
  state->deck[player][2] = curse;
  state->deck[player][3] = curse;
  state->deck[player][4] = curse;
  state->handCount[player] = 2; // test different hand sizes in each scenario
  state->hand[player][0] = curse;
  state->hand[player][1] = adventurer; // test different adventurer positions
  returnValue = cardEffect(adventurer, 0, 0, 0, state, 1, &bonus);

  assertTrue(returnValue == 0, "", "Expected adventurer effect to return 0");
  assertTrue(state->handCount[player] == 3,
             "", "Expected player to have three cards in hand");
  assertTrue(state->hand[player][0] == curse,
             "", "Expected the player to have curse in position 0");
  assertTrue(state->hand[player][1] == copper,
             "", "Expected the player to have copper in position 1");
  assertTrue(state->hand[player][2] == copper,
             "", "Expected the player to have copper in position 2");
  assertTrue(state->deckCount[player] == 0,
             "", "Expected deckCount to have decreased by 5");
  assertTrue(state->discardCount[player] == 4, // everything is discarded
             "", "Expected discard to have 4 cards");

  // Test that adventurer shuffles the discard into the deck if necessary
  printf("**********\n");
  printf("Play adventurer with only 1 copper in the deck and 1 in the discard\n");
  resetGame(state);
  state->discardCount[player] = 1;
  state->discard[player][0] = copper; // treasure in discard
  state->deckCount[player] = 5;
  state->deck[player][0] = curse;
  state->deck[player][1] = copper; // only one treasure in deck
  state->deck[player][2] = curse;
  state->deck[player][3] = curse;
  state->deck[player][4] = curse;
  state->handCount[player] = 3; // test different hand sizes in each scenario
  state->hand[player][0] = adventurer;
  state->hand[player][1] = curse;
  state->hand[player][2] = curse;
  returnValue = cardEffect(adventurer, 0, 0, 0, state, 0, &bonus);

  assertTrue(returnValue == 0, "", "Expected adventurer effect to return 0");
  assertTrue(state->handCount[player] == 4,
             "", "Expected player to have 4 cards in hand");
  assertTrue(state->hand[player][0] == curse,
             "", "Expected the player to have curse in position 0");
  assertTrue(state->hand[player][1] == curse,
             "", "Expected the player to have curse in position 1");
  assertTrue(state->hand[player][2] == copper,
             "", "Expected the player to have copper in position 2");
  assertTrue(state->hand[player][3] == copper,
             "", "Expected the player to have copper in position 3");
  assertTrue(state->deckCount[player] == 0,
             "", "Expected deckCount to have decreased by 5");
  assertTrue(state->discardCount[player] == 5, // everything is discarded
             "", "Expected discard to have 5 cards");

  // Test that adventurer draws one card if there is only one treasure in the
  // deck + discard piles. 
  printf("**********\n");
  printf("Play adventurer with only 1 copper in the deck and 0 in the discard\n");
  resetGame(state);
  state->discardCount[player] = 1;
  state->discard[player][0] = curse; // no treasure in discard
  state->deckCount[player] = 5;
  state->deck[player][0] = curse;
  state->deck[player][1] = copper; // only one treasure in deck
  state->deck[player][2] = curse;
  state->deck[player][3] = curse;
  state->deck[player][4] = curse;
  state->handCount[player] = 3; // test different hand sizes in each scenario
  state->hand[player][0] = curse;
  state->hand[player][1] = curse;
  state->hand[player][2] = adventurer;
  returnValue = cardEffect(adventurer, 0, 0, 0, state, 2, &bonus);

  assertTrue(returnValue == 0, "", "Expected adventurer effect to return 0");
  assertTrue(state->handCount[player] == 3,
             "", "Expected player to have 3 cards in hand");
  assertTrue(state->hand[player][0] == curse,
             "", "Expected the player to have curse in position 0");
  assertTrue(state->hand[player][1] == curse,
             "", "Expected the player to have curse in position 1");
  assertTrue(state->hand[player][2] == copper,
             "", "Expected the player to have copper in position 2");
  assertTrue(state->deckCount[player] == 0,
             "", "Expected deckCount to have decreased by 5");
  assertTrue(state->discardCount[player] == 6, // everything is discarded
             "", "Expected discard to have 6 cards");

  // Test that adventurer draws nothing if there are no treasures in the
  // deck + discard piles. NOTE: this has a bug which will cause a segfault
  // if there are no treasures in the players hand at the beginning!
  printf("**********\n");
  printf("Play adventurer with no treasures\n");
  resetGame(state);
  state->whoseTurn = player;
  state->discardCount[player] = 1;
  state->discard[player][0] = curse; // no treasure in deck + discard
  state->deckCount[player] = 5;
  state->deck[player][0] = curse;
  state->deck[player][1] = curse;
  state->deck[player][2] = curse;
  state->deck[player][3] = curse;
  state->deck[player][4] = curse;
  state->handCount[player] = 3; // test different hand sizes in each scenario
  state->hand[player][0] = copper; // NOTE: treasure is needed!!!
  state->hand[player][1] = adventurer;
  state->hand[player][2] = curse;
  returnValue = cardEffect(adventurer, 0, 0, 0, state, 1, &bonus);

  assertTrue(returnValue == 0, "", "Expected adventurer effect to return 0");
  assertTrue(state->handCount[player] == 2,
             "", "Expected player to have 2 cards in hand");
  assertTrue(state->hand[player][0] == curse,
             "", "Expected the player to have curse in position 0");
  assertTrue(state->hand[player][1] == curse,
             "", "Expected the player to have curse in position 1");
  assertTrue(state->deckCount[player] == 0,
             "", "Expected deckCount to have decreased by 5");
  assertTrue(state->discardCount[player] == 7, // everything is discarded
             "", "Expected discard to have 7 cards");


}

int main() {
  testAdventurer();
  return 0;
}
