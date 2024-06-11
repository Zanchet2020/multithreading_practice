#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <limits.h>
// int active_thread_count;
// static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#define ARRAY_LEN (INT_MAX - 1000)
#define THREADS 300
#define POOL_SIZE (ARRAY_LEN / THREADS)

int min(int a, int b){
  return a > b ? b : a;
}

typedef struct{
  int * data;
  int size;
} Vec;

typedef struct{
  Vec v;
  int result;
} thread_data;

void* thread_adder(void * vector){
  thread_data *td = (thread_data*)vector;
  for(int i = 0; i < td->v.size; ++i){
    td->result += td->v.data[i];
  }
  return NULL;
}

int add_vector_mt(Vec v, int threads){
  int max_pool = v.size / threads;
  int num_of_threads = ceil((float)v.size / (float)max_pool);
  //active_thread_count = num_of_threads;
  thread_data *td = malloc(num_of_threads*sizeof(thread_data));
  pthread_t * thread_ids = malloc(num_of_threads * sizeof(pthread_t));

  //printf("Num of threads: %d\n", num_of_threads);
  
  for(int i = 0; i < num_of_threads; ++i){
    td[i].v.data = v.data + (i * max_pool);
    td[i].v.size = min((v.size - (i * max_pool)), max_pool);
    pthread_create(&thread_ids[i], NULL, &thread_adder, (void*)&td[i]);
  }
  
  //printf("Thread 0: %d\n", td[0].result);

  int sum = 0;
  for(int i = 0 ; i < num_of_threads; ++i){
    pthread_join(thread_ids[i], NULL);
    sum += td[i].result;
  }

  free(td);
  free(thread_ids);
  
  return sum;
}

int add_vector(Vec v){
  int sum = 0;
  for(int i = 0 ; i < v.size; ++i){
    sum += v.data[i];
  }
  return sum;
}

int main(int argc, char*argv[]){
  Vec v = {0};
  int size = ARRAY_LEN;
  int num_of_threads = THREADS;
  if(argc > 1){
    size = atoi(argv[1]);
    num_of_threads = atoi(argv[2]);
  }
  v.data = (int *)malloc(size * sizeof(int ));
  v.size = size;
  srand(time(NULL));
  printf("Summing a total of %d numbers, %d per thread\n\n", size, size/num_of_threads);
  for(int i = 0; i < size; ++i){
    v.data[i] = ((rand() % 10) - 5);
  }

  uint64_t start, end, result;
  printf("Starting multithreaded\n");

  start = clock();
  result = add_vector_mt(v, num_of_threads);
  end = clock();

  printf("Sum of vector multithread: %d     took %lf\n\n", result, (float)10*(end - start)/(float)CLOCKS_PER_SEC);

  printf("Starting singlethreaded\n");
  start = clock();
  result = add_vector(v);
  end = clock();

    printf("Sum of vector:           %d     took %lf\n", result, (float)10*(end - start)/(float)CLOCKS_PER_SEC);
  return 0;
}
