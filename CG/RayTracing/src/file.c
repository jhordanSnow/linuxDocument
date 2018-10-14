#include "headers/common.h"

#define SWAP(x) ( ((x) << 24) | \
         (((x) << 8) & 0x00ff0000) | \
         (((x) >> 8) & 0x0000ff00) | \
         ((x) >> 24) )

#define FIX(x) (*(unsigned *)&(x) = \
         SWAP(*(unsigned *)&(x)))


void WritePixel(Color pixelColor, FILE *file);

void FileToFrameBuffer(char* file){
  int i,j;
  FILE *fptr;

  if ((fptr = fopen(file,"r")) == NULL) {
    fprintf(stderr, "Error al abrir el archivo \"%s\"\n", file);
    exit(-1);
  }

  /* Read the header */
  fread(&H_SIZE, sizeof(int), 1, fptr);
  FIX(H_SIZE);

  fread(&V_SIZE, sizeof(int), 1, fptr);
  FIX(V_SIZE);


  /* Allocate the Matrix */
  AllocateFrameBuffer();

  /* Fill the Matrix */
  for (j = 0; j < V_SIZE; j++) {
    for (i = 0; i < H_SIZE; i++) {
       FrameBuffer[i][j] = CreateColor(fgetc(fptr), fgetc(fptr), fgetc(fptr), fgetc(fptr));
    }
  }

  fclose(fptr);
}


void FrameBufferToFile(char* file){
  int i,j;
  FILE *fptr;

  if ((fptr = fopen(file,"w")) == NULL) {
    fprintf(stderr, "Error al abrir el archivo \"%s\"\n", file);
    exit(-1);
  }

  /* Transform to 4 bytes */
  int hsize = H_SIZE;
  FIX(hsize);
  int vsize = V_SIZE;
  FIX(vsize);

  fwrite(&hsize, sizeof(int), 1, fptr);
  fwrite(&vsize, sizeof(int), 1, fptr);

  /* Fill the Matrix */
  for (j = 0; j < V_SIZE; j++) {
    for (i = 0; i < H_SIZE; i++) {
      WritePixel(FrameBuffer[i][j], fptr);
    }
  }

  fclose(fptr);
}

void WriteColorComponent(double component, FILE* file){
  int componentInt = component * MAX_COLOR;
  fwrite(&componentInt, sizeof(unsigned char), 1, file);
}


void WritePixel(Color pixelColor, FILE *file){
  WriteColorComponent(pixelColor.A, file);
  WriteColorComponent(pixelColor.RGB.X, file);
  WriteColorComponent(pixelColor.RGB.Y, file);
  WriteColorComponent(pixelColor.RGB.Z, file);

}
