#include<stdio.h>

int main() {
    int choice;

    while(1) {
        printf("\n*** Bank Management System ***\n");
        printf("Please select an option:\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");
        printf("\nEnter your choice (1-5): ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a valid number.\n");
            while(getchar() != '\n');
            continue;
        }

        if (choice == 5){
            printf("\nExiting the User Management System. Goodbye!\n");
            break;
        }

        else if (choice < 1 || choice > 5){
            printf("\nInvalid choice! Please select a valid option.\n");
            continue;
        }
    }
    
    return 0;
}