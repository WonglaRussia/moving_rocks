CC = gcc 
CFLAGS = -c -ggdb -Wall
FFLAGS = -ggdb -Wall
MAIN: main.c file.o mapping.o maps.o menu.o menu_map_editor.o menu_start.o round.o menu_load.o
	$(CC) $(FFLAGS) main.c file.o mapping.o maps.o menu.o menu_map_editor.o menu_start.o menu_load.o round.o -o $@ -lncurses
file.o: file.c file.h
	$(CC) $(CFLAGS)  file.c -o $@
mapping.o: mapping.c mapping.h
	$(CC) $(CFLAGS)  mapping.c -o $@ -lncurses
maps.o: maps.c maps.h
	$(CC) $(CFLAGS)  maps.c -o $@
menu.o: menu.c menu.h
	$(CC) $(CFLAGS)  menu.c -o $@ -lncurses
menu_map_editor.o: menu_map_editor.c menu_map_editor.h
	$(CC) $(CFLAGS)  menu_map_editor.c -o $@
menu_start.o: menu_start.c menu_start.h
	$(CC) $(CFLAGS)  menu_start.c -o $@
round.o: round.c round.h
	$(CC) $(CFLAGS)  round.c -o $@ -lncurses
menu_load.o: menu_load.c menu_load.h
	$(CC) $(CFLAGS)  menu_load.c -o $@ -lncurses

