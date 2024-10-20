/* 
 * 
 * 		ucurses.h
 * 		A curses TUI library for Uinxed-Kernel.
 * 
 * 		Auth: Rainy101112
 * 		Date: 2024/10/19
 * 
 */

/* 
 * 		Note
 * 		For replanting, you should make sure your terminal system supports VT-100.
 */

#ifndef INCLUDE_UCURSES_H_
#define INCLUDE_UCURSES_H_

/* 
 * 		Note
 * 		For replanting, at least the system MUST provide some following things: 
 * 		
 * 		Functions: 
 * 			void* malloc(size_t size);
 * 			void* free(void *memory);
 * 			int printf(const char *format, ...);
 * 			int getchar(void);
 * 		
 * 		Types: 
 * 			bool
 * 			
 * 		Defintions:
 * 			NULL
 * 		
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/* Replant interfaces */

#define clear_screen() system("clear")

/* Structures */

typedef struct WINDOW {
	bool status;		/* status = 0 - hide 
						   status = 1 - show */
	int sheet;			// Current sheet

	int height;
	int width;
	int start_x;
	int start_y;
	struct WINDOW *next;
} WINDOW;

struct screen {
	bool initialized;
	int current_sheet_count;
	WINDOW *window_list;
};

struct screen *current_screen = NULL;

/* Functions */

int initscr();																	// Initialize the ucurses screen
WINDOW* newwin(int height, int width, int start_x, int start_y);				// Create a new window
void subwin(WINDOW *parent, int height, int width, int start_x, int start_y);	// Create a sub-window on a parent window
void delwin(WINDOW *window);													// Free a window
void endwin(void);																// Close all the windows

void move(int row, int col);													// Move cursor to row(Y) col(X);
/* @TODO
void wmove(WINDOW *window, int row, int col);

void printw(const char *format, ...);
void wprintw(WINDOW *parent, const char *format, ...);

int getch(void);
void scanw(const char *format, ...);
void wscanw(WINDOW *parent, const char *format, ...);
*/
void refresh(void);																// Refresh all the windows
void wrefresh(WINDOW *window);													// Refresh a window

#endif // INCLUDE_UCURSES_H_
