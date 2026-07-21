#include<stdio.h>
#include<stdlib.h>

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'

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

int check_draw(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
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

void player_move(char board[BOARD_SIZE][BOARD_SIZE]) {}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE]) {}

void play_game() {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char current_player = rand() ? X : O;

    while (1) {
        print_board(board);

        if (current_player == X) {
            player_move(board);
            if (check_win(board, X)) {
                score.player++;
                printf("Congratulations!! You win!\n");
                return;
            }
            current_player = O;
        } else {
            computer_move(board);
            if (check_win(board, O)) {
                score.computer++;
                printf("Computer wins!\n");
                return;
            }
            current_player = X;
        }

        if (check_draw(board)) {
            score.draw++;
            printf("It's a draw!\n");
            return;
        }
    }
    
    print_board(board);
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
    int play_again;

    input_difficulty_level();
    play_game();

    printf("\nPlay Again? (1 for yes, 0 for no): ");
    while (scanf("%d", &play_again) != 1 || (play_again != 1 && play_again != 0)) {
        printf("\nInvalid input. Please enter 1 for yes or 0 for no: ");
        while(getchar() != '\n');
    }

    if (play_again == 1) {
        main();
    }
    if (play_again == 0) {
        printf("\nThank you for playing!\n\n");
    }

    return 0;
}