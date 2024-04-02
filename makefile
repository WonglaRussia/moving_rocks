MAIN: rolling-the-rocks.c file.o mapping.o maps.o menu.o menu_map_editor.o menu_start.o round.o
	gcc -g -Wall rolling-the-rocks.c file.o mapping.o maps.o menu.o menu_map_editor.o menu_start.o round.o -o MAIN -lncurses
file.o: file.c file.h
	gcc -c  file.c -o file.o
mapping.o: mapping.c mapping.h
	gcc -c  mapping.c -o mapping.o -lncurses
maps.o: maps.c maps.h
	gcc -c  maps.c -o maps.o
menu.o: menu.c menu.h
	gcc -c  menu.c -o menu.o -lncurses
menu_map_editor.o: menu_map_editor.c menu_map_editor.h
	gcc -c  menu_map_editor.c -o menu_map_editor.o
menu_start.o: menu_start.c menu_start.h
	gcc -c  menu_start.c -o menu_start.o
round.o: round.c round.h
	gcc -c  round.c -o round.o -lncurses
