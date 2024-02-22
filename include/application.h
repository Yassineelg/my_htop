//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include "process_info.h"

#define MAX_PATH_LENGTH 256
#define MAX_NAME_LENGTH 255
#define MAX_DIR_NAME_LENGTH 240

void initializeApplication();
void cleanupApplication();
void updateApplication();
void freeProcessList();

#endif //APPLICATION_H
