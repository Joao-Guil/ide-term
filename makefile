cflags = -Wall -Wextra -Werror -pedantic -std=c99 
libs = -lncurses

all:
	gcc ./main.c -o ./bin/ide.out $(cflags) $(libs)
	rm -rf ide.out