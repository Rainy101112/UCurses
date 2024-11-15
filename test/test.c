#include "../include/ucurses.h"

int main(){
	initscr();
	WINDOW* win = newwin(10, 20, 10, 10);
	WINDOW *win2 = newwin(5, 10, 5, 5);

	//move(10, 10);

	getchar();

	win->height = 20;

	delwin(win);
	refresh();

	getchar();

	delwin(win2);
	endwin();
	return 0;
}