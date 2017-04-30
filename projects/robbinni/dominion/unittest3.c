/* unittest2.c
 * Nigel Robbins
 * Test the gainCard function in dominion.c
 */

#include"dominion.h"
#include"dominion_helpers.h"
#include"rngs.h"
#include<stdio.h>
#include<stdlib.h>

void resetGame(struct gameState* state) {
  // Eventually this method may be a good place for some random testing
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

void testCommonFunctionality(struct gameState* state, int trashFlag) {
  int player = 0; // first player has been given the hand [copper, estate, smithy]
  int returnValue;

  // Test discarding a middle card
  // discard the estate (hand: [copper, smithy])
  returnValue = discardCard(1, player, state, trashFlag);
  assertTrue(returnValue == 0, "", "Expected discardCard to return 0");
  assertTrue(state->hand[0][0] == copper,
             "", "Expected hand[0][0] to be copper after discarding estate");
  assertTrue(state->hand[0][1] == smithy,
             "", "Expected hand[0][1] to be smithy after discarding estate");
  assertTrue(state->hand[0][2] == -1,
             "", "Expected hand[0][2] to be -1 after discarding estate");
  assertTrue(state->handCount[0] == 2,
             "", "Expected handCount to be 2 after discarding estate");
 
  // Test discarding the card at the end of the array
  // discard the smithy (hand: [copper])
  returnValue = discardCard(1, player, state, trashFlag);
  assertTrue(returnValue == 0, "", "Expected discardCard to return 0");
  assertTrue(state->hand[0][0] == copper,
             "", "Expected hand[0][0] to be copper after discarding smithy");
  assertTrue(state->hand[0][1] == -1,
             "", "Expected hand[0][1] to be -1 after discarding smithy");
  assertTrue(state->hand[0][2] == -1,
             "", "Expected hand[0][2] to be -1 after discarding smithy");
  assertTrue(state->handCount[0] == 1,
             "", "Expected handCount to be 1 after discarding smithy");

  // Test discarding the card at the beginning of the array
  // discard the copper (hand: [])
  returnValue = discardCard(0, player, state, trashFlag);
  assertTrue(returnValue == 0, "", "Expected discardCard to return 0");
  assertTrue(state->hand[0][0] == -1,
             "", "Expected hand[0][0] to be -1 after discarding copper");
  assertTrue(state->hand[0][1] == -1,
             "", "Expected hand[0][1] to be -1 after discarding copper");
  assertTrue(state->hand[0][2] == -1,
             "", "Expected hand[0][2] to be -1 after discarding copper");
  assertTrue(state->handCount[0] == 0,
             "", "Expected handCount to be 0 after discarding copper");
}

void testGainCard() {
  struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
  if (!state) return;
  int trashFlag = 0; // first test cards without trashing

  resetGame(state);
  // set default hand
  state->hand[0][0] = copper;
  state->hand[0][1] = estate;
  state->hand[0][2] = smithy;
  state->handCount[0] = 3;
  
  assertTrue(state->playedCardCount == 0,
             "Game initialized\n", "Initialized game already had played cards");
  testCommonFunctionality(state, trashFlag);
  assertTrue(state->playedCardCount == 3,
             "", "Not all cards were played even though trashFlag was 0");
  assertTrue(state->playedCards[0] == estate,
             "", "Expected first played card to be an estate");
  assertTrue(state->playedCards[1] == smithy,
             "", "Expected second played card to be a smithy");
  assertTrue(state->playedCards[2] == copper,
             "", "Expected  third played card to be a copper");


  // test discardCard when trashing cards
  trashFlag = 1;
  resetGame(state);
  // set default hand
  state->hand[0][0] = copper;
  state->hand[0][1] = estate;
  state->hand[0][2] = smithy;
  state->handCount[0] = 3;
  
  assertTrue(state->playedCardCount == 0,
             "Game initialized\n", "Initialized game already had played cards");
  testCommonFunctionality(state, trashFlag);
  assertTrue(state->playedCardCount == 0,
             "", "Cards were marked \"played\" even though trashFlag was 1");
}

int main() {
  testGainCard();
  return 0;
}
