#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define BOARD_SIZE 10
#define MAX_NAME 50
#define MAX_TIME 30
#define EASY_TIME 30
#define MEDIUM_TIME 20
#define HARD_TIME 10

// Struktur untuk menyimpan informasi pemain
typedef struct {
    char name[MAX_NAME];
    int position;
    int score;
} Player;

// Struktur untuk menyimpan high score
typedef struct {
    char name[MAX_NAME];
    int score;
    int time;
} HighScore;

// Struktur untuk papan permainan
typedef struct {
    int value;
    char type;  // 'S' untuk ular, 'L' untuk tangga, ' ' untuk kosong
    int destination;
} Board;

Board gameBoard[BOARD_SIZE][BOARD_SIZE];
HighScore highScores[5];

// Fungsi untuk inisialisasi papan permainan
void initializeBoard() {
    // Inisialisasi papan kosong
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            gameBoard[i][j].value = BOARD_SIZE * i + j + 1;
            gameBoard[i][j].type = ' ';
            gameBoard[i][j].destination = 0;
        }
    }

    // Menambahkan tangga
    gameBoard[9][0].type = 'L';
    gameBoard[9][0].destination = 38;
    gameBoard[7][3].type = 'L';
    gameBoard[7][3].destination = 84;
    gameBoard[6][2].type = 'L';
    gameBoard[6][2].destination = 44;
    gameBoard[2][8].type = 'L';
    gameBoard[2][8].destination = 68;

    // Menambahkan ular
    gameBoard[3][9].type = 'S';
    gameBoard[3][9].destination = 16;
    gameBoard[6][6].type = 'S';
    gameBoard[6][6].destination = 25;
    gameBoard[8][5].type = 'S';
    gameBoard[8][5].destination = 32;
    gameBoard[9][7].type = 'S';
    gameBoard[9][7].destination = 12;
}

// Fungsi untuk menampilkan papan permainan
void displayBoard(Player p1, Player p2) {
    system("cls");
    printf("\n=== PAPAN PERMAINAN ULAR TANGGA ===\n\n");
    
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            int currentPos = gameBoard[i][j].value;
            
            if(currentPos == p1.position && currentPos == p2.position)
                printf("[P1P2]");
            else if(currentPos == p1.position)
                printf("[P1  ]");
            else if(currentPos == p2.position)
                printf("[P2  ]");
            else
                printf("[%2d%c ]", currentPos, gameBoard[i][j].type);
        }
        printf("\n");
    }
    printf("\nPemain 1 (%s): Posisi %d\n", p1.name, p1.position);
    printf("Pemain 2 (%s): Posisi %d\n", p2.name, p2.position);
}

// Fungsi untuk melempar dadu
int rollDice() {
    return (rand() % 6) + 1;
}

// Fungsi AI untuk komputer
int computerMove(int currentPos, int difficulty) {
    int dice = rollDice();
    int newPos = currentPos + dice;
    
    // Logika AI berdasarkan tingkat kesulitan
    if(difficulty == 1) { // Mudah - random
        return dice;
    }
    else if(difficulty == 2) { // Sedang - mencoba menghindari ular
        for(int i = 0; i < BOARD_SIZE; i++) {
            for(int j = 0; j < BOARD_SIZE; j++) {
                if(gameBoard[i][j].value == newPos && gameBoard[i][j].type == 'S') {
                    dice = rollDice(); // Coba lempar lagi jika akan kena ular
                    break;
                }
            }
        }
    }
    else { // Sulit - mencoba mendapatkan tangga
        for(int i = 0; i < BOARD_SIZE; i++) {
            for(int j = 0; j < BOARD_SIZE; j++) {
                if(gameBoard[i][j].value == newPos && gameBoard[i][j].type == 'L') {
                    return dice; // Ambil langkah ini jika ada tangga
                }
            }
        }
    }
    
    return dice;
}

// Fungsi untuk mengecek dan memindahkan posisi (ular/tangga)
int checkPosition(int position) {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(gameBoard[i][j].value == position) {
                if(gameBoard[i][j].type == 'S' || gameBoard[i][j].type == 'L') {
                    return gameBoard[i][j].destination;
                }
            }
        }
    }
    return position;
}

// Fungsi untuk menyimpan high score
void saveHighScore(Player winner, int timeSpent) {
    // Implementasi penyimpanan high score ke file
    FILE *file = fopen("highscores.txt", "a");
    if(file != NULL) {
        fprintf(file, "%s %d %d\n", winner.name, winner.score, timeSpent);
        fclose(file);
    }
}

// Fungsi utama permainan
void playGame() {
    Player player1, player2;
    int difficulty, timeLimit, currentTime;
    char gameMode;
    
    printf("=== PERMAINAN ULAR TANGGA ===\n");
    printf("Pilih mode permainan (1: vs Komputer, 2: vs Pemain): ");
    scanf(" %c", &gameMode);
    
    printf("Masukkan nama pemain 1: ");
    scanf("%s", player1.name);
    player1.position = 1;
    player1.score = 0;
    
    if(gameMode == '1') {
        strcpy(player2.name, "Computer");
        printf("Pilih tingkat kesulitan (1: Mudah, 2: Sedang, 3: Sulit): ");
        scanf("%d", &difficulty);
        
        switch(difficulty) {
            case 1: timeLimit = EASY_TIME; break;
            case 2: timeLimit = MEDIUM_TIME; break;
            case 3: timeLimit = HARD_TIME; break;
            default: timeLimit = EASY_TIME;
        }
    } else {
        printf("Masukkan nama pemain 2: ");
        scanf("%s", player2.name);
        timeLimit = EASY_TIME;
    }
    
    player2.position = 1;
    player2.score = 0;
    
    initializeBoard();
    int turn = 1;
    time_t startTime, currentTurn;
    
    while(1) {
        displayBoard(player1, player2);
        
        startTime = time(NULL);
        Player *currentPlayer = (turn == 1) ? &player1 : &player2;
        
        printf("\nGiliran %s\n", currentPlayer->name);
        
        if(gameMode == '1' && turn == 2) {
            Sleep(1000); // Delay untuk simulasi komputer berpikir
            int dice = computerMove(currentPlayer->position, difficulty);
            printf("Komputer melempar dadu: %d\n", dice);
            currentPlayer->position += dice;
        } else {
            printf("Tekan Enter untuk melempar dadu...");
            getchar();
            getchar();
            
            currentTurn = time(NULL);
            if(currentTurn - startTime > timeLimit) {
                printf("Waktu habis! Giliran dilewati\n");
                Sleep(1000);
                turn = (turn == 1) ? 2 : 1;
                continue;
            }
            
            int dice = rollDice();
            printf("Dadu menunjukkan: %d\n", dice);
            currentPlayer->position += dice;
        }
        
        // Cek posisi setelah bergerak
        currentPlayer->position = checkPosition(currentPlayer->position);
        
        // Cek kemenangan
        if(currentPlayer->position >= BOARD_SIZE * BOARD_SIZE) {
            displayBoard(player1, player2);
            printf("\n%s MENANG!\n", currentPlayer->name);
            currentPlayer->score = 100;
            
            // Simpan high score
            int totalTime = (int)(time(NULL) - startTime);
            saveHighScore(*currentPlayer, totalTime);
            break;
        }
        
        // Ganti giliran
        turn = (turn == 1) ? 2 : 1;
        Sleep(1000);
    }
}

int main() {
    srand(time(NULL));
    char playAgain;
    
    do {
        playGame();
        printf("\nMain lagi? (y/n): ");
        scanf(" %c", &playAgain);
    } while(playAgain == 'y' || playAgain == 'Y');
    
    return 0;
}