# Makefile for sample sender/receiver UDP multicast programs

CC=gcc
CGLAGS = -g -Wall

all: multicast 

multicast: sender.c listener.c 
	$(CC) $(CFLAGS) -o sender sender.c
	$(CC) $(CFLAGS) -o listener listener.c

clean:
	rm sender
	rm listener
