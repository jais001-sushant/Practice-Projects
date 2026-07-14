#include<stdio.h>

const int BAR_LENGTH = 50;

int main(){
    int id = 3, progress = 40;
    int filled_length = (progress * BAR_LENGTH) / 100;

    printf("Task %d: [", id);
    for (int i = 0; i < BAR_LENGTH; i++) {
        if (i < filled_length) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%\n", progress);

    return 0;
}