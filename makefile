all:
	gcc ./main.c -o ./bin/ide.out -lncurses
	rm -rf ide.out