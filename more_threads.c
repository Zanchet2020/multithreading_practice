#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

void* print_id(void * id){
  uint8_t time = rand()%4;
  sleep(time);
  printf("Thread ID: %d\n", *(int*)id);
  return NULL;
}

int main(int argc, char*argv[]){
  srand(time(NULL));
  pthread_t threads[10];
  int N = sizeof(threads)/sizeof(threads[0]);
  for(int i = 0; i < N; ++i){
    pthread_create(&threads[i], NULL, &print_id, (void*)&threads[i]);
  }

  pthread_exit(NULL);
  return 0;
}
