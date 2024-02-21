//
// Created by Yassine EL GHERRABI on 21/02/2024.
//

#include "./../include/application.h"
#include "./../include/input.h"
#include "./../include/ui.h"

int main() {
    initializeApplication();

    while (1) {
        processInput();
        updateApplication();
        renderApplication();
    }

    cleanupApplication();

    return 0;
}
