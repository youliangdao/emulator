#include <stdio.h>

int main(void)
{
  int arr[4];
  int *x = &arr[0];

  x[0] = 1;
  arr[1] = 2;

  *(x + 2) = 3;
  *(arr + 3) = 4;

  for (int i = 0; i < 4; i++)
  {
    printf("%d番目の要素：%d\n", i + 1, arr[i]);
  }

  return 0;
}
