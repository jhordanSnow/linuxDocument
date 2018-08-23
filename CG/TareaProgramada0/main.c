#include <math.h>
#include "main.h"

int H_SIZE;
int V_SIZE;
int CANT_LINES;
int CANT_TIMES;

void draw_lines();
extern void line5(int x0, int y0, int x1, int y1, void (*plotToUse)(int,int));
extern void line6(int x0, int y0, int x1, int y1, void (*plotToUse)(int,int));

void caca(int x, int y){
  printf("nani: %d %d\n", x, y);
}

int main(int argc, char** argv){

  if (argc < 4){
    printf("Hace falta 1 o más parámetros.\n");
    exit(0);
  }

  if (!validateEntry(argv[1]) || !validateEntry(argv[2]) || !validateEntry(argv[3])){
    printf("Los parámetros deben ser número enteros positivos mayores a 0.\n");
    exit(0);
  }

  H_SIZE = atoi(argv[1]);
  V_SIZE = H_SIZE;
  CANT_LINES = atoi(argv[2]);
  CANT_TIMES = atoi(argv[3]);

  if (CANT_TIMES <= 0 || CANT_LINES <= 0 || H_SIZE <= 0){
    printf("Los parámetros deben ser número enteros positivos mayores a 0.\n");
    exit(0);
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_STENCIL);
  glutInitWindowSize(H_SIZE,V_SIZE);
  glutCreateWindow("Proyecto 0: Lineas");
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(-0.5, H_SIZE + 0.5, -0.5, V_SIZE + 0.5);
  glutDisplayFunc(draw_lines);
  glutMainLoop();
}

void circleTest(void (*functionToUse) (int,int,int,int,void(*)(int, int)),  void (*plotToUse)(int,int)){
  int x, y;
  int centro = H_SIZE/2;
  int largo = centro;

  for (float i = 0; i < 360; i+=0.008) {
    x = (largo * cos(i)) + centro;
    y = (largo * sin(i)) + centro;
    functionToUse(centro, centro, x, y, plotToUse);
    glFlush();
  }
}

double testLines(void (*functionToUse) (int,int,int,int,void(*)(int, int)), void (*plotToUse)(int,int), int (*lineSet)[4]){
  clock_t startTime;
  double diffms;

  startTime = clock();

  /*circleTest(functionToUse, plotToUse);
  diffms = (double) (clock() - startTime)/(CLOCKS_PER_SEC/1000);
  return diffms;*/

  for (int i = 0; i < CANT_TIMES; i++) {
    for (int j = 0; j < CANT_LINES; j++) {
      functionToUse(lineSet[j][0], lineSet[j][1], lineSet[j][2], lineSet[j][3], plotToUse);
      glFlush();
    }
  }

  diffms = (double) (clock() - startTime)/(CLOCKS_PER_SEC/1000);
  return diffms;
}

void draw_lines(){
  int lineSet[CANT_LINES][4];
  double timeL1, timeL1Clean, timeL2, timeL2Clean,timeL3, timeL3Clean, timeL4, timeL4Clean, timeL5, timeL5Clean;

  srand(time(NULL));
  for (int i = 0; i < CANT_LINES; i++) {
    for (int j = 0; j < 4; j++) {
      lineSet[i][j] = rand() % H_SIZE;
    }
  }

  setColor(1, 0, 0);
  timeL1 = testLines(line1, plot, lineSet);
  timeL1Clean = testLines(line1, plotClean, lineSet);

  setColor(0, 0, 1);
  timeL2 = testLines(line2, plot, lineSet);
  timeL2Clean = testLines(line2, plotClean, lineSet);

  setColor(1, 1, 0);
  timeL3 = testLines(line3, plot, lineSet);
  timeL3Clean = testLines(line3, plotClean, lineSet);

  setColor(0, 1, 0);
  timeL4 = testLines(line4, plot, lineSet);
  timeL4Clean = testLines(line4, plotClean, lineSet);

  setColor(1, 1, 1);
  timeL5 = testLines(line5, plot, lineSet);
  timeL5Clean = testLines(line6, plotClean, lineSet);


  printf("\n");
  printf(" ================================================================ \n ");
  printf("| Ecuación de la recta \t\t |\t %.4f ms \t|\n", timeL1);
  printf(" ---------------------------------------------------------------- \n ");
  printf("| Incremental 1 \t\t\t |\t %.4f ms \t|\n", timeL2);
  printf(" ---------------------------------------------------------------- \n ");
  printf("| Incremental 2 \t\t\t |\t %.4f ms \t|\n", timeL3);
  printf(" ---------------------------------------------------------------- \n ");
  printf("| Bresenham \t\t\t\t |\t %.4f ms \t|\n", timeL4);
  printf(" ---------------------------------------------------------------- \n ");
  printf("| Bresenham ensamblador\t\t |\t %.4f ms \t|\n", timeL5);
  printf(" ---------------------------------------------------------------- \n ");
  printf("| Ecuación de la recta sin dibujar\t |\t %.4f ms \t|\n", timeL1Clean);
  printf(" ---------------------------------------------------------------- \n ");
  printf("| Incremental 1 sin dibujar\t\t |\t %.4f ms \t|\n", timeL2Clean);
  printf(" ---------------------------------------------------------------- \n ");
  printf("| Incremental 2 sin dibujar\t\t |\t %.4f ms \t|\n", timeL3Clean);
  printf(" ---------------------------------------------------------------- \n ");
  printf("| Bresenham sin dibujar\t\t |\t %.4f ms \t|\n", timeL4Clean);
  printf(" ---------------------------------------------------------------- \n ");
  printf("| Bresenham ensamblador sin dibujar \t|\t %.4f ms \t|\n", timeL5Clean);
  printf(" ================================================================ \n ");
}
