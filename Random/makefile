all:
	gcc -o exec random.c

run: all
	./exec

valgrind:
	gcc -g random.c
	valgrind --leak-check=yes ./a.out

clean:
	rm exec
	clear
	rm *~
	clear

cleanall:
	rm exec
	rm a.out
	rm *~
	clear
