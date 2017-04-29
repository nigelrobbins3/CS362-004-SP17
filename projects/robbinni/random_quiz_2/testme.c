#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // Select a random "command" chacter
    int randomIndex = rand() % 9;
    return "[({ ax})]"[randomIndex];
}

char *inputString()
{
    // simulate text input between 1 and 10 characters long
    int stringLength = rand() % 10 + 1;
    char str[11]; // 10 chars and a terminator 
    int index = 0;

    // 1 in 1000 chance to return "reset"
    if (rand() % 1000 == 0)
        return "reset";

    while(index < stringLength) {
        int randIndex = rand() % 27; // 26 lowercase letters and ' '
        str[index] = "abcdefghijklmnopqrstuvwxyz "[randIndex];
        index++;
    }
    str[index] = '\0';
	
    return str;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
