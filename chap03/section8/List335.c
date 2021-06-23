#include <stdio.h>

size_t my_strlen(const char* s){
  static int count = 0;
  size_t i;

  count++;
  printf("strlen: called %d time.\n", count);

  for ( i = 0; s[i]; i++);
  return i;
}

int main(void)
{
  const char* str = "hello";
  int len = my_strlen(str);
  printf("%d", len);
  return 0;
}

