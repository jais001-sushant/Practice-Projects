#include<stdio.h>

void create_account() {
    printf("\nCreating Account\n");
}

void deposit_money() {
    printf("\nMoney Deposited\n");
}

void withdraw_money() {
    printf("\nMoney Withdraw\n");
}

void check_balance() {
    printf("\nCurrent Balance: \n");
}

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
            printf("\nExiting the Bank Management System. Goodbye!\n\n");
            break;
        }

        else if (choice < 1 || choice > 5){
            printf("\nInvalid choice! Please select a valid option.\n");
            continue;
        }

        switch(choice){
            case 1:
                create_account();
            break;

            case 2:
                deposit_money();
            break;

            case 3:
                withdraw_money();
            break;

            case 4:
                check_balance();
            break;

            default:
                printf("Invalid choice! Please select a valid option.");
                continue;
        }
    }
    
    return 0;
}