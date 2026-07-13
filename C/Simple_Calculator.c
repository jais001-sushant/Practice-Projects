#include<stdio.h>
#include<math.h>

void choice_operation(int choice, int num1, int num2){
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
}

int main(){
    int choice;
    double num1, num2, result;

    while(1) {
        choice_operation(choice, num1, num2);
        scanf("%d", &choice);

        if (choice == 7) {
            printf("Exiting the calculator. Goodbye!\n");
            break;
        }
        else if (choice < 1 || choice > 7){
            printf("Invalid choice. Please select a valid option.\n");
            continue;
        }

        printf("Enter first number: ");
        scanf("%lf", &num1);
        printf("Enter second number: ");
        scanf("%lf", &num2);

        switch(choice){
            case 1:
                result = num1 + num2;
            break;
            case 2:
                result = num1 - num2;
            break;
            case 3:
                result = num1 * num2;
            break;
            case 4:
                result = num1 / num2;
            break;
            case 5:
                result = (int)num1 % (int)num2;
            break;
            case 6:
                result = pow(num1, num2);
            break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
                continue;
        }

        printf("Result: %.2f\n", result);
        printf("---------------------------------\n");
    };

    return 0;
}