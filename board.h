#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 100
#define GRID_SIZE 3

typedef struct {
    int number;          // nomor petak (1-100)
    char event;          // 'u' untuk ular, 't' untuk tangga
    char eventConnect;   // penghubung event (misal 't1', 'u1')
    int players[4];      // array untuk menyimpan posisi pemain (max 4 pemain)
} Square;

void initializeBoard(Square board[]);
void printBoard(Square board[]);
void clearScreen();

#endif