#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* async_func(void * a){
  sleep(3);
  printf("Inside thread\n");
  return NULL;
}

int main(int argc, char*argv[]){
  pthread_t new_thread;
  pthread_create(&new_thread, NULL, &async_func, NULL);
  pthread_join(new_thread, NULL);
  return 0;
}
