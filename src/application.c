//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#include "./../include/application.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>

ProcessInfo *head = NULL;

/**
 * Free the process list
 */
void freeProcessList() {
    ProcessInfo* current = head;
    while (current != NULL) {
        ProcessInfo* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

/**
 * Add a process to the list
 * @param pid The process ID
 * @param name The name of the process
 */
void addProcess(int pid, const char* name) {
    // Create a new process
    ProcessInfo* newProcess = (ProcessInfo*)malloc(sizeof(ProcessInfo));
    newProcess->pid = pid;
    strncpy(newProcess->name, name, 255);
    newProcess->name[255] = '\0';
    newProcess->next = head;
    head = newProcess;
}

/**
 * Initialize the application
 */
void initializeApplication() {
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_CYAN, COLOR_BLACK); // For headers
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // For process info
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // For instructions
}

/**
 * Get the name of a process from its status file
 * @param path The path to the status file
 * @return The name of the process
 */
char* getProcessName(char* path) {
    char line[MAX_PATH_LENGTH], name[MAX_NAME_LENGTH];
    FILE* fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return NULL;
    }
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "Name: %255s", name) == 1) {
            fclose(fp);
            return strdup(name);
        }
    }
    fclose(fp);
    return NULL;
}

/**
 * Update the application
 */
void updateApplication() {
    freeProcessList();
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("/proc")) == NULL) {
        perror("Error opening directory");
        return;
    }
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_DIR && atoi(ent->d_name) > 0) {
            char path[MAX_PATH_LENGTH];
            snprintf(path, sizeof(path), "/proc/%.240s/status", ent->d_name);
            char* name = getProcessName(path);
            if (name != NULL) {
                addProcess(atoi(ent->d_name), name);
                free(name);
            }
        }
    }
    closedir(dir);
}

/**
 * Clean up the application
 */
void cleanupApplication() {
    freeProcessList();
    endwin();
}
