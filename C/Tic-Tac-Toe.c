#include<stdio.h>
#include<stdlib.h>

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
    input_difficulty_level();
    // clear_screen();
    printf("\033[H\033[2J");

    return 0;
}