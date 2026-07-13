#include<stdio.h>

int main(){
    int choice;

    do {
        printf("Welcome to the Simple Calculator\n");
        printf("Select an operation:\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Modulus\n");
        printf("6. Power\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
    } while (choice != 7);

    return 0;
}