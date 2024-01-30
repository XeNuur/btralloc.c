OUT=btralloc

all:
	gcc -g main.c btralloc.c -o $(OUT)

clear:
	rm $(OUT)

run: all
	./$(OUT)
