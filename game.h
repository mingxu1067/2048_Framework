#ifndef GAME2048_FRAMEWORK_GAME_H_
#define GAME2048_FRAMEWORK_GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked-list.h"

class Game {
public:
    Game();
    ~Game();

    static const int MOVE_UP = 0;
    static const int MOVE_DOWN = 1;
    static const int MOVE_LEFT = 2;
    static const int MOVE_RIGHT = 3;

    static const int CHECKERBOARD_LENGTH = 4;

    void start();

    void move(int direction);

    int moveUp();

    int moveDown();

    int moveLeft();

    int moveRight();

    void printCheckerboard();

    int** getCheckerboard();

private:
    int _checkerboard[CHECKERBOARD_LENGTH][CHECKERBOARD_LENGTH];
    int _sorce;
    LinkedList _empty_list;

    void initCheckerBoard();

    void setupEmptyList();

    void randomGenerate(int generate_amount);

    void mergeGrid(CheckerboardIndex target, CheckerboardIndex operate, int &sorce, CheckerboardIndex &stop_index);

    bool isGameOver();
};

#endif