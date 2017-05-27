/* cardtest2.c
 * Nigel Robbins
 * Test functionality of the smithy card
 */

#include"dominion.h"
#include"dominion_helpers.h"
#include"rngs.h"
#include"assert_true.h"
#include<stdio.h>
#include<stdlib.h>

void resetGame(struct gameState* state, int* cards) {
  int numPlayers = 2;
  initializeGame(numPlayers, cards, 12345, state);
}

void testSmithy() {
  struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
  if (!state) return;
  int returnValue;
  int player;
  int otherPlayer;
  int* cards = kingdomCards( // declare cards at top level to loop over later
    feast,
    adventurer,
    council_room,
    smithy,
    village,
    steward,
    baron,
    mine,
    treasure_map,
    remodel
  );

  for (player=0; player<2; player++) {
    otherPlayer = (player + 1) % 2;

    // Test that current player draws 3 cards from their deck
    printf("Player %d plays smithy\n", player + 1);
    resetGame(state, cards);
    state->hand[player][0] = smithy;
    state->handCount[player] = 1;
    state->deckCount[player] = 5;
    state->discardCount[player] = 0;
    returnValue = performSmithyCardEffect(player, 0, state);

    assertTrue(returnValue == 0, "", "Expected smithy to return 0");
    assertTrue(state->handCount[player] == 3,
               "", "Expected player to have 3 cards in hand");
    assertTrue(state->deckCount[player] == 2,
               "", "Expected deck to have 2 cards left");
    assertTrue(state->discardCount[player] = 1,
               "", "Expected discard pile to have 1 card");
    assertTrue(state->discard[player][0] = smithy,
               "", "Expected discard pile to have smithy");
    // expect other player to have expereinced no changes
    assertTrue(state->handCount[otherPlayer] == otherPlayer ? 0 : 5,
               "", "Expected other player's hand to not change");
    assertTrue(state->deckCount[otherPlayer] == otherPlayer ? 10 : 5,
               "", "Expected other player's deck to not change");
    assertTrue(state->discardCount[otherPlayer] == 0,
               "", "Expected other player's discard to be unchanged");
    // exepct other piles to have experienced no changes
    int cardIndex;
    int card;
    for (cardIndex = 0; cardIndex<10; cardIndex++) {
      card = cards[cardIndex];
      assertTrue(supplyCount(card, state) == 10,
                 "", "Expected kingdom cards to have supply 10");
    }
    int victoryCard; // vistory cards are all at the beginning
    for (victoryCard = curse; victoryCard <= province; victoryCard++) {
      // curse = 0 and has 10 cards
      assertTrue(supplyCount(victoryCard, state) == victoryCard ? 8 : 10,
                 "", "Expected victory card supplies to have not changed");
    }
 }
}

int main() {
  testSmithy();
  return 0;
}
