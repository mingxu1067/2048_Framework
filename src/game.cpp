#include <stdio.h>
#include "game.h"

bool Game::_is_move_work;

Game::Game() {
    srand(time(NULL));
    initCheckerBoard();
    _empty_list = LinkedList();
    setupEmptyList();
    _sorce = 0;
}

Game::~Game() {
    deleteCheckerboard();
}

void Game::start() {
    printf("Up: \'w\', Down: \'s\', Left: \'a\', Right: \'d\'\n");

    randomGenerate(2);
    printCheckerboard();

    int round = 0;
    while (!isGameOver()) {
        printf("Round: %d\n", ++round);
        printf("Sorce: %ld\n", _sorce);

        char direction[2] = "w";
        scanf("%s", direction);

        switch (direction[0]) {
            case 'w':
                move(kMoveUp);
                break;
            case 's':
                move(kMoveDown);
                break;
            case 'a':
                move(kMoveLeft);
                break;
            case 'd':
                move(kMoveRight);
                break;
        }

        randomGenerate(1);
        printCheckerboard();

        printf("\n");
    }
}

void Game::reset() {
    deleteCheckerboard();
    initCheckerBoard();
    setupEmptyList();
    _sorce = 0;
}

int** Game::getCopyCheckerboard() {
    int** returnCheckerboard = new int*[CHECKERBOARD_LENGTH];
    for (int row = 0; row < CHECKERBOARD_LENGTH; row++) {
        *(returnCheckerboard+row) = new int[CHECKERBOARD_LENGTH];
        for (int col = 0; col < CHECKERBOARD_LENGTH; col++) {
            returnCheckerboard[row][col] = _checkerboard[row][col];
        }
    }

    return returnCheckerboard;
}

long Game::get_score() {
    return _sorce;
}

void Game::move(int direction) {
    switch (direction) {
        case kMoveUp:
            _sorce += moveUp(_checkerboard);
            break;
        case kMoveDown:
            _sorce += moveDown(_checkerboard);
            break;
        case kMoveLeft:
            _sorce += moveLeft(_checkerboard);
            break;
        case kMoveRight:
            _sorce += moveRight(_checkerboard);
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
            printf("%5d", _checkerboard[row][col]);
        }
        printf("\n");
    }
}

void Game::initCheckerBoard() {
    _checkerboard = new int*[CHECKERBOARD_LENGTH];
    for (int row = 0; row < CHECKERBOARD_LENGTH; row++) {
        *(_checkerboard+row) = new int[CHECKERBOARD_LENGTH];
        for (int col = 0; col < CHECKERBOARD_LENGTH; col++) {
            _checkerboard[row][col] = 0;
        }
    }
}

void Game::deleteCheckerboard() {
    for (int row = 0; row < CHECKERBOARD_LENGTH; row++) {
        delete [] _checkerboard[row];
    }

    delete [] _checkerboard;
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

bool Game::isMoveWork() {
    return _is_move_work;
}

void Game::mergeGrid(int **checkerboard, CheckerboardIndex target, CheckerboardIndex operate, long &reward, CheckerboardIndex &stop_index) {
    if ((checkerboard[target.row][target.col] == checkerboard[operate.row][operate.col]) ||
        (checkerboard[target.row][target.col] == 0)) {

        _is_move_work = true;

        if (checkerboard[target.row][target.col] != 0) {
            reward += checkerboard[target.row][target.col] + checkerboard[operate.row][operate.col];
            stop_index = operate;
        }
        checkerboard[target.row][target.col] += checkerboard[operate.row][operate.col];
        checkerboard[operate.row][operate.col] = 0;
    }
}

bool Game::isGameOver() {
    if (_empty_list.size() > 0) {
        return false;
    }

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
long Game::moveUp(int **checkerboard) {
    _is_move_work = false;
    long reward = 0;
    for (int col = 0; col < CHECKERBOARD_LENGTH; col ++) {
        CheckerboardIndex stop_index = {0, col};
        for (int row = 0; row < CHECKERBOARD_LENGTH; row++) {

            for (int i = row; i > stop_index.row; i--) {
                CheckerboardIndex target = {i-1, col};
                CheckerboardIndex operate = {i, col};
                mergeGrid(checkerboard, target, operate, reward, stop_index);
            }
        }
    }
    return reward;
}

long Game::moveDown(int **checkerboard) {
    _is_move_work = false;
    long reward = 0;
    for (int col = 0; col < CHECKERBOARD_LENGTH; col ++) {
        CheckerboardIndex stop_index = {CHECKERBOARD_LENGTH - 1, col};
        for (int row = CHECKERBOARD_LENGTH - 1; row >= 0; row--) {

            for (int i = row; i < stop_index.row; i++) {
                CheckerboardIndex target = {i+1, col};
                CheckerboardIndex operate = {i, col};
                mergeGrid(checkerboard, target, operate, reward, stop_index);
            }
        }
    }
    return reward;}

long Game::moveLeft(int **checkerboard) {
    _is_move_work = false;
    long reward = 0;
    for (int row = 0; row < CHECKERBOARD_LENGTH; row++) {
        CheckerboardIndex stop_index = {row, 0};
        for (int col = 0; col < CHECKERBOARD_LENGTH; col++) {

            for (int i = col; i > stop_index.col; i--) {
                CheckerboardIndex target = {row, i-1};
                CheckerboardIndex operate = {row, i};
                mergeGrid(checkerboard, target, operate, reward, stop_index);
            }
        }
    }
    return reward;
}

long Game::moveRight(int **checkerboard) {
    _is_move_work = false;
    long reward = 0;
    for (int row = 0; row < CHECKERBOARD_LENGTH; row++) {
        CheckerboardIndex stop_index = {row, CHECKERBOARD_LENGTH - 1};
        for (int col = CHECKERBOARD_LENGTH - 1; col >= 0; col--) {

            for (int i = col; i < stop_index.col; i++) {
                CheckerboardIndex target = {row, i+1};
                CheckerboardIndex operate = {row, i};
                mergeGrid(checkerboard, target, operate, reward, stop_index);
            }
        }
    }
    return reward;
}

