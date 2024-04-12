cd C:\Users\asanov\Desktop\GITHUB\moving_rocks
rm MAIN.exe
c:\cygwin64\bin\gcc.exe -Wall -g .\main.c .\round.c .\mapping.c .\file.c .\maps.c .\menu.c .\menu_map_editor.c .\menu_start.c .\menu_load.c .\list.c -o .\MAIN.exe -lncurses
MAIN.exe