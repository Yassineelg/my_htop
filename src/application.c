//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#include "./../include/application.h"
#include "./../include/ui.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <pwd.h>

ProcessInfo *head = NULL; // The head of the process list
extern int processCount; // The number of processes

/**
 * Initialize the application
 */
void initializeApplication() {
    initscr(); // Initialize the ncurses screen
    cbreak(); // Disable line buffering
    noecho(); // Don't echo any keypresses
    keypad(stdscr, TRUE); // Enable the keypad
    curs_set(0); // Hide the cursor
    start_color(); // Enable color
    init_pair(HEADER_COLOR, COLOR_BLACK, COLOR_GREEN); // Header color
    init_pair(SELECTED_COLOR, COLOR_BLACK, COLOR_BLUE); // Selected process color
    init_pair(DEFAULT_COLOR, COLOR_WHITE, COLOR_BLACK); // Default color
    init_pair(INSTRUCTION_COLOR, COLOR_YELLOW, COLOR_BLACK); // Instruction color
    bkgd(COLOR_PAIR(DEFAULT_COLOR)); // Set the default color
    timeout(1000); // Set the timeout for getch() to 1000ms
}


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
 */
void addProcess(ProcessInfo process) {
    ProcessInfo* newProcess = (ProcessInfo*)malloc(sizeof(ProcessInfo));
    *newProcess = process; // Copier les données
    newProcess->next = head;
    head = newProcess;
    processCount++;
}

/**
 * Get the name of a user from their UID
 * @param uid The user ID
 */
char* getUidName(uid_t uid) {
    struct passwd *pw = getpwuid(uid);
    return pw ? strdup(pw->pw_name) : strdup("unknown");
}

/**
 * Read the /proc/stat file to get the total CPU time
 * @param path The path to the /proc/stat file
 */
void readProcessStat(ProcessInfo* process, const char* path) {
    FILE* fp = fopen(path, "r");
    if (fp) {
        long int dummy;
        fscanf(fp, "%ld %s %c %ld %ld %ld %ld %ld %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %lu %lu %ld",
            &dummy,
            process->command,
            &process->state,
            &dummy, &dummy, &dummy, &dummy,
            &dummy,
            &dummy, &dummy, &dummy,
            &dummy,
            &dummy,
            &dummy,
            &dummy, &dummy,
            &dummy,
            &dummy,
            &dummy,
            &dummy,
            &process->virtualMemory,
            &dummy
        );
        fclose(fp);
    }
}

/**
 * Read the /proc/[pid]/status file to get the process status
 * @param path The path to the /proc/[pid]/status file
 */
void readProcessStatus(ProcessInfo* process, const char* path) {
    FILE* fp = fopen(path, "r");
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "Uid:", 4) == 0) {
                uid_t uid;
                sscanf(line, "Uid: %d", &uid);
                strcpy(process->user, getUidName(uid));
            } else if (strncmp(line, "VmRSS:", 6) == 0) {
                sscanf(line, "VmRSS: %ld", &process->residentMemory);
            } else if (strncmp(line, "VmSize:", 7) == 0) {
                sscanf(line, "VmSize: %ld", &process->virtualMemory);
            } else if (strncmp(line, "VmLck:", 6) == 0) {
                sscanf(line, "VmLck: %ld", &process->sharedMemory);
            } else if (strncmp(line, "Priority:", 9) == 0) {
                sscanf(line, "Priority: %d", &process->priority);
            } else if (strncmp(line, "Nice:", 5) == 0) {
                sscanf(line, "Nice: %d", &process->niceValue);
            }
        }
        fclose(fp);
    }
}

/**
 * Render the application
 */
void updateApplication() {
    freeProcessList();
    DIR *dir;
    struct dirent *ent;
    char path[256];

    if ((dir = opendir("/proc")) == NULL) {
        perror("Failed to open /proc directory");
        return;
    }

    processCount = 0;
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_DIR && atoi(ent->d_name) > 0) {
            ProcessInfo process;
            memset(&process, 0, sizeof(ProcessInfo));

            process.pid = atoi(ent->d_name);

            snprintf(path, sizeof(path), "/proc/%d/stat", process.pid);
            readProcessStat(&process, path);

            snprintf(path, sizeof(path), "/proc/%d/status", process.pid);
            readProcessStatus(&process, path);

            addProcess(process);
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
