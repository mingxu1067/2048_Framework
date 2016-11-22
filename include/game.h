#ifndef GAME2048_FRAMEWORK_GAME_H_
#define GAME2048_FRAMEWORK_GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked-list.h"

#define CHECKERBOARD_LENGTH 4

class Game {
public:
    Game();
    ~Game();

    static const int kMoveUp = 0;
    static const int kMoveDown = 1;
    static const int kMoveLeft = 2;
    static const int kMoveRight = 3;

    void start();

    void move(int direction);

    void printCheckerboard();

    int** getCopyCheckerboard();

    bool isGameOver();

    static int moveUpWithCheckerboard(int **checkerboard);

    static int moveDownWithCheckerboard(int **checkerboard);

    static int moveLeftWithCheckerboard(int **checkerboard);

    static int moveRightWithCheckerboard(int **checkerboard);

private:
    int** _checkerboard;
    int _sorce;
    LinkedList _empty_list;

    void initCheckerBoard();

    void setupEmptyList();

    void randomGenerate(int generate_amount);

    static void mergeGrid(int **checkerboard, CheckerboardIndex target, CheckerboardIndex operate, int &sorce, CheckerboardIndex &stop_index);

    int moveUp();

    int moveDown();

    int moveLeft();

    int moveRight();
};

#endif