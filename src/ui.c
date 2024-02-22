//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#include "./../include/ui.h"
#include "./../include/application.h"
#include <ncurses.h>
#include <stdlib.h>

extern ProcessInfo *head; // The head of the process list
ProcessInfo *selectedProcess = NULL; // The selected process
int selectedIndex = 0; // The index of the selected process
int processCount = 0; // The number of processes
int scrollOffset = 0; // The scroll offset

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
    mvhline(HEADER_ROW, 0, ' ', getmaxx(stdscr));
    mvprintw(HEADER_ROW, HEADER_COL, "%-10s%-15s%-5s%-5s%-10s%-10s%-10s%-5s%-10s%-10s%-10s%-s",
             "PID", "USER", "PRI", "NI", "VIRT", "RES", "SHR", "S", "%%CPU", "%%MEM", "TIME+", "Command");
    attroff(COLOR_PAIR(HEADER_COLOR));
}

/**
 * Print the process information
 * @param y The row to print the information
 * @param isSelected If the process is selected
 */
void printProcessInfo(ProcessInfo* process, int y, bool isSelected) {
    if (isSelected) {
        attron(COLOR_PAIR(SELECTED_COLOR));
    } else {
        attron(COLOR_PAIR(DEFAULT_COLOR));
    }
    mvhline(y, 0, ' ', getmaxx(stdscr));
    mvprintw(y, 0, "%-10d%-15s%-5d%-5d%-10ld%-10ld%-10ld%-5c%-10.2f%-10.2f%-10ld%-s",
                process->pid,
                process->user,
                process->priority,
                process->niceValue,
                process->virtualMemory,
                process->residentMemory,
                process->sharedMemory,
                process->state,
                process->cpuUsagePercentage,
                process->memoryUsagePercentage,
                process->totalTime,
                process->command);
    attroff(COLOR_PAIR(isSelected ? SELECTED_COLOR : DEFAULT_COLOR));
}

/**
 * Render the process list
 */
void renderProcessList() {
    int y = START_ROW;
    int index = 0;
    ProcessInfo* current = head;
    for (int i = 0; i < scrollOffset && current != NULL; i++) {
        current = current->next;
    }
    for (; current != NULL; current = current->next, index++) {
        if (index == selectedIndex) {
            selectedProcess = current;
        }
        printProcessInfo(current, y++, current == selectedProcess);
    }
}

/**
 * Render the application
 */
void renderApplication() {
    printInstructions();
    printHeaders();
    renderProcessList();
    refresh();
}
