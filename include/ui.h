//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#ifndef UI_H
#define UI_H

#include "process_info.h"

#define INSTRUCTION_ROW 0
#define HEADER_ROW 2
#define HEADER_COL 0
#define START_ROW 3
#define HEADER_COLOR 1
#define SELECTED_COLOR 2
#define DEFAULT_COLOR 3
#define INSTRUCTION_COLOR 4

extern ProcessInfo *selectedProcess;
extern int selectedIndex;

void renderApplication();

#endif //UI_H
