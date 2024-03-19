/* rolling-the-rocks.c */
#include <ncurses.h>
#include "maps.h"						//current_map
#include "rocks.h"						//play_the_map()

char work_bw;							//b&w terminal?

int main() {
	score = 40;

	initscr();
	work_bw = !has_colors();						//REWRITE all screen functions
	keypad(stdscr, 1); 								//esc seq for moving by arrows
	curs_set(0);

	play_the_map(current_map);
	endwin();
return 0;
}
