CC=gcc
CFLAGS=-o
EXEC=iesire
OBJ=sah.o

build: $(OBJ)
	$(CC) $(CFLAGS) $(EXEC) sah.c
run:
	./$(EXEC)
clean:
	rm -f $(OBJ) $(EXEC)

