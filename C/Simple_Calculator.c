#include<stdio.h>
#include<math.h>

void choice_operation(int choice, int num1, int num2){
    printf("--------------------------------\n");
    printf("\nWelcome to the Simple Calculator\n");
    printf("\nSelect an operation:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Modulus\n");
    printf("6. Power\n");
    printf("7. Exit\n");
    printf("Enter your choice (1-7): ");
}

int main(){
    int choice;
    double num1, num2, result;

    while(1) {
        choice_operation(choice, num1, num2);
        if(scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while(getchar() != '\n');
            continue;
        }

        if (choice == 7) {
            printf("Exiting the calculator. Goodbye!\n");
            break;
        }
        else if (choice < 1 || choice > 7) {
            printf("Invalid choice! Please select a valid operation.\n");
            continue;
        }

        printf("\nEnter first number: ");
        if(scanf("%lf", &num1) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while(getchar() != '\n');
            continue;
        }
        printf("Enter second number: ");
        if(scanf("%lf", &num2) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while(getchar() != '\n');
            continue;
        }

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
                if(num2 == 0){
                    printf("Error: Division by zero is not allowed.\n");
                    continue;
                }
                result = num1 / num2;
            break;

            case 5:
                if(num2 == 0){
                    printf("Error: Modulus by zero is not allowed.\n");
                    continue;
                }
                result = (int)num1 % (int)num2;
            break;

            case 6:
                result = pow(num1, num2);
            break;

            default:
                printf("Invalid choice! Please select a valid operation.\n");
                continue;
        }

        printf("\nResult of the operation: %.2f",result);
        printf("\n--------------------------------\n");
    };

    return 0;
}