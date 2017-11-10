all:
	gcc -o exec *.c

run: all
	./exec

valgrind:
	gcc -g *.c
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
