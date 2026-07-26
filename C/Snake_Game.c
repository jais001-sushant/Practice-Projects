#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<unistd.h>
#include<time.h>

#define HEIGHT 20
#define WIDTH 60

enum Direction { UP, DOWN, LEFT, RIGHT, STOP };

enum Direction dir;
int score;
int fruit_x, fruit_y;
int head_x, head_y;
int tail_length;
int tail_x[100], tail_y[100];

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

void game_play() {
    for(int i = tail_length - 1; i > 0; i--) {
        tail_x[i] = tail_x[i - 1];
        tail_y[i] = tail_y[i - 1];
    }
    tail_x[0] = head_x;
    tail_y[0] = head_y;

    switch(dir) {
        case UP:
            head_y--;
            break;
        case DOWN:
            head_y++;
            break;
        case LEFT:
            head_x--;
            break;
        case RIGHT:
            head_x++;
            break;
        case STOP:
            break;
    }

    if (head_x < 0) {
        head_x = WIDTH - 1;
    } else if (head_x >= WIDTH) {
        head_x = 0;
    }

    if (head_y < 0) {
        head_y = HEIGHT - 1;
    } else if (head_y >= HEIGHT) {
        head_y = 0;
    }

    if (head_x == fruit_x && head_y == fruit_y) {
        score += 10;
        tail_length++;
        fruit_x = rand() % WIDTH;
        fruit_y = rand() % HEIGHT;
    }
}

int input_available() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

void input() {
    if (input_available()) {
        char ch = getchar();
        switch(ch) {
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'q':
                exit(0);
                break;
        }
    }
}

void setup_game() {
    head_x = WIDTH / 2;
    head_y = HEIGHT / 2;
    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HEIGHT;
    dir = STOP;
    score = 0;
    tail_length = 0;
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
                int tail_found = 0;
                for (int k = 0; k < tail_length; k++) {
                    if (tail_x[k] == j && tail_y[k] == i) {
                        printf("o");
                        tail_found = 1;
                        break;
                    }
                }
                if (!tail_found) {
                    printf(" ");
                }
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
    while (1) {
        draw_border();
        input();
        game_play();
        int delay = 300000 - (score * 2000);
        if (delay < 100000) {
            delay = 100000;
        }
        usleep(delay);
    }

    return 0;
}