#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXHEX 100

int alternate_htoi(char hex[]);

int main(void)
{
  char hex[MAXHEX] = "0Xf23";

  printf("%s\n%i\n", hex, alternate_htoi(hex));

  return 0;
}

// Converts string of hexadecimal number into equivalent integer value
int alternate_htoi(char s[])
{
  int n = 0, i;

  // Skip the first two characters if string starts with 0x or 0X
  int limit = (s[0] == '0') ? 2 : 0;

  int s_length = strlen(s) - 1;

  for (i = s_length; i >= limit; i--)
  {
    if (s[i] >= '0' && s[i] <= '9')
    {
      n += pow(16, s_length - i) * (s[i] - '0');
    }
    else if (s[i] >= 'A' && s[i] <= 'F')
    {
      n += pow(16, s_length - i) * (s[i] - 'A' + 10);
    }
    else if (s[i] >= 'a' && s[i] <= 'f')
    {
      n += pow(16, s_length - i) * (s[i] - 'a' + 10);
    }
    else
    {
      printf("Error: invalid input.\n");
      return 1;
    }
  }

  return n;
}
