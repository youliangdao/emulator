#include <stdio.h>
#include <stdlib.h>

int inc(int v){
  return v++;
}

int main(void)
{
  int (*arr[2])(int) = {&inc, NULL};

  typedef int func(int);
  func *ptr[2] = {&inc, NULL};
}

