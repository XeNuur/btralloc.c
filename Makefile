OUT=test.out
CC=gcc
RM=rm

all:
	$(CC) -g main.c btralloc.c -o $(OUT)

clear:
	$(RM) $(OUT)

run: all
	./$(OUT)
