all: stringy.o main.o
	gcc -o strtest stringy.o main.o

stringy.o: stringy.c stringy.h
	gcc -c stringy.c

main.o: main.c stringy.h
	gcc -c main.c

run: all
	./strtest

clean:
	rm *.o
	rm *~
