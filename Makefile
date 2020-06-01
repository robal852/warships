CC=gcc
CFLAGS=-ansi -O
all: main_program_zaliczeniowy.o statki.o
	$(CC) $(CFLAGS) -o statki_gra main_program_zaliczeniowy.o statki.o
