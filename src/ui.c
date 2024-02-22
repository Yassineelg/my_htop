//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#include "./../include/ui.h"
#include "./../include/application.h"
#include <ncurses.h>

extern ProcessInfo *head;

/**
 * Initialize the application
 */
void printInstructions() {
    mvprintw(INSTRUCTION_ROW, 0, "Press '");
    attron(COLOR_PAIR(INSTRUCTION_COLOR));
    printw("q");
    attroff(COLOR_PAIR(INSTRUCTION_COLOR));
    printw("' to quit and '");
    attron(COLOR_PAIR(INSTRUCTION_COLOR));
    printw("space");
    attroff(COLOR_PAIR(INSTRUCTION_COLOR));
    printw("' to refresh.");
}

/**
 * Print the headers for the process list
 */
void printHeaders() {
    attron(COLOR_PAIR(HEADER_COLOR));
    mvprintw(HEADER_ROW, PID_COLUMN, "PID");
    mvprintw(HEADER_ROW, NAME_COLUMN, "Nom du Processus");
    attroff(COLOR_PAIR(HEADER_COLOR));
}

/**
 * Render the application
 */
void renderApplication() {
    int row = START_ROW;
    clear();

    printInstructions();
    printHeaders();

    // Display process info
    ProcessInfo* current = head;
    while (current != NULL) {
        attron(COLOR_PAIR(PROCESS_INFO_COLOR));
        mvprintw(row, PID_COLUMN, "%d", current->pid);
        mvprintw(row, NAME_COLUMN, "%s", current->name);
        attroff(COLOR_PAIR(PROCESS_INFO_COLOR));
        row++;
        current = current->next;
    }

    // Refresh the screen
    refresh();
}