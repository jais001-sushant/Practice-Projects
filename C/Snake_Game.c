#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<unistd.h>

#define HEIGHT 20
#define WIDTH 60
int score = 0;
int fruit_x = 10, fruit_y = 10;
int head_x = 30, head_y = 10;

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
    printf("\n\t\tWelcome to the Snake Game!\n\n");
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        printf("#");
        for (int j = 0; j < WIDTH; j++) {
            if (i == head_y && j == head_x) {
                printf("O");
            }
            else if (i == fruit_y && j == fruit_x) {
                printf("*");
            }
            else {
                printf(" ");
            }
        }
        printf("#\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n\nScore: %d\n", score);
}

int main() {
    set_terminal_attributes();
    draw_border();

    return 0;
}