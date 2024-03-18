C:\Users\asanov\Desktop\GITHUB\moving_rocks
rm MAIN.exe
c:\cygwin64\bin\gcc.exe -Wall -g .\rocks.c .\mapping.c .\maps.c -o .\MAIN.exe -lncurses
MAIN.exe
timeout 100