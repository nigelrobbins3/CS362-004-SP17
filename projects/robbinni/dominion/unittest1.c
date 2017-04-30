/* unittest1.c
 * Nigel Robbins
 * Test the getCost function in dominion.c
 */

#include"dominion.h"
#include"dominion_helpers.h"
#include"rngs.h"
#include"assert_true.h"
#include<stdio.h>

void testGetCost() {
  int cost;

  // curse
  cost = getCost(curse);
  assertTrue(cost == 0, "", "Expected curse to cost 0\n");
  // estate
  cost = getCost(estate);
  assertTrue(cost == 2, "", "Expected estate to cost 2\n");
  // duchy
  cost = getCost(duchy);
  assertTrue(cost == 5, "", "Expected duchy to cost 5\n");
  // province
  cost = getCost(province);
  assertTrue(cost == 8, "", "Expected province to cost 8\n");
  // copper
  cost = getCost(copper);
  assertTrue(cost == 0, "", "Expected copper to cost 0\n");
  // silver
  cost = getCost(silver);
  assertTrue(cost == 3, "", "Expected silver to cost 3\n");
  // gold
  cost = getCost(gold);
  assertTrue(cost == 6, "", "Expected gold to cost 6\n");
  // adventurer
  cost = getCost(adventurer);
  assertTrue(cost == 6, "", "Expected adventurer to cost 6\n");
  // council_room
  cost = getCost(council_room);
  assertTrue(cost == 5, "", "Expected concil room to cost 5\n");
  // feast
  cost = getCost(feast);
  assertTrue(cost == 4, "", "Expected feast to cost 4\n");
  // gardens
  cost = getCost(gardens);
  assertTrue(cost == 4, "", "Expected gardens to cost 4\n");
  // mine
  cost = getCost(mine);
  assertTrue(cost == 5, "", "Expected mine to cost 5\n");
  // remodel
  cost = getCost(remodel);
  assertTrue(cost == 4, "", "Expected remodel to cost 4\n");
  // smithy
  cost = getCost(smithy);
  assertTrue(cost == 4, "", "Expected smithy to cost 4\n");
  // village
  cost = getCost(village);
  assertTrue(cost == 3, "", "Expected village to cost 3\n");
  // baron
  cost = getCost(baron);
  assertTrue(cost == 4, "", "Expected baron to cost 4\n");
  // great_hall
  cost = getCost(great_hall);
  assertTrue(cost == 3, "", "Expected great hall to cost 3\n");
  // minion
  cost = getCost(minion);
  assertTrue(cost == 5, "", "Expected minion to cost 5\n");
  // steward
  cost = getCost(steward);
  assertTrue(cost == 3, "", "Expected steward to cost 3\n");
  // tribute
  cost = getCost(tribute);
  assertTrue(cost == 5, "", "Expected tribute to cost 5\n");
  // ambassador
  cost = getCost(ambassador);
  assertTrue(cost == 3, "", "Expected ambassador to cost 3\n");
  // cutpurse
  cost = getCost(cutpurse);
  assertTrue(cost == 4, "", "Expected cutpurse to cost 4\n");
  // embargo
  cost = getCost(embargo);
  assertTrue(cost == 2, "", "Expected embargo to cost 2\n");
  // outpost
  cost = getCost(outpost);
  assertTrue(cost == 5, "", "Expected outpost to cost 5\n");
  // salvager
  cost = getCost(salvager);
  assertTrue(cost == 4, "", "Expected salvager to cost 4\n");
  // sea hag
  cost = getCost(sea_hag);
  assertTrue(cost == 4, "", "Expected sea hag to cost 4\n");
  // treasure_map
  cost = getCost(treasure_map);
  assertTrue(cost == 4, "", "Expected treasure_map to cost 4\n");
}

int main() {
  testGetCost();
  return 0;
}
