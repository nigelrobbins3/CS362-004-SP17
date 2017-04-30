/* unittest2.c
 * Nigel Robbins
 * Test the gainCard function in dominion.c
 */

#include"dominion.h"
#include"dominion_helpers.h"
#include"rngs.h"
#include<stdio.h>

void assertTrue(int result, char* success, char* failure) {
  if (result) {
    if (success[0] == '\0') {
      printf("Success\n");
    } else {
      printf(success);
    }
  } else {
    printf("TEST FAILURE: ");
    printf(failure);
  }
}

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

void testGainCard() {
  struct gameState state; // set pointer to null
  int returnValue;
  int player;
  
  for (player = 0; player < 2; player++) {
    int otherPlayer = (player + 1) % 2;
    // Fails if supply pile has no cards
    resetGame(&state);
    state.supplyCount[smithy] = 0;
    returnValue = gainCard(smithy, &state, 0, player);
    assertTrue((returnValue == -1),
               "",
               "expected failure when drawing from empty supply");

    // Fails if passed card is not in the game
    resetGame(&state);
    returnValue = gainCard(sea_hag, &state, 0, player);
    assertTrue((returnValue == -1),
               "",
               "expected failure when drawing from invalid supply");

    // When toFlag is 0, doesn't change deckCount, handCount, or other player's
    // counts of any kind. The discard count goes up, and the supply goes down
    resetGame(&state);
    returnValue = gainCard(smithy, &state, 0, player);
    assertTrue((returnValue == 0), "", "gainCard failed when toFlag was 0");
    assertTrue( // supply decreases
      state.supplyCount[smithy] == 9,
      "", "failed to properly decrease supplyCount with toFlag 0"
    );
    assertTrue( // discard pile increases
      state.discardCount[player] == 1,
      "", "failed to properly increase discardCount with toFlag 0"
    );
    assertTrue( // discard has a smithy
      state.discard[player][0] == smithy,
      "", "failed to properly add smithy to discard with toFlag 0"
    );
    assertTrue( // no change in handCount
      state.handCount[player] == player ? 0 : 5, // non-player 1 has no cards
      "", "increased handCount with toFlag 0"
    );
    assertTrue( // no change in deckCount
      state.deckCount[player] == player ? 10 : 5,
      "", "increased deckCount with toFlag 0"
    );
    assertTrue( // no change in discardCount for otherPlayer
      state.discardCount[otherPlayer] == 0,
      "", "increased discardCount of wrong player with toFlag 0"
    );
    assertTrue( // no change in handCount for otherPlayer
      state.handCount[otherPlayer] == otherPlayer ? 0 : 5,
      "", "increased handCount of wrong player with toFlag 0"
    );
    assertTrue( // no change in deckCount
      state.deckCount[otherPlayer] == otherPlayer ? 10 : 5,
      "", "increased deckCount of wrong player with toFlag 0"
    );

    // When toFlag is 1, doesn't change discardCount, handCount, or other
    // player's counts of any kind.
    resetGame(&state);
    returnValue = gainCard(smithy, &state, 1, player);
    assertTrue((returnValue == 0), "", "gainCard failed when toFlag was 1");
    assertTrue( // supply decreases
      state.supplyCount[smithy] == 9,
      "", "failed to properly decrease supplyCount with toFlag 1"
    );
    assertTrue( // no change in discardCount
      state.discardCount[player] == 0,
      "", "increased discardCount with toFlag 1"
    );
    assertTrue( // no change in handCount
      state.handCount[player] == player ? 0 : 5,
      "", "increased handCount with toFlag 1"
    );
    assertTrue( // deckCount increases
      state.deckCount[player] == player ? 11 : 6,
      "", "failed to increase deckCount with toFlag 1"
    );
    assertTrue( // deck has a smithy
      state.deck[player][player ? 10 : 5] == smithy,
      "", "failed to properly add smithy to deck with toFlag 1"
    );
    assertTrue( // no change in discardCount for otherPlayer
      state.discardCount[otherPlayer] == 0,
      "", "increased discardCount of wrong player with toFlag 1"
    );
    assertTrue( // no change in handCount for otherPlayer
      state.handCount[otherPlayer] == otherPlayer ? 0 : 5,
      "", "increased handCount of wrong player with toFlag 1"
    );
    assertTrue( // no change in deckCount
      state.deckCount[otherPlayer] == otherPlayer ? 10 : 5,
      "", "increased deckCount of wrong player with toFlag 1"
    );
 
    // When toFlag is 2, doesn't change discardCount, handCount, or other
    // player's counts of any kind.
    resetGame(&state);
    returnValue = gainCard(smithy, &state, 2, player);
    assertTrue((returnValue == 0), "", "gainCard failed when toFlag was 2");
    assertTrue( // supply decreases
      state.supplyCount[smithy] == 9,
      "", "failed to properly decrease supplyCount with toFlag 2"
    );
    assertTrue( // no change in discardCount
      state.discardCount[player] == 0,
      "", "increased discardCount with toFlag 2"
    );
    assertTrue( // handCount increases
      state.handCount[player] == player ? 1 : 6,
      "", "failed to increase handCount with toFlag 2"
    );
    assertTrue( // no change in deckCount
      state.deckCount[player] == player ? 10 : 5,
      "", "increased deckCount with toFlag 2"
    );
    assertTrue( // hand has a smithy
      state.hand[player][player ? 0 : 5] == smithy,
      "", "failed to properly add smithy to hand with toFlag 2"
    );
    assertTrue( // no change in discardCount for otherPlayer
      state.discardCount[otherPlayer] == 0,
      "", "increased discardCount of wrong player with toFlag 2"
    );
    assertTrue( // no change in handCount for otherPlayer
      state.handCount[otherPlayer] == otherPlayer ? 0 : 5,
      "", "increased handCount of wrong player with toFlag 2"
    );
    assertTrue( // no change in deckCount
      state.deckCount[otherPlayer] == otherPlayer ? 10 : 5,
      "", "increased deckCount of wrong player with toFlag 2"
    );
 
    // It would also be nice to test that the game state is unchanged when
    // a call to this method fails
  }
}

int main() {
  testGainCard();
  return 0;
}
