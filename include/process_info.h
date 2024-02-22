//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H

typedef struct ProcessInfo {
    int pid; // Process ID
    char name[256]; // Process name
    struct ProcessInfo* next; // Pointer to the next process in the list
} ProcessInfo;

#endif //PROCESS_INFO_H
