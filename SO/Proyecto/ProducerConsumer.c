/*
 *  Jhordan Alexander Gómez Tapasco
 *        2016074382
 *  Proyecto 1
 *  Para compilar: cc -pthread -o Proyecto_3 ProducerConsumer.c
 *  Ejecutar: ./Proyecto_3 <sleep> <cantidad producers> <cantidad consumers>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "buffer.h"

buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutexLock;
sem_t full, empty;
int count, in, out;

int insert_item(buffer_item item){
 int success;
 sem_wait(&empty);
 pthread_mutex_lock(&mutexLock);

 if (count != BUFFER_SIZE){
   buffer[in] = item;
   in = (in + 1) % BUFFER_SIZE;
   count++;
   success = 0;
 }else{
   success = -1;
 }

 pthread_mutex_unlock(&mutexLock);
 sem_post(&full);

 return success;
}

int remove_item(buffer_item *item){
 int success;

 sem_wait(&full);
 pthread_mutex_lock(&mutexLock);

 if (count != 0){
   *item = buffer[out];
   out = (out + 1) % BUFFER_SIZE;
   count--;
   success = 0;
 }
 else{
   success = -1;
 }

 pthread_mutex_unlock(&mutexLock);
 sem_post(&empty);

 return success;
}

void *producer(void *param){
 buffer_item item;
 while(1){
   sleep(rand() % 5 + 1);

   item = rand();
   if(insert_item(item)){
     printf("Error occured\n");
   }else{
     printf("Item %d (Producer)\n", item);
   }
 }
}


void *consumer(void *param){
 buffer_item item;
 while(1){
   sleep(rand() % 5 + 1);

   if(remove_item(&item)){
     printf("Error*\n");
   }else{
     printf("Item %d (Consumer)\n", item);
   }
 }
}



int main(int argc, char **argv){
  /* 1. -------------------------------------------- Get command line arguments argv[1],argv[2],argv[3] --------------------------------*/
  if (argc < 4){
    printf("Hace falta 1 o más parámetros.\n");
    exit(0);
  }

  if (!validateEntry(argv[1]) || !validateEntry(argv[2]) || !validateEntry(argv[3])){
    printf("Los parámetros deben ser número enteros positivos mayores a 0.\n");
    exit(0);
  }

  int sleepTime = atoi(argv[1]);
  int producersCant = atoi(argv[2]);
  int consumersCant = atoi(argv[3]);

 /* 2. ------------------------------------------------------ Initialize buffer --------------------------------------------------*/
 int i;
 srand(time(NULL));
 pthread_mutex_init(&mutexLock, NULL);
 sem_init(&empty, 0, BUFFER_SIZE);
 sem_init(&full, 0, 0);

 count = 0;
 in = 0;
 out = 0;

/* 3. -------------------------------------------------- Create producer thread(s) -------------------------------------------------*/
 pthread_t producers[producersCant];
 for(i = 0; i < producersCant; i++){
   pthread_create(&producers[i], NULL, producer, NULL);
 }

 /* 4. ------------------------------------------------- Create consumer thread(s) ---------------------------------------------*/
 pthread_t consumers[consumersCant];
 for(i = 0; i < consumersCant; i++){
   pthread_create(&consumers[i], NULL, consumer, NULL);
 }

 /* 5. ---------------------------------------------------------- Sleep -----------------------------------------------------*/

 for(i = 0; i < producersCant; i++){
    pthread_join(producers[i], NULL);
 }
 for(i = 0; i < consumersCant; i++){
   pthread_join(consumers[i], NULL);
 }

 sleep(sleepTime);

 /* 6. ---------------------------------------------------------- Exit -----------------------------------------------------*/
 return 0;
}
