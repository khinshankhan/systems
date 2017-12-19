forking: client fserver

basic: client bserver

fserver: forking_server.o pipe_networking.o
	gcc -o server forking_server.o pipe_networking.o

client: client.o pipe_networking.o
	gcc -o client client.o pipe_networking.o

bserver: basic_server.o pipe_networking.o
	gcc -o server basic_server.o pipe_networking.o

client.o: client.c pipe_networking.h
	gcc -c client.c

basic_server.o: basic_server.c pipe_networking.h
	gcc -c basic_server.c

forking_server.o: forking_server.c pipe_networking.h
	gcc -c forking_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

clean:
	rm *.o
	rm *~
