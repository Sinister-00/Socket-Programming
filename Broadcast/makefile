# Makefile for sample sender/receiver UDP multicast programs

CC=gcc
CGLAGS = -g -Wall

all: multicast 

multicast: sender.c listener1.c listener2.c
	$(CC) $(CFLAGS) -o sender sender.c
	$(CC) $(CFLAGS) -o listener1 listener1.c
	$(CC) $(CFLAGS) -o listener2 listener2.c

clean:
	rm sender
	rm listener1
	rm listener2
