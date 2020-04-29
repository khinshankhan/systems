all: node.o
	gcc -o node node.o

node.o: node.c
	gcc -c node.c

clean:
	rm *.o
	rm *~

cleanall:
	rm *.o
	rm *~
	rm node

run: all
	./node
