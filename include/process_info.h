//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H

#include <sys/types.h>

typedef struct ProcessInfo {
    pid_t pid; // Process ID
    char user[256]; // User who launched the process
    int priority; // Process priority
    int niceValue; // Nice value of the process
    long virtualMemory; // Virtual memory used by the process
    long residentMemory; // Resident memory used by the process
    long sharedMemory; // Shared memory of the process
    char state; // State of the process
    float cpuUsagePercentage; // CPU usage as a percentage
    float memoryUsagePercentage; // Memory usage as a percentage
    long totalTime; // Total execution time of the process
    char command[1054]; // Command that launched the process
    struct ProcessInfo* next; // Pointer to the next process in the list
} ProcessInfo;

#endif //PROCESS_INFO_H