//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#include "./../include/input.h"
#include "./../include/application.h"
#include "./../include/ui.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

extern int running; // Control the main loop
extern int selectedIndex; // The index of the selected process
extern int processCount; // The number of processes
extern int scrollOffset; // The scroll offset

/**
 * Process the input from the user
 */
void processInput() {
    int ch = getch();
    if (ch == ERR) {
        return;
    }
    switch(ch) {
    case KEY_UP: // Up arrow key to move the selection up
        if (selectedIndex > 0) {
            selectedIndex--;
            if (selectedIndex < scrollOffset) {
                scrollOffset--;
            }
        }
        break;
    case KEY_DOWN: // Down arrow key to move the selection down
        if (selectedIndex < processCount - 1) {
            selectedIndex++;
            if (selectedIndex >= scrollOffset + getmaxy(stdscr) - START_ROW) {
                scrollOffset++;
            }
        }
        break;
    case ' ': // Space key to refresh the process list
        updateApplication();
        renderApplication();
        break;
    case 'q': // Q key to quit the application
        running = 0;
        break;
    }
}
