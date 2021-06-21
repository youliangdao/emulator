#include <stdio.h>
#include <stdlib.h>

int inc(int v){
  return v++;
}

int main(void)
{
  typedef int func_t(int);
  int (*arr1[2]) (int) = {&inc, NULL};
  func_t *arr2[2] = {&inc, NULL};
  return 0;
}

