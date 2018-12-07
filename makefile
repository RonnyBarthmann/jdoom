jDOOM: main.c
	gcc -I /usr/include/SDL -o jDOOM main.c -lSDL

.PHONY: clean
clean:
	rm jDOOM
