/*------------------------------------------------------------------------------
 * randomstring.c
 * Nigel Robbins
 *
 * In order to cause an error in the execution of testme.c, I needed to bring
 * the "state" value up to 9 and set the "s" value to "reset". Since increasing
 * "state" can only be done with the characters in '[({ ax})]', I made inputChar
 * return only characters from that set.
 *
 * In a real-world scenario where I didn't have access to the code under test,
 * I probably wouldn't have a subset of characters this precise. However, to me
 * these look like they may be command characters a user might enter, rather
 * than simple characters in text. For instance, they may be inputs for
 * controlling a game avatar. I would certainly test a variety of command
 * characters in a random tester, so I felt comfortable writing inputChar this
 * way.
 *
 * For inputString I wrote code which would produce arbitrary lowercase strings
 * of many lengths, with a high weighting towards the string "reset". My
 * justification is that perhaps the user is inputting text based commands to
 * the game as well as pressing 'a' and '[' to control the avatar, for instance
 * if when selecting menu options. The special string "reset" can be entered to
 * restart the level. In a scenario like this, with black box random testing, I
 * would try to bias return values toward other commands the user would enter 
 * as well, like "quit" or "yes". I would still use random strings, for things
 * like misspelling or having a cat run across the keyboard. Since this is not
 * a black box test, I only biased toward "reset".
 * 
 * 
 * One conclusion drawn from this test is that defining the space of the random
 * inputs is the most important part of writing good random tests. 1,000,000
 * tests might run quickly, but they only cover about 4.2 characters in a truly
 * random string of lowercase letters. (26 ^ 4.2 is 1,000,000). If the string
 * which makes your test fail is 5 characters, you need ~26,000,000 runs to have
 * a decent chance of catching it. If you test strings of different lengths,
 * like I did, you start to need hundreds of millions of tests.
 *
 * On the other hand, the inputChar method was extremely effective at updating
 * state. As a test, I returned random bytes with (char)(rand() % 256) and it
 * never seemed to take more than 3000 tests to get state up to 9. This makes
 * sense, because there are ten characters I need to see and a 1/256 chance to
 * see them, so I would expect about 2560 runs to see all the characters.
 *
 * By biasing my random test to have a 1 in 1000 chance to return a string
 * which was considered "dangerous", brought the number of tests I would need
 * to run to catch an error from hundreds of millions to thousands. Testing
 * the entire input space is impractical, so carefully biasing results toward
 * areas your intuition (or knowledge of the code, in this case) tells you is
 * most likely to produce bugs will significantly improve the odds of catching
 * a bug when it exists.
 *
 */
