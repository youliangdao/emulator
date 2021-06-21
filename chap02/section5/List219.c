#include <string.h>

char* evil(char* a){
  char s[128];
  strcpy(s, a);
  return s;
}

int main(void)
{
  char* string = "あいうえお";
  evil(string);
  return 0;
}

