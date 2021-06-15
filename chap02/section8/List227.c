int inc(int v){
  return v + 1;
}

int (*ptr)(int) = &inc;