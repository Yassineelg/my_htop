//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#include "./../include/input.h"
#include <ncurses.h>

extern int running; // Global variable to control the main loop

void processInput() {
    nodelay(stdscr, TRUE); // Set the window to non-blocking mode
    int ch = getch(); // Get the input from the user

    switch(ch) {
        case 'q': // Quit the application
            running = 0;
            break;
    }
}
