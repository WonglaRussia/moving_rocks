/* menu.h */
#ifndef MENU_H
#define MENU_H

struct menu_option {
	char *option_name;
	struct menu_option *next;
};

int menu(int qt, ...);

#endif