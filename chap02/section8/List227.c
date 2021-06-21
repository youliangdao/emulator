int inc(int v){
  return v++;
}

int (*ptr)(int) = &inc;