#include<stdio.h>

int main(){
    int choice;
    int num1, num2, result;

    do {
        printf("---------------------------------\n");
        printf("\nWelcome to the Simple Calculator\n");
        printf("\nSelect an operation:\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Modulus\n");
        printf("6. Power\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        printf("Enter first number: ");
        scanf("%d", &num1);
        printf("Enter second number: ");
        scanf("%d", &num2);

        printf("Result: \n");
        printf("---------------------------------\n");
    } while (choice != 7);

    return 0;
}