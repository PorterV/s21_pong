// Copyright 2022 gerardys
#include <stdio.h>
#include <math.h>
#include <ncurses.h>

int jumpWall(int ydirection);
int jumpRocket(int direction);
int rocketPositionCheck(int yRocket, int yToCheck);
void printScore(int leftScore, int rightScore);
void printPole(int x, int y, int yLeftRocket, int yRightRocket, int leftScore, int rightScore);
int rocketBlock(int yRocket);
int rocketMovement(int yRocket, char uI);
int scoreSum(int leftScore, int rightScore);
void congratsOne();
void congratsTwo();

int main() {
    initscr();
    timeout(65);
    noecho();
    cbreak();
    int x = 40;
    int y = 13;
    int direction = 1;
    int ydirection = 1;
    int yLeftRocket = 13;
    int yRightRocket = 13;
    int leftScore = 0;
    int rightScore = 0;
    char uI1, uI2;
    while (leftScore < 21 && rightScore < 21) {
        clear();
        printPole(x, y, yLeftRocket, yRightRocket, leftScore, rightScore);
        if (x == 1) {
            rightScore++;
            x = 40;
            y = 13;
            direction = -direction;
            yLeftRocket = 13;
            yRightRocket = 13;
        } else if (x == 80) {
            leftScore++;
            x = 40;
            y = 13;
            direction = -direction;
            yLeftRocket = 13;
            yRightRocket = 13;
        } else if (x == 6 && rocketPositionCheck(yLeftRocket, y) < 2) {
            direction = jumpRocket(direction);
            ydirection = rocketPositionCheck(yLeftRocket, y);
        } else if (x == 75 && rocketPositionCheck(yRightRocket, y) < 2) {
            direction = jumpRocket(direction);
            ydirection = rocketPositionCheck(yRightRocket, y);
        } else if (y == 1 || y == 25) {
            ydirection = jumpWall(ydirection);
        }
        y = y + ydirection;
        x = x + direction;

        uI1 = getch();
        if (uI1 == 'k' || uI1 == 'm') {
            yRightRocket = rocketMovement(yRightRocket, uI1);
        } else if (uI1 == 'a' || uI1 == 'z') {
            yLeftRocket = rocketMovement(yLeftRocket, uI1);
        }
        uI2 = getch();
        if (uI2 == 'k' || uI2 == 'm') {
            yRightRocket = rocketMovement(yRightRocket, uI2);
        } else if (uI2 == 'a' || uI2 == 'z') {
            yLeftRocket = rocketMovement(yLeftRocket, uI2);
        }
    }
    endwin();
    if (leftScore == 21) {
        congratsOne();
    } else {
        congratsTwo();
    }
    return 0;
}

int jumpWall(int ydirection) {
    return -ydirection;
}

int jumpRocket(int direction) {
    return -direction;
}

int rocketPositionCheck(int yRocket, int yToCheck) {
    if (yRocket == yToCheck) {
        return 0;
    } else if (yRocket == yToCheck - 1) {
        return -1;
    } else if (yRocket == yToCheck + 1) {
        return 1;
    } else {
        return 2;
    }
}

void printScore(int leftScore, int rightScore) {
    for (int j = 0; j <= 70; j++) {
                if (j == 0) {
                    printw("Player 1");
                } else if (j == 25) {
                    for (int i = 0; i < scoreSum(leftScore, rightScore); i++) {
                        printw("\b");
                    }
                } else if (j == 37) {
                    printw("%d", leftScore);
                } else if (j == 38) {
                    printw(":");
                } else if (j == 39) {
                    printw("%d", rightScore);
                } else if (j == 70) {
                    printw("Player 2\n");
                } else {
                    printw(" ");
                }
            }
}

void printPole(int x, int y, int yLeftRocket, int yRightRocket, int leftScore, int rightScore) {
    for (int i = 0; i <= 26; i++) {
        for (int j = 0; j <= 81; j++) {
            if (i == y && j == x) {
                printw("*");
            } else if (i == 26 && j == 81) {
                printw("*\n");
            } else if (i == 26) {
                printw("*");
            } else if (j == 0) {
                printw("*");
            } else if (j == 81) {
                printw("*\n");
            } else if (i == 0) {
                printw("*");
            } else if (j == 40) {
                printw("|");
            } else if (j == 5 && rocketPositionCheck(yLeftRocket, i) != 2) {
                printw("|");
            } else if (j == 76 && rocketPositionCheck(yRightRocket, i) != 2) {
                printw("|");
            } else {
               printw(" ");
            }
        }
    }
    printScore(leftScore, rightScore);
}

int rocketBlock(int yRocket) {
    int res;
    switch (yRocket) {
        case 25:
            res = 24;
            break;
        case 1:
            res = 2;
            break;
        default:
            res = yRocket;
            break;
    }
    return res;
}

int rocketMovement(int yRocket, char uI) {
    if (uI == 'k' || uI == 'a') {
        return rocketBlock(yRocket - 1);
    } else if (uI == 'z' || uI == 'm') {
        return rocketBlock(yRocket + 1);
    } else {
        return yRocket;
    }
}

int scoreSum(int leftScore, int rightScore) {
    if (leftScore / 10 >= 1 && rightScore / 10 >= 1) {
        return 4;
    } else if (leftScore / 10 >= 1 || rightScore / 10 >= 1) {
        return 3;
    } else {
        return 2;
    }
}

void congratsOne() {
    printf("                                              #\n");
    printf("#####  #        ##   #   # ###### #####      ##      #    #  ####  #    #         \n");
    printf("#    # #       #  #   # #  #      #    #    # #      #    # #    # ##   #         \n");
    printf("#    # #      #    #   #   #####  #    #      #      #    # #    # # #  #         \n");
    printf("#####  #      ######   #   #      #####       #      # ## # #    # #  # #         \n");
    printf("#      #      #    #   #   #      #   #       #      ##  ## #    # #   ##         \n");
    printf("#      ###### #    #   #   ###### #    #    #####    #    #  ####  #    #         \n");
    printf("                                             #####                                \n");
    printf("#####  #        ##   #   # ###### #####     #     #    #       ####   ####  ##### \n");
    printf("#    # #       #  #   # #  #      #    #          #    #      #    # #        #   \n");
    printf("#    # #      #    #   #   #####  #    #     #####     #      #    #  ####    #   \n");
    printf("#####  #      ######   #   #      #####     #          #      #    #      #   #   \n");
    printf("#      #      #    #   #   #      #   #     #          #      #    # #    #   #   \n");
    printf("#      ###### #    #   #   ###### #    #    #######    ######  ####   ####    #   \n");
}

void congratsTwo() {
    printf("                                              #####                                \n");
    printf(" #####  #        ##   #   # ###### #####     #     #    #    #  ####  #    #       \n");
    printf(" #    # #       #  #   # #  #      #    #          #    #    # #    # ##   #       \n");
    printf(" #    # #      #    #   #   #####  #    #     #####     #    # #    # # #  #       \n");
    printf(" #####  #      ######   #   #      #####     #          # ## # #    # #  # #       \n");
    printf(" #      #      #    #   #   #      #   #     #          ##  ## #    # #   ##       \n");
    printf(" #      ###### #    #   #   ###### #    #    #######    #    #  ####  #    #       \n");
    printf("                                               #                                   \n");
    printf(" #####  #        ##   #   # ###### #####      ##      #       ####   ####  #####   \n");
    printf(" #    # #       #  #   # #  #      #    #    # #      #      #    # #        #     \n");
    printf(" #    # #      #    #   #   #####  #    #      #      #      #    #  ####    #     \n");
    printf(" #####  #      ######   #   #      #####       #      #      #    #      #   #     \n");
    printf(" #      #      #    #   #   #      #   #       #      #      #    # #    #   #     \n");
    printf(" #      ###### #    #   #   ###### #    #    #####    ######  ####   ####    #     \n");
}
