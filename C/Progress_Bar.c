#include<stdio.h>

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

int main(){
    Task tasks[] = {
        {1, 70, 5},
        {2, 90, 10},
        {3, 40, 20},
        {4, 100, 0},
        {5, 0, 15}
    };

    for (int i = 0; i < 5; i++) {
        print_bar(tasks[i]);
    }

    return 0;
}