TARGET1 = main
TARGET2 = pending
TARGET3 = floyd
TARGET4 = knapsack
TARGET5 = sportsSeries
TARGET6 = reemplazoDeEquipos
TARGET7 = BST
TARGETS = $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7)

# compiler
CC = gcc
# debug
DEBUG = -g
# optimisation
OPT = -O0
# warnings
WARN = -Wall
PTHREAD = -pthread
FLAGS = $(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe
GTKLIB = `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

OBJS = main.o

all:  $(TARGETS)

main: src/main.c
	$(CC) -o $(TARGET1) $(FLAGS) src/main.c $(GTKLIB)

pending: src/pending.c
	$(CC) -o $(TARGET2) $(FLAGS) src/pending.c $(GTKLIB)

floyd: src/floyd.c
	$(CC) -o $(TARGET3) $(FLAGS) src/floyd.c $(GTKLIB)

knapsack: src/knapsack.c
	$(CC) -o $(TARGET4) $(FLAGS) src/knapsack.c $(GTKLIB)

sportsSeries: src/sportsSeries.c
	$(CC) -o $(TARGET5) $(FLAGS) src/sportsSeries.c $(GTKLIB)

reemplazoDeEquipos: src/reemplazoDeEquipos.c
	$(CC) -o $(TARGET6) $(FLAGS) src/reemplazoDeEquipos.c $(GTKLIB)

BST: src/BST.c
	$(CC) -o $(TARGET7) $(FLAGS) src/BST.c $(GTKLIB)

clean:
	rm -f *.o $(TARGETS)
