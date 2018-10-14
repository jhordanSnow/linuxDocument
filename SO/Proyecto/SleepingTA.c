/*
 *  Jhordan Alexander Gómez Tapasco
 *        2016074382
 *  Proyecto 1
 *  Para compilar: cc -pthread -o Proyecto_1 SleepingTA.c
 *  Ejecutar: ./Proyecto_1
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int CANT_STUDENTS = 5;

pthread_t* studentsThreads;
sem_t studentInside;

pthread_t assistantThread;
sem_t assistantNap;

sem_t chairsWait[3];
pthread_mutex_t mutexLock;

int chairsCount = 0;
int current = 0;


void* assistant(){
  while(1){
    sem_wait(&assistantNap);
    printf("Profesor Asistente es despertado por un estudiante\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    while (1) {
      pthread_mutex_lock(&mutexLock);

      if(chairsCount == 0){
        pthread_mutex_unlock(&mutexLock);
        break;
      }

      sem_post(&chairsWait[current]);
			chairsCount--;
      printf("Silla liberada, quedan %d\n", 3 - chairsCount);
			current = (current + 1) % 3;
      pthread_mutex_unlock(&mutexLock);

      printf("Asistente ocupado ayudando un estudiante.\n");
			sleep(5);
			sem_post(&studentInside);
      usleep(1000);
    }
  }
}
void* student(void *idThread){
  int studentTime;

  while(1){
    printf("Estudiante %ld.\n", (long)idThread);
    studentTime = rand() % 12 + 1;
    sleep(studentTime);

    printf("Estudiante %ld ocupa ayuda.\n", (long)idThread);
    pthread_mutex_lock(&mutexLock);
    int count = chairsCount;
    pthread_mutex_unlock(&mutexLock);

    if(count < 3){
      if(count == 0){
        sem_post(&assistantNap);
      }else{
        printf("Estudiante %ld se sienta a esperar el asistente. \n", (long)idThread);
      }

      pthread_mutex_lock(&mutexLock);
      int index = (current + chairsCount) % 3;
      chairsCount++;
      printf("Estudiante se sienta a esperar el asistente, quedan %d sillas.\n", 3 - chairsCount);
      pthread_mutex_unlock(&mutexLock);


      sem_wait(&chairsWait[index]);
      printf("El estudiante %ld tiene ayuda del asistente. \n", (long)idThread);
      sem_wait(&studentInside);
      printf("Estudiante %ld deja de recibir ayuda del asistente.\n",(long)idThread);
    }
  }

}

int main(int argc, char* argv[]){
	int id = 0;
	srand(time(NULL));

	sem_init(&assistantNap, 0, 0);
	sem_init(&studentInside, 0, 0);
	for(id = 0; id < 3; ++id){
    sem_init(&chairsWait[id], 0, 0);
  }

	pthread_mutex_init(&mutexLock, NULL);
	studentsThreads = (pthread_t*) malloc(sizeof(pthread_t)*CANT_STUDENTS);

	pthread_create(&assistantThread, NULL, assistant, NULL);
	for(id = 0; id < CANT_STUDENTS; id++){
    pthread_create(&studentsThreads[id], NULL, student,(void*) (long)id);
  }

	pthread_join(assistantThread, NULL);
	for(id = 0; id < CANT_STUDENTS; id++){
		pthread_join(studentsThreads[id], NULL);
  }

	free(studentsThreads);
	return 0;
}
