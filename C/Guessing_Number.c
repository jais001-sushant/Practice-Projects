#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    int random, guess, attempts = 0;

    srand(time(0));
    random = rand() % 100 + 1;

    printf("\nWelcome to the Guessing Game!\n");
    printf("I have selected a number between 1 and 100. Can you guess it?\n");

    do {
        printf("\nEnter your guess: ");
        scanf("%d", &guess);
        attempts++;

        if (guess < 1 || guess > 100) {
            printf("Please enter a number between 1 and 100.\n");
            continue;
        }
        if (guess < random) {
            printf("Too low! Try again.\n");
        } else if (guess > random) {
            printf("Too high! Try again.\n");
        } else {
            printf("Congratulations! You've guessed the number %d in %d attempts.\n\n", random, attempts);
        }

    } while (guess != random);

    return 0;
}