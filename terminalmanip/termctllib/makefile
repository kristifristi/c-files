all: use clean

use: uselib.o style.o
	gcc style.o uselib.o -o use

uselib.o: uselib.c
	gcc -c uselib.c -o uselib.o

style.o: style.c
	gcc -c style.c -o style.o

clean:
	rm style.o uselib.o
