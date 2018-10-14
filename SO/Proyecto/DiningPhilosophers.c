/*
 *  Jhordan Alexander Gómez Tapasco
 *        2016074382
 *  Proyecto 1
 *  Para compilar: cc -pthread -o Proyecto_2 DiningPhilosophers.c
 *  Ejecutar: ./Proyecto_2
 */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>


enum philosophersstatess{eating, hungry, thinking};

#define REPETICIONES 420
#define LEFT (phnum + 4) % 5
#define RIGHT (phnum + 1) % 5

int philosophersStates[5];
int philosophers[5] = { 0, 1, 2, 3, 4 };

sem_t mutexLock;
sem_t S[5];

void test(int phnum){
  if (philosophersStates[phnum] == hungry && philosophersStates[LEFT] != eating && philosophersStates[RIGHT] != eating) {
    philosophersStates[phnum] = eating;
    sleep(2);

    printf("Los tenedores %d y %d son tomados por el filosofo %d.\n", LEFT + 1, phnum + 1, phnum + 1);

    printf("Filosofo %d comiendo.\n", phnum + 1);
    sem_post(&S[phnum]);
  }
}

void take_fork(int phnum){
  sem_wait(&mutexLock);
  philosophersStates[phnum] = hungry;
  printf("El filosofo %d tiene hambre.\n", phnum + 1);

  test(phnum);
  sem_post(&mutexLock);

  sem_wait(&S[phnum]);
  sleep(1);
}

void put_fork(int phnum){
  sem_wait(&mutexLock);
  philosophersStates[phnum] = thinking;

  printf("Los tenedores %d y %d son regresados por el filosofo %d.\n",LEFT + 1, phnum + 1, phnum + 1);
  printf("El filosofo %d está pensando.\n", phnum + 1);

  test(LEFT);
  test(RIGHT);

  sem_post(&mutexLock);
}

void* philospher(void* num){
  while (420) {
    int* i = num;

    sleep(1);
    take_fork(*i);
    sleep(0);
    put_fork(*i);
  }
}

int main(){
  int i;
  pthread_t idThread[5];
  sem_init(&mutexLock, 0, 1);

  for (i = 0; i < 5; i++){
    sem_init(&S[i], 0, 0);
  }

  for (i = 0; i < 5; i++) {
    pthread_create(&idThread[i], NULL, philospher, &philosophers[i]);
    printf("El filosofo %d está pensando.\n", i + 1);
  }

  for (i = 0; i < 5; i++){
    pthread_join(idThread[i], NULL);
  }
}
