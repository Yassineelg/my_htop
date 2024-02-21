//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#include "./../include/application.h"
#include <ncurses.h>

void initializeApplication() {
    // Initialize the Ncurses library
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void cleanupApplication() {
    // Clean up and exit Ncurses properly
    endwin();
}

void updateApplication() {
    // Update the state of the application, such as refreshing the list of processes
}
