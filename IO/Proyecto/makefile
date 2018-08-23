TARGET1 = main
TARGET2 = pending
TARGET3 = floyd
TARGETS = $(TARGET1) $(TARGET2) $(TARGET3)

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

clean:
	rm -f *.o $(TARGETS)
