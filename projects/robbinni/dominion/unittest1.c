/* unittest1.c
 * Nigel Robbins
 * Test the getCost function in dominion.c
 */

#include"dominion.h"
#include"dominion_helpers.h"
#include"rngs.h"
#include<stdio.h>

#define NOISY_TEST 1

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
int main() {
  int cost;

  // curse
  cost = getCost(curse);
  assertTrue(cost == 0, "Hurray!\n", "Or not :(\n");
  return 0;
}
