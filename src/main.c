//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#include "./../include/application.h"
#include "./../include/input.h"
#include "./../include/ui.h"

int running = 1; // Control the main loop

int main() {
    initializeApplication();

    while (running) {
        processInput();
        updateApplication();
        renderApplication();
    }

    cleanupApplication();
    return 0;
}
