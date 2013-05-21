CC = gcc
all:
	$(CC) -c boy.c `pkg-config --libs --cflags glib-2.0 gobject-2.0`
	$(CC) -c man.c  `pkg-config --libs --cflags glib-2.0 gobject-2.0`
	$(CC) -c main.c  `pkg-config --libs --cflags glib-2.0 gobject-2.0`
	$(CC) -o simple boy.o man.o main.o `pkg-config --libs --cflags glib-2.0 gobject-2.0`



