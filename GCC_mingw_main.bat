C:\Users\asanov\Desktop\GITHUB\moving_rocks
rm MAIN.exe
c:\cygwin64\bin\gcc.exe -Wall -g .\main.c .\round.c .\mapping.c .\file.c .\maps.c .\menu.c .\menu_map_editor.c .\menu_start.c -o .\MAIN.exe -lncurses
MAIN.exe
timeout 100