//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#include "./../include/input.h"
#include "./../include/application.h"
#include <ncurses.h>

extern void renderApplication();
extern int running;

/**
 * Process the input from the user
 */
void processInput() {
    int ch = getch();
    switch(ch) {
    case ' ': // Space key to refresh the process list
        updateApplication();
        renderApplication();
        break;
    case 'q': // Q key to quit the application
        running = 0;
        break;
    }
}
