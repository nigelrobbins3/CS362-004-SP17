CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

assert_true.o: assert_true.h assert_true.c dominion.o
	gcc -c assert_true.c -g $(CFLAGS)

tests: unittestresults.out

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c assert_true.o dominion.o rngs.o
	echo "Result for running unit tests:" > unittestresults.out

	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 rngs.o dominion.o assert_true.o unittest1.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 rngs.o dominion.o assert_true.o unittest2.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 rngs.o dominion.o assert_true.o unittest3.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 rngs.o dominion.o assert_true.o unittest4.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 rngs.o dominion.o assert_true.o cardtest1.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 rngs.o dominion.o assert_true.o cardtest2.c $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 rngs.o dominion.o assert_true.o cardtest3.c $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 rngs.o dominion.o assert_true.o cardtest4.c $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

randomtests: randomtestcard1.out randomtestcard2.out randomtestadventurer.out

randomtestcard1.out: randomtestcard1.c assert_true.o dominion.o rngs.o
	echo "Result for random testing:" > randomtestcard1.out

	gcc -o randomtestcard1 rngs.o dominion.o assert_true.o randomtestcard1.c $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out
	gcov -b -f dominion.c >> randomtestcard1.out

randomtestcard2.out: randomtestcard2.c assert_true.o dominion.o rngs.o
	echo "Result for random testing:" > randomtestcard2.out

	gcc -o randomtestcard2 rngs.o dominion.o assert_true.o randomtestcard2.c $(CFLAGS)
	randomtestcard2 >> randomtestcard2.out
	gcov -b -f dominion.c >> randomtestcard2.out

randomtestadventurer.out: randomtestadventurer.c assert_true.o dominion.o rngs.o
	echo "Result for random testing:" > randomtestadventurer.out

	gcc -o randomtestadventurer rngs.o dominion.o assert_true.o randomtestadventurer.c $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	gcov -b -f dominion.c >> randomtestadventurer.out

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
	rm -f badTestDrawCard testDrawCard unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	rm -f randomtestcard1 randomtestcard2 randomtestadventurer
