#include<stdio.h>

int difficulty_level;

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

    return 0;
}