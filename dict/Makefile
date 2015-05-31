server client:server.o server_init.o client_init.o client.o public.o
	gcc server.o server_init.o public.o -o server -Wall -lsqlite3
	gcc client_init.o client.o public.o -o client -Wall -lsqlite3
	rm *.o

server.o:
server_init.o:
client.o:
client_init.o:
public.o:

clean:
	rm *.o
cleanall:
	rm server
	rm client
