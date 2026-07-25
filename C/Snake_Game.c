#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<unistd.h>
#include<time.h>

#define HEIGHT 20
#define WIDTH 60

enum Direction { UP, DOWN, LEFT, RIGHT, STOP };

enum Direction dir;
int score = 0;
int fruit_x, fruit_y;
int head_x, head_y;

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

int input_available() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

void setup_game() {
    head_x = WIDTH / 2;
    head_y = HEIGHT / 2;
    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HEIGHT;
    dir = STOP;
}

void draw_border() {
    clear_screen();
    printf("\n\n\n\t\tWelcome to the Snake Game!\n\n");
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
    srand(time(NULL));
    set_terminal_attributes();
    setup_game();
    draw_border();

    return 0;
}