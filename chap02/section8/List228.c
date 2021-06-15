int inc(int v){
  return v++;
}

typedef int func(int);
func *ptr = &inc;