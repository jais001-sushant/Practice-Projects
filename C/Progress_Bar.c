#include<stdio.h>

const int BAR_LENGTH = 50;

void print_bar(int id, int progress){
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
}

int main(){
    // int id = 3, progress = 40;
    print_bar(1, 70);
    print_bar(2, 90);
    print_bar(3, 40);
    print_bar(4, 100);
    print_bar(5, 0);

    return 0;
}