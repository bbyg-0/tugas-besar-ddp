#include <stdio.h>
#include "board.h"

int main() {
    Square board[BOARD_SIZE];
    initializeBoard(board);
    printBoard(board);
    return 0;
}