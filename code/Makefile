EXEC = solver
SRC  = $(wildcard *.c)
OBJ  = $(SRC:.c=.o)

CC	   = gcc
CFLAGS = -Wall -Wextra -std=c99 -O -g

all: $(EXEC) clean

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJ)

mrproper: clean
	rm -f $(EXEC)
