#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    return !(row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ');
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    clear_screen();
    
    printf("\n\n\nScore — Player (X): %d, Computer (O): %d, Draws: %d\n\n", score.player, score.computer, score.draw);
    printf("Current Tic Tac Toe Board:\n\n");

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

void player_move(char board[BOARD_SIZE][BOARD_SIZE]) {
    int count = 0, x, y;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                count++;
                x = i;
                y = j;
            }
        }
    }

    if (count == 1) {
        board[x][y] = X;
        return;
    }

    int row, col;
    do {
        printf("Player X's turn.\n");
        printf("Enter row and column (1-3) for X: ");
        while (scanf("%d %d", &row, &col) != 2 || !is_valid_move(board, row - 1, col - 1)) {
            printf("\nInvalid input. Please enter row and column (1-3) for X: ");
            while(getchar() != '\n');
        }
        row--;
        col--;
    } while (!is_valid_move(board, row, col));
    board[row][col] = X;

}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE]) {

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = O;
                if (check_win(board, O)) {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = X;
                if (check_win(board, X)) {
                    board[i][j] = O;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    if (difficulty_level == 2) {
        if (board[1][1] == ' ') {
            board[1][1] = O;
            return;
        }

        if (board[0][0] == X && board[2][1] == X && board[2][0] == ' ') {
            board[2][0] = O;
            return;
        }

        if (board[2][0] == X && board[1][2] == X && board[2][2] == ' ') {
            board[2][2] = O;
            return;
        }

        int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
        for (int i = 0; i < 4; i++) {
            if (board[corners[i][0]][corners[i][1]] == ' ') {
                board[corners[i][0]][corners[i][1]] = O;
                return;
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = O;
                return;
            }
        }
    }
}

void play_game() {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char current_player = rand() % 2 == 0 ? X : O;

    print_board(board);
    while (1) {

        if (current_player == X) {
            player_move(board);
            print_board(board);
            if (check_win(board, X)) {
                score.player++;
                print_board(board);
                printf("Congratulations!! You win!\n");
                return;
            }
            current_player = O;
        } else {
            computer_move(board);
            print_board(board);
            if (check_win(board, O)) {
                score.computer++;
                print_board(board);
                printf("Computer wins! Better luck next time!\n");
                return;
            }
            current_player = X;
        }

        if (check_draw(board)) {
            score.draw++;
            print_board(board);
            printf("It's a draw!\n");
            return;
        }
    }
    
    print_board(board);
}

void input_difficulty_level() {
    printf("\n\n\nWelcome to the Tic Tac Toe game!\n\n");
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
    srand(time(NULL));
    int play_again;
    clear_screen();
    input_difficulty_level();
    
    do {
        play_game();
        printf("\nPlay Again? (1 for yes, 0 for no): ");
        while (scanf("%d", &play_again) != 1 || (play_again != 1 && play_again != 0)) {
            printf("\nInvalid input. Please enter 1 for yes or 0 for no: ");
            while(getchar() != '\n');
        }
    } while (play_again == 1);

    if (play_again == 0) {
        printf("\nThank you for playing!\n\n");
    }

    return 0;
}