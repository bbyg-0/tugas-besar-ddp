#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void initializeBoard(Square board[]) {
    for(int i = 0; i < BOARD_SIZE; i++) {
        board[i].number = i + 1;
        board[i].event = ' ';
        board[i].eventConnect = ' ';
        for(int j = 0; j < 4; j++) {
            board[i].players[j] = 0;
        }
    }
    
    // Inisialisasi tangga
    board[3].event = 't';
    board[3].eventConnect = '1';
    board[15].event = 't';
    board[15].eventConnect = '1';
    
    board[8].event = 't';
    board[8].eventConnect = '2';
    board[30].event = 't';
    board[30].eventConnect = '2';
    
    // Inisialisasi ular
    board[97].event = 'u';
    board[97].eventConnect = '1';
    board[78].event = 'u';
    board[78].eventConnect = '1';
    
    board[95].event = 'u';
    board[95].eventConnect = '2';
    board[45].event = 'u';
    board[45].eventConnect = '2';
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printBoard(Square board[]) {
    clearScreen();
    printf("\n=== PAPAN ULAR TANGGA ===\n\n");
    
    // Cetak board dari atas ke bawah (100 ke 1)
    for(int row = 9; row >= 0; row--) {
        // Cetak 3 baris untuk setiap baris petak
        for(int subrow = 0; subrow < 3; subrow++) {
            // Cetak garis horizontal untuk semua petak dalam baris
            for(int col = 0; col < 10; col++) {
                printf("+---+---+---+");
            }
            printf("\n");
            
            // Cetak isi petak
            for(int col = 0; col < 10; col++) {
                int index;
                if(row % 2 == 0) {
                    index = row * 10 + (9 - col);  // Reverse untuk baris genap
                } else {
                    index = row * 10 + col;        // Normal untuk baris ganjil
                }
                
                if(subrow == 0) {
                    // Baris pertama: Nomor petak
                    printf("| %2d|   |   |", board[index].number);
                }
                else if(subrow == 1) {
                    // Baris kedua: Event dan Player 1,2
                    char p1 = board[index].players[0] ? '1' : ' ';
                    char p2 = board[index].players[1] ? '2' : ' ';
                    printf("|%c%c |   | %c |", p1, p2, board[index].event);
                }
                else {
                    // Baris ketiga: Player 3,4 dan Event Connect
                    char p3 = board[index].players[2] ? '3' : ' ';
                    char p4 = board[index].players[3] ? '4' : ' ';
                    printf("|%c%c |   | %c |", p3, p4, board[index].eventConnect);
                }
            }
            printf("\n");
        }
    }
    
    // Cetak garis horizontal terakhir
    for(int col = 0; col < 10; col++) {
        printf("+---+---+---+");
    }
    printf("\n");
}