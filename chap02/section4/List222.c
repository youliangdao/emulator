#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
  //mallocの戻り値はvoid*だが、キャストなしでint*型の変数に代入できる
  int *p = malloc(sizeof(int) * 128);

  //memsetの第一引数はvoid*だが、キャストなしでint*型の変数を渡せる
  memset(p, 0, sizeof(int) * 128);
  return 0;
}
