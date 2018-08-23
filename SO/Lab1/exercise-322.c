#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>
#include <sys/mman.h>
#include <string.h>

int* collatzConjecture(unsigned int n) {
  int* result = malloc(420 * sizeof(int));
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

void* createSharedMemory(size_t size){
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_ANONYMOUS | MAP_SHARED;

    return mmap(NULL, size, protection, visibility, 0, 0);
}

int main(int argc, char *args[]) {
    int* result;
    void* sharedMessage = createSharedMemory(420);

    memcpy(sharedMessage, args[1], sizeof(args[1]));

    if (fork() == 0){
        result = collatzConjecture(atoi(args[1]));
        memcpy(sharedMessage, result, sizeof(result));
    }else{
        wait(NULL);
        printf("caca %d \n", result[0]);
    }

    return 0;
}
