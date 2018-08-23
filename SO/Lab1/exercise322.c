#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>

int* collatzConjecture(unsigned int n, int* result) {
  int i = 0;
  result[i] = n;
  while(n != 1) {
    if(n % 2 == 0) {
      n /= 2;
    } else {
      n = (3 * n) + 1;
    }
    i++;
    result[i] = n;
  }
  return result;
}
void printCollatzConjecture(int* toPrint) {
  int i = 0;
  while(toPrint[i] != 1){
      printf("%d,", toPrint[i]);
      i++;
  }
  printf("%d\n", toPrint[i]);
}

int main(int argc, char *args[]){
  int* result;
  int COLLATZ_NUMBER;
  const int SHARED_SIZE = 8192;
  const char *SHARED_NAME = "OS";
  int SHARED_MEMORY;
  pid_t pid;

  SHARED_MEMORY = shm_open(SHARED_NAME, O_CREAT | O_RDWR, 0666);

  if (ftruncate(SHARED_MEMORY, SHARED_SIZE) == -1){
    printf("Error al crear la memoria compartida.\n");
    exit(1);
  }

  COLLATZ_NUMBER = atoi(args[1]);
  pid = fork();

  if(pid == 0){
    result = (int *)mmap(0, SHARED_SIZE, PROT_WRITE, MAP_SHARED, SHARED_MEMORY, 0);
    collatzConjecture(COLLATZ_NUMBER, result);
  }
  else if(pid > 0){
      wait(NULL);
      result = mmap(0, SHARED_SIZE, PROT_READ, MAP_SHARED, SHARED_MEMORY, 0);
      printCollatzConjecture(result);
  }else{
    printf("Error al crear el proceso hijo.\n");
    exit(1);
  }

  return 0;
}
