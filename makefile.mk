cipher.exe: cipher.o cipher_server.o
	gcc cipher.o cipher_server.o -o cipher.exe

cipher_server.o: cipher_server.c cipher.h
	gcc -Wall -c cipher_server.c

cipher.o: cipher.c cipher.h
	gcc -Wall -c cipher.c

clean:
	rm -f cipher.o cipher_server.o