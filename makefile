jDOOM: main.c
	gcc -I /usr/include/SDL -o jDOOM main.c -lSDL -lm

.PHONY: clean
clean:
	rm jDOOM
