CC1=gcc -O3 -Wall

CFLAGS = -g -c -Wall
#CFLAGS = -ansi -c -Wall -pedantic
all: Receiver Sender

A = Receiver.o
B = Sender.o


Receiver: $A
	$(CC1) -o Receiver $A

Receiver.o: Receiver.c
	$(CC1) -c Receiver.c

Sender: $B
	$(CC1) -o Sender $B

Sender.o: Sender.c
	$(CC1) -c Sender.c


clean:
	rm *.o
	rm Sender
	rm Receiver        

