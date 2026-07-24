#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<unistd.h>

#define HEIGHT 20
#define WIDTH 60
int score = 0;

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

struct termios oldt;

void reset_terminal_attributes() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void set_terminal_attributes() {
    tcgetattr(STDIN_FILENO, &oldt);
    atexit(reset_terminal_attributes);
    struct termios newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void draw_border() {
    clear_screen();
    printf("Welcome to the Snake Game!\n");
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        printf("#");
        for (int j = 0; j < WIDTH; j++) {
            printf(" ");
        }
        printf("#\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\nScore: %d\n", score);
}

int main() {
    set_terminal_attributes();
    draw_border();

    return 0;
}