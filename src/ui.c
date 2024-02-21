//
// Created by Yassine EL GHERRABI on 21/02/2024.
//
#include "./../include/ui.h"
#include <ncurses.h>

void renderApplication() {
    erase();
    mvprintw(0, 0, "Appuyez sur 'q' pour quitter.");
    refresh();
}
