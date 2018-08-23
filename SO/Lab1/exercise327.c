#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>

int main( int argc, char* argv[] ) {
    int fdone[2];
    pid_t pid;
    char buffer[500];
    int readCounter;

    pipe(fdone);

    if(argc < 3) {
        printf( "Error, faltan parametros.\n");
        exit(1);
    }

    int readFile = open(argv[1], 0);
    int writeFile = open(argv[2], 0666);

    if (readFile == -1 || writeFile == -1) {
        printf("Error al abrir alguno de los archivos.\n");
        exit(1);
    }

    pid = fork();

    if(pid == 0) {
        close(fdone[1]);
        read(fdone[0], buffer, sizeof(buffer));
        write(writeFile, buffer, strlen(buffer));
        printf("Copiado terminado.\n");
    } else {
        close(fdone[0]);
        while((readCounter = read(readFile, buffer, sizeof(buffer)) > 0 )) {
          write(fdone[1], buffer, sizeof(buffer));
        }
        close(fdone[1]);
    }
}
