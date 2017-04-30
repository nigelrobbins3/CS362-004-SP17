/* unittest4.c
 * Nigel Robbins
 * Test the isGameOver function in dominion.c
 */

#include"dominion.h"
#include"dominion_helpers.h"
#include"rngs.h"
#include"assert_true.h"
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

void testIsGameOver() {
  struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
  if (!state) return;
  int returnValue;

  // With a new game
  resetGame(state);
  returnValue = isGameOver(state);
  assertTrue(returnValue == 0, "", "Game was over before it began");
  
  // With only one province
  resetGame(state);
  state->supplyCount[province] = 1;
  returnValue = isGameOver(state);
  assertTrue(returnValue == 0,
             "", "Expected game to not be over with 1 province remaining");

  // With 0 provinces
  resetGame(state);
  state->supplyCount[province] = 0;
  returnValue = isGameOver(state);
  assertTrue(returnValue == 1,
             "", "Expected game to be over with 0 provinces remaining");
  
  // With one (non-province) supply pile emptied 
  resetGame(state);
  state->supplyCount[feast] = 0;
  returnValue = isGameOver(state);
  assertTrue(returnValue == 0,
             "", "Expected game to not be over with 1 empty supply pile");

  // With two (non-province) supply piles emptied 
  resetGame(state);
  state->supplyCount[feast] = 0;
  state->supplyCount[village] = 0;
  returnValue = isGameOver(state);
  assertTrue(returnValue == 0,
             "", "Expected game to not be over with 2 empty supply piles");

  // With three (non-province) supply piles emptied 
  resetGame(state);
  state->supplyCount[feast] = 0;
  state->supplyCount[village] = 0;
  state->supplyCount[gardens] = 0;
  returnValue = isGameOver(state);
  assertTrue(returnValue == 1,
             "", "Expected game be over with 3 empty supply piles");

  // With one non-province and and the province supply pile emptied 
  resetGame(state);
  state->supplyCount[feast] = 0;
  state->supplyCount[province] = 0;
  returnValue = isGameOver(state);
  assertTrue(returnValue == 1,
             "", "Expected game to be over with no provinces remaining");

}

int main() {
  testIsGameOver();
  return 0;
}
