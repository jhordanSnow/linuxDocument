/*
 *  Jhordan Alexander Gómez Tapasco
 *        2016074382
 *  Laboratorio 2
 *  Para compilar: cc -pthread -o main Lab2.c
 *  Ejecutar: ./main
 */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int MAX_SECONDS = 2;
int MAX_THREADS = 100;
int MAX_PID = 5000;
int MIN_PID = 500;
int *pid_map;
pthread_mutex_t mutex;

int allocate_map();
int allocate_pid();
void release_pid(int pid);
void *allocator(void *parameter);

int main(void) {
    int i;
    pthread_t thread_ids[MAX_THREADS];
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    printf("\n.........................................................................\n");

    if (allocate_map() == -1) {
        printf("Error al asignar la estructura para los pids\n");
        return -1;
    }

    for (i = 0; i < MAX_THREADS; i++) {
        pthread_create(&thread_ids[i], NULL, allocator, NULL);
    }

    for (i = 0; i < MAX_THREADS; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    if (pid_map != NULL) {
        free(pid_map);
    }

    printf(".........................................................................\n");
    return 0;
}


int allocate_map() {
  pid_map = calloc(MAX_PID, sizeof(int));

	for(int i = 0; i < MAX_PID; i++) {
		pid_map[i] = 0;
	}

  return (pid_map != NULL) ? 1 : -1;
}

int allocate_pid() {
  int i = 0;
	while (pid_map[i] != 0) {
		i++;
	}

	if (i + MIN_PID > MAX_PID) {
		return -1;
	}

	pid_map[i] = 1;

  return i + MIN_PID;
}

void release_pid(int pid) {
  if (pid < MIN_PID || pid > MAX_PID) {
		printf("Pid inválido, debe ser mayor a %i y menor a %i\n", MIN_PID, MAX_PID);
		return;
	}

	pid_map[pid - MIN_PID] = 0;
}

void *allocator(void *parameter) {
    int sleepTime = rand() % MAX_SECONDS;

    int pid = -1;
    while(pid == -1) {
        pthread_mutex_lock(&mutex);
        pid = allocate_pid();
        if (pid == -1) {
            printf("Error al asignar el pid.\n");
        }
        pthread_mutex_unlock(&mutex);
    }

    printf("pid %i activo.\n", pid, sleepTime);
    sleep(sleepTime);

    printf("pid %i liberado.\n", pid);
    release_pid(pid);

    return NULL;
}
