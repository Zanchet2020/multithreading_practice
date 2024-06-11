#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
  size_t size;
  int * data;
} Vec;

void merge_sort_mt(Vec v) {}



void merge(Vec v, Vec a, Vec b){
  
}

void merge_sort(Vec v){
  if(v.size == 0) return;
  Vec a, b;
  size_t middle = v.size / 2;
  a.data = v.data;
  a.size = middle;
  b.data = v.data + middle + 1;
  b.size = v.size - middle;
  merge_sort(a);
  merge_sort(b);
  merge(v,a,b);
  //  printf("a.size = %zu     b.size = %zu\n", a.size, b.size);
}

int main(int argc, char*argv[]){
  int N = atoi(argv[1]);
  Vec v = {
    .data =(int*) malloc(N * sizeof(int)),
    .size = N
  };
  merge_sort(v);
  return 0;  
}
