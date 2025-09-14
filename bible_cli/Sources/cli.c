#include "cli.h"

void cliInit() {
    if (DEBUG_MODE)
        sleep(1);
    system("clear");
}

void cliLoop(int *isRunning) {
    if (isRunning == NULL || *(isRunning) == 0) return;
    struct termios old_t, new_t;
    char character;

    tcgetattr(STDIN_FILENO, &old_t);
    new_t = old_t;
    new_t.c_lflag &= ~(ICANON | ECHO);
    new_t.c_cc[VMIN] = 0;
    new_t.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_t);

    puts("Press 'q' to quit the loop.");
    while (*(isRunning)) {
        if (read(STDIN_FILENO, &character, 1) > 0) {
            if (character == 'q') {
                cliExit(isRunning, &old_t);
            }
        }
    }
}

void cliExit(int *isRunning, struct termios *old_t) {
    *(isRunning) = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, old_t);
}
