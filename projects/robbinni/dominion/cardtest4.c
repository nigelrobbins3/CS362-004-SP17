/* cardtest4.c
 * Nigel Robbins
 * Test functionality of the Tribute card
 */

#include"dominion.h"
#include"dominion_helpers.h"
#include"rngs.h"
#include"assert_true.h"
#include<stdio.h>
#include<stdlib.h>

void resetGame(struct gameState* state) {
  int numPlayers = 3;
  int* cards = kingdomCards(
    feast,
    adventurer,
    council_room,
    smithy,
    village,
    steward,
    gardens,
    mine,
    tribute,
    great_hall
  );
  initializeGame(numPlayers, cards, 12345, state);
}

void giveEachPlayerFiveCardsInEachPile(struct gameState* state) {
  int player;
  for (player=0; player<3; player++) {
    state->handCount[player] = 5;
    state->deckCount[player] = 5;
    state->discardCount[player] = 5;
    int index;
    for (index=0; index<5; index++) {
     state->hand[player][index] = curse;
     state->deck[player][index] = curse;
     state->discard[player][index] = curse;
    }
  }
}


void debugPlayers(struct gameState* state) {
  printf("coin: %d, actions: %d", state->coins, state->numActions);
  int i;
  for (i=0; i<3; i++) {
    printf("Player %d h: %d, dk: %d, d: %d\n", i, state->handCount[i], state->deckCount[i], state->discardCount[i]);
  }
}

void testTribute() {
  struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
  if (!state) return;
  int returnValue;
  int player;

  // test for each player
  for (player=0; player < 3; player++) {
    int nextPlayer = (player + 1) % 3;
    int prevPlayer = (nextPlayer + 1) % 3; // I don't remember negative modulus, but it's probably wrong

    printf("\n\nPlayer %d\n", player + 1);
    // Test against opponent with no cards
    resetGame(state);
    giveEachPlayerFiveCardsInEachPile(state);
    state->hand[player][0] = tribute;
    state->deckCount[nextPlayer] = 0;
    state->discardCount[nextPlayer] = 0;
    state->coins = 0; // we get coins from our opening hand in resetGame

    printf("Play tribute against opponent with no cards\n");
    returnValue = performTributeCardEffect(player, 0, state);
    assertTrue(returnValue == 0,
               "", "Expected tribute to return 0");
    assertTrue(state->handCount[player] == 4,
               "", "Expected player handCount to be 4");
    assertTrue(state->discardCount[player] == 6,
               "", "Expected player discardCount to be 6");
    assertTrue(state->deckCount[player] == 5,
               "", "Expected player deckCount to be 5");
    assertTrue(state->numActions == 1,
               "", "Expected numActions to be 1");
    assertTrue(state->coins == 0,
               "", "Expected coins to be 0");
    // next player should have done nothing
    assertTrue(state->handCount[nextPlayer] == 5,
               "", "Expected next player handCount to be 5");
    assertTrue(state->discardCount[nextPlayer] == 0,
               "", "Expected next player discardCount to be 0");
    assertTrue(state->deckCount[nextPlayer] == 0,
               "", "Expected next player deckCount to be 0");
    // previous player should have done nothing
    assertTrue(state->handCount[prevPlayer] == 5,
               "", "Expected previous player handCount to be 5");
    assertTrue(state->discardCount[prevPlayer] == 5,
               "", "Expected previous player discardCount to be 5");
    assertTrue(state->deckCount[prevPlayer] == 5,
               "", "Expected previous player deckCount to be 5");

    // Test against opponent with 1 treasure card in deck 
    resetGame(state);
    giveEachPlayerFiveCardsInEachPile(state);
    state->hand[player][1] = tribute; // change position of tribute in each scenario
    state->deckCount[nextPlayer] = 1;
    state->deck[nextPlayer][0] = copper;
    state->discardCount[nextPlayer] = 0;
    state->coins = 0;

    printf("Play tribute against opponent with 1 treasure card\n");
    returnValue = performTributeCardEffect(player, 1, state);
    assertTrue(returnValue == 0,
               "", "Expected tribute to return 0");
    assertTrue(state->handCount[player] == 4,
               "", "Expected player handCount to be 4");
    assertTrue(state->discardCount[player] == 6,
               "", "Expected player discardCount to be 6");
    assertTrue(state->deckCount[player] == 5,
               "", "Expected player deckCount to be 5");
    assertTrue(state->numActions == 1,
               "", "Expected numActions to be 1");
    assertTrue(state->coins == 2,
               "", "Expected to recieve 2 coins");
    // next player should have done nothing
    assertTrue(state->handCount[nextPlayer] == 5,
               "", "Expected next player handCount to be 5");
    assertTrue(state->discardCount[nextPlayer] == 1,
               "", "Expected next player discardCount to be 1");
    assertTrue(state->deckCount[nextPlayer] == 0,
               "", "Expected next player deckCount to be 0");
    // previous player should have done nothing
    assertTrue(state->handCount[prevPlayer] == 5,
               "", "Expected previous player handCount to be 5");
    assertTrue(state->discardCount[prevPlayer] == 5,
               "", "Expected previous player discardCount to be 5");
    assertTrue(state->deckCount[prevPlayer] == 5,
               "", "Expected previous player deckCount to be 5");

    // test other treasure cards. Only worry about coins: other failures should have been caught above
    int treasure;
    for (treasure = silver; treasure <= gold; treasure++) {
      resetGame(state);
      giveEachPlayerFiveCardsInEachPile(state);
      state->hand[player][2] = tribute;
      state->deckCount[nextPlayer] = 1;
      state->deck[nextPlayer][0] = treasure;
      state->discardCount[nextPlayer] = 0;
      state->coins = 0;

      returnValue = performTributeCardEffect(player, 2, state);
      assertTrue(returnValue == 0, "", "Expected tribute to return 0");
      assertTrue(state->coins == 2, "", "Expected to receive 2 coins");
    }
 
    // Test against opponent with 1 action card in discard 
    resetGame(state);
    giveEachPlayerFiveCardsInEachPile(state);
    state->hand[player][3] = tribute; // change position of tribute in each scenario
    state->discardCount[nextPlayer] = 1;
    state->discard[nextPlayer][0] = adventurer;
    state->deckCount[nextPlayer] = 0;
    state->coins = 0;

    printf("Play tribute against opponent with 1 action card\n");
    returnValue = performTributeCardEffect(player, 3, state);
    assertTrue(returnValue == 0,
               "", "Expected tribute to return 0");
    assertTrue(state->handCount[player] == 4,
               "", "Expected player handCount to be 4");
    assertTrue(state->discardCount[player] == 6,
               "", "Expected player discardCount to be 6");
    assertTrue(state->deckCount[player] == 5,
               "", "Expected player deckCount to be 5");
    assertTrue(state->numActions == 3,
               "", "Expected numActions to be 3");
    assertTrue(state->coins == 0,
               "", "Expected coins to not change");
    // next player should have done nothing
    assertTrue(state->handCount[nextPlayer] == 5,
               "", "Expected next player handCount to be 5");
    assertTrue(state->discardCount[nextPlayer] == 1,
               "", "Expected next player discardCount to be 1");
    assertTrue(state->deckCount[nextPlayer] == 0,
               "", "Expected next player deckCount to be 0");
    // previous player should have done nothing
    assertTrue(state->handCount[prevPlayer] == 5,
               "", "Expected previous player handCount to be 5");
    assertTrue(state->discardCount[prevPlayer] == 5,
               "", "Expected previous player discardCount to be 5");
    assertTrue(state->deckCount[prevPlayer] == 5,
               "", "Expected previous player deckCount to be 5");

    // test other action cards. Only worry about actions: other failures should have been caught above
    int action;
    for (action = council_room; action <= treasure_map; action++) {
      resetGame(state);
      giveEachPlayerFiveCardsInEachPile(state);
      state->hand[player][4] = tribute;
      state->discardCount[nextPlayer] = 1;
      state->discard[nextPlayer][0] = action;
      state->deckCount[nextPlayer] = 0;
      state->coins = 0;

      returnValue = performTributeCardEffect(player, 4, state);
      assertTrue(returnValue == 0, "", "Expected tribute to return 0");
      assertTrue(state->numActions == 3, "", "Expected to receive 2 actions");
    }
  }
}

int main() {
  testTribute();
  return 0;
}
