.PHONY : clean all

CC=gcc
CFLAGS=-O2 -march=native -fomit-frame-pointer -Wall

all: UARTaudio

UARTaudio: src/UARTaudio.c
	$(CC) $(CFLAGS) src/UARTaudio.c -o UARTaudio

clean:
	rm -rf UARTaudio
