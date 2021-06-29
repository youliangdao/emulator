int abs(int a, int b){
  if (a < b) {
    return b;
  } else
  {
    return a;
  }
}

int main(void)
{
  return abs(5, 3);
}
