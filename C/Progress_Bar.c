#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

const int BAR_LENGTH = 50;

typedef struct {
    int id;
    int progress;
    int step;
} Task;

void print_bar(Task task){
    int filled_length = (task.progress * BAR_LENGTH) / 100;

    printf("Task %d: [", task.id);
    for (int i = 0; i < BAR_LENGTH; i++) {
        if (i < filled_length) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%\n", task.progress);
}

void clear_console() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main(){
    Task tasks[5];
    srand(time(0));

    for (int i = 0; i < 5; i++) {
        tasks[i].id = i + 1;
        tasks[i].progress = 0;
        tasks[i].step = rand() % 5 + 1;
    }

    while (1) {
        int all_done = 1;
        // clear_console(); // Clear console
        printf("\033[H\033[J"); // Clear console
        for (int i = 0; i < 5; i++) {
            if (tasks[i].progress < 100) {
                tasks[i].progress += tasks[i].step;
                if (tasks[i].progress > 100) {
                    tasks[i].progress = 100;
                }
                all_done = 0;
            }
            print_bar(tasks[i]);
        }

        if (all_done) {
            break;
        }

        printf("\n");
        sleep(1);
    }

    printf("\nAll tasks completed!\n");

    return 0;
}