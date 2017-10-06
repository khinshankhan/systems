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

cleaner:
	rm strtest
	rm *.o
	clear

cleanall:
	rm strtest
	rm *.o
	rm *.~
	clear
