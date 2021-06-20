#include <stdio.h>

void mydiv(int a, int b, int *quot, int *rem){
  *quot = a / b;
  *rem = a % b;
  printf("商 = %d, 余り = %d", *quot, *rem);
}

int main(int argc, char const *argv[])
{
  int q;
  int r;
  mydiv(10, 3, &q, &r);

  return 0;
}
