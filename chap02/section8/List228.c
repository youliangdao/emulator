int inc(int v){
  return v++;
}

typedef int func_t(int);
func_t *ptr2 = &inc;