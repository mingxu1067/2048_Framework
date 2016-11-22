#include <stdio.h>
#include "game.h"

Game::Game() {
    initCheckerBoard();
    _empty_list = LinkedList();
    setupEmptyList();
}

Game::~Game() {}

void Game::start() {
    printf("Up: \'w\', Down: \'w\', Left: \'w\', Right: \'d\'\n");

    int round = 0;
    while (!isGameOver()) {
        printf("Round: %d\n", round);
        printf("Sorce: %d\n", _sorce);

        randomGenerate(2);
        printCheckerboard();

        char direction[2] = "w";
        scanf("%s", direction);

        printf("%s", direction);

        switch (direction[0]) {
            case 'w':
                move(MOVE_UP);
                break;
            case 's':
                move(MOVE_DOWN);
                break;
            case 'a':
                move(MOVE_LEFT);
                break;
            case 'd':
                move(MOVE_RIGHT);
                break;
        }

        printf("\n");
    }
}

int** Game::getCheckerboard() {
    return (int**)_checkerboard;
}

void Game::move(int direction) {
    switch (direction) {
        case MOVE_UP:
            _sorce += moveUp();
            break;
        case MOVE_DOWN:
            _sorce += moveDown();
            break;
        case MOVE_LEFT:
            _sorce += moveLeft();
            break;
        case MOVE_RIGHT:
            _sorce += moveRight();
            break;
        default:
            printf("Wrong direction\n");
            break;
    }

    setupEmptyList();
}

void Game::printCheckerboard() {
    for (int row = 0; row < CHECKERBOARD_LENGTH; row++) {
        for (int col = 0; col < CHECKERBOARD_LENGTH; col++) {
            printf("%3d", _checkerboard[row][col]);
        }
        printf("\n");
    }
}

void Game::initCheckerBoard() {
    for (int row = 0; row < CHECKERBOARD_LENGTH; row++) {
        for (int col = 0; col < CHECKERBOARD_LENGTH; col++) {
            _checkerboard[row][col] = 0;
        }
    }
}

void Game::setupEmptyList() {
    _empty_list.clear();
    for (int row = 0; row < CHECKERBOARD_LENGTH; row++) {
        for (int col = 0; col < CHECKERBOARD_LENGTH; col++) {
            if (_checkerboard[row][col] == 0) {
                CheckerboardIndex index_set = {row, col};

                _empty_list.add(index_set);
            }
        }
    }
}

void Game::randomGenerate(int generate_amount) {
    srand(time(NULL));
    for (int i = 0; i < generate_amount; i++) {
        if (_empty_list.isEmpty()) {
            return;
        }
        int idx = rand() % _empty_list.size();
        CheckerboardIndex cb_idx = _empty_list.get(idx);
        _checkerboard[cb_idx.row][cb_idx.col] = ((rand() % 2) + 1) * 2;
        _empty_list.remove(idx);
    }
}

void Game::mergeGrid(CheckerboardIndex target, CheckerboardIndex operate, int &reward, CheckerboardIndex &stop_index) {
    if ((_checkerboard[target.row][target.col] == _checkerboard[operate.row][operate.col]) ||
        (_checkerboard[target.row][target.col] == 0)) {

        if (_checkerboard[target.row][target.col] != 0) {
            reward += _checkerboard[target.row][target.col] + _checkerboard[operate.row][operate.col];
            stop_index = operate;
        }
        _checkerboard[target.row][target.col] += _checkerboard[operate.row][operate.col];
        _checkerboard[operate.row][operate.col] = 0;
    }
}

int Game::moveUp() {
    int reward = 0;
    for (int col = 0; col < CHECKERBOARD_LENGTH; col ++) {
        CheckerboardIndex stop_index = {0, col};
        for (int row = 0; row < CHECKERBOARD_LENGTH; row++) {

            for (int i = row; i > stop_index.row; i--) {
                CheckerboardIndex target = {i-1, col};
                CheckerboardIndex operate = {i, col};
                mergeGrid(target, operate, reward, stop_index);
            }
        }
    }
    return reward;
}

int Game::moveDown() {
    int reward = 0;
    for (int col = 0; col < CHECKERBOARD_LENGTH; col ++) {
        CheckerboardIndex stop_index = {CHECKERBOARD_LENGTH - 1, col};
        for (int row = CHECKERBOARD_LENGTH - 1; row >= 0; row--) {

            for (int i = row; i < stop_index.row; i++) {
                CheckerboardIndex target = {i+1, col};
                CheckerboardIndex operate = {i, col};
                mergeGrid(target, operate, reward, stop_index);
            }
        }
    }
    return reward;}

int Game::moveLeft() {
    int reward = 0;
    for (int row = 0; row < CHECKERBOARD_LENGTH; row++) {
        CheckerboardIndex stop_index = {row, 0};
        for (int col = 0; col < CHECKERBOARD_LENGTH; col++) {

            for (int i = col; i > stop_index.col; i--) {
                CheckerboardIndex target = {row, i-1};
                CheckerboardIndex operate = {row, i};
                mergeGrid(target, operate, reward, stop_index);
            }
        }
    }
    return reward;
}

int Game::moveRight() {
    int reward = 0;
    for (int row = 0; row < CHECKERBOARD_LENGTH; row++) {
        CheckerboardIndex stop_index = {row, CHECKERBOARD_LENGTH - 1};
        for (int col = CHECKERBOARD_LENGTH - 1; col >= 0; col--) {

            for (int i = col; i < stop_index.col; i++) {
                CheckerboardIndex target = {row, i+1};
                CheckerboardIndex operate = {row, i};
                mergeGrid(target, operate, reward, stop_index);
            }
        }
    }
    return reward;
}

bool Game::isGameOver() {
    for (int row = 0; row < CHECKERBOARD_LENGTH; row++) {
        for (int col = 0; col < CHECKERBOARD_LENGTH; col++) {
            if ((row+1) < CHECKERBOARD_LENGTH) {
                if (_checkerboard[row][col] == _checkerboard[row+1][col]) {
                    return false;
                }
            }

            if ((col+1) < CHECKERBOARD_LENGTH) {
                if (_checkerboard[row][col] == _checkerboard[row][col+1]) {
                    return false;
                }
            }
        }
    }

    return true;
}
