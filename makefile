all:
	gcc -o control semaphores.c

run: all
	./control

gdb: all
	gdb control


clean:
	rm *~
	clear

cleanall:
	rm control
	rm *~
	clear
