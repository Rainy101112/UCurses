/* 
 * 
 * 		ucurses.c
 * 		A curses TUI library for Uinxed-Kernel.
 * 
 * 		Auth: Rainy101112
 * 		Date: 2024/10/19
 * 
 */

#include "ucurses.h"

// int main(){
// 	initscr();
// 	WINDOW* win = newwin(10, 20, 10, 10);
// 	WINDOW *win2 = newwin(5, 10, 5, 5);

// 	//move(10, 10);

// 	getchar();

// 	win->height = 20;

// 	delwin(win);
// 	refresh();

// 	getchar();

// 	delwin(win2);
// 	endwin();
// 	return 0;
// }

int initscr(){															// Initialize the ucurses screen
	current_screen = (struct screen *)malloc(sizeof(struct screen));	// Alloc a part of memory for the screen
	current_screen->initialized = 1;									// Set the screen status to initialized
	current_screen->current_sheet_count = 0;							// Initialize sheet
	current_screen->window_list = NULL;									// Initialize the window list
	clear_screen();														// Clean screen
	return 0;
}

static int ucurses_abs(int n) {
	if (n < 0) {
		return ~(n) + 1;
	}
	return n;
}

void move(int row, int col){											// Move cursor to row(Y) col(X);
	printf("\033[%d;%dH", row, col + 1);								// VT-100 move cursor: \033[<X>;<Y>H or \033[<X>;<Y>f
	return;
}

WINDOW* newwin(int height, int width, int start_x, int start_y){		// Create a new window
	struct WINDOW *window = malloc(sizeof(WINDOW));						// Alloc a part of memory for the new window

	if (current_screen == NULL) {										// Check if the screen never initialize
		printf("[\033[35mUCURESES\033[0m - \033[31mERROR\033[0m] The screen is uninitialized.\n");
		return NULL;
	}

	/* Translate */
	if (height == 0) {
		return 0;
	} else 
	if (height - 3 == 0){
		return 0;
	} else
	if (height - 3 < 0) {
		height = ucurses_abs(height);
	}

	if (width == 0) {
		return 0;
	}
	if (width - 3 == 0) {
		return 0;
	} else 
	if (width - 3 < 0) {
		width = ucurses_abs(width);
	}

	/* Initialize options */
	window->status = 1;
	window->height = height;
	window->width = width;
	window->start_x = start_x;
	window->start_y = start_y;

	current_screen->current_sheet_count++;								// Sheet count plus 1, because created a new window

	/* Draw window */

	move(start_y, start_x);												// Move to the start of the window

	printf("╔");
	for (int w = 0; w <= width - 3; w++) {								// Draw head line. width - 3: width - first - end - end of array
		printf("═");
	}
	printf("╗\n");

	for (int h = 1; h <= height - 1; h++) {								// Draw body
		move(start_y + h, start_x);
		printf("║\n");
		move(start_y + h, start_x + width - 1);
		printf("║\n");
	}

	move(start_y + height - 1, start_x);
	printf("╚");
	for (int w = 0; w <= width - 3; w++) {								// Draw foot line
		printf("═");
	}
	printf("╝");

	/* Add the new window to the window list */
	window->next = current_screen->window_list;
	current_screen->window_list = window;

	return window;
}

static void wrewrite(WINDOW *window){									// Refresh
	int status = window->status;
	int height = window->height;
	int width = window->width;
	int start_x = window->start_x;
	int start_y = window->start_y;
	// int sheet = window->sheet;

	if (status != 1) {
		return;
	}

	clear_screen();

	move(start_y, start_x);												// Move to the start of the window

	printf("╔");
	for (int w = 0; w <= width - 3; w++) {								// Draw head line. width - 3: width - first - end - end of array
		printf("═");
	}
	printf("╗\n");

	for (int h = 1; h <= height - 1; h++) {								// Draw body
		move(start_y + h, start_x);
		printf("║\n");
		move(start_y + h, start_x + width - 1);
		printf("║\n");
	}

	move(start_y + height - 1, start_x);
	printf("╚");
	for (int w = 0; w <= width - 3; w++) {								// Draw foot line
		printf("═");
	}
	printf("╝");

	return;
}

void wrefresh(WINDOW *window){											// Refresh a window
	wrewrite(window);
	return;
}

void refresh(void) {													// Refresh all the windows
	WINDOW *current_window = current_screen->window_list;
	while (current_window != NULL) {
		wrefresh(current_window);
		current_window = current_window->next;
	}
}

void delwin(WINDOW *window) {											// Free a window
	if (window == NULL || current_screen == NULL || current_screen->window_list == NULL) {
		return; 														// If uninitialized, return
	}

	WINDOW *current = current_screen->window_list;
	WINDOW *previous = NULL;

	/* Special: Delete first window */
	if (current == window) {
		current_screen->window_list = current->next;					// Update head pointer
		free(current);
		return;
	}

	/* Find the window before the window which will delete */
	while (current != NULL && current != window) {
		previous = current;
		current = current->next;
	}

	/* If empty */
	if (current == NULL) {
		return;															// Not found, return
	}

	/* Remove window */
	if (previous != NULL) {
		previous->next = current->next;
	}

	free(current);
	current_screen->current_sheet_count--; 								// Update sheet count
}

void endwin(void){														// Close all the window and dealloc memories
	free(current_screen);												// Dealloc
	current_screen = NULL;
}