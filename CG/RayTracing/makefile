NAME = main
OBJECTS = src/*.c
OUTPUT = $(NAME)

CFLAGS =
LDFLAGS = -g
LDLIBS = -lm

$(OUTPUT): $(OBJECTS)
	cc $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(OUTPUT) $(OBJECTS)

clean:
	rm -f *.o
	rm -f $(NAME)
