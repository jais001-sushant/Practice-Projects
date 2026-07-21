#include<stdio.h>
#include<stdlib.h>

#define BOARD_SIZE 3

typedef struct {
    int player;
    int computer;
    int draw;
} Score;

int difficulty_level;
Score score = {.player = 0, .computer = 0, .draw = 0};

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return 1;
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return 1;
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return 1;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return 1;
    }
    return 0;
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    clear_screen();
    
    printf("\n\n\nScore — Player: %d, Computer: %d, Draws: %d\n\n", score.player, score.computer, score.draw);

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < BOARD_SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < BOARD_SIZE - 1) {
            printf("---+---+---\n");
        }
    }
    printf("\n");
}

void input_difficulty_level() {
    printf("\nWelcome to the tic-tac-toe game!\n\n");
    printf("Select difficulty level:\n");
    printf("1 - Human (Standard)\n");
    printf("2 - God Mode (Unbeatable)\n");
    printf("Choose an option (1 or 2): ");
    while (scanf("%d", &difficulty_level) != 1 || (difficulty_level != 1 && difficulty_level != 2)) {
        printf("\nInvalid input. Please enter 1 for Human or 2 for God Mode: ");
        while(getchar() != '\n');
    }
}

int main() {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    input_difficulty_level();
    print_board(board);

    return 0;
}