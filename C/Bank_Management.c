#include<stdio.h>
#include<string.h>

const char* ACCOUNT_FILE = "account.txt";

typedef struct {
    char name[30];
    int acc_no;
    float balance;
} Account;

void create_account() {
    Account acc;

    FILE *file;
    file = fopen(ACCOUNT_FILE, "a+");
    if (file == NULL) {
        printf("\nFile doesn't exist\n");
        return;
    }

    printf("\nCreating New Account:\n");
    printf("Enter your name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    int index = strcspn(acc.name, "\n");
    acc.name[index] = '\0';

    printf("Enter your account number: ");
    scanf("%d", &acc.acc_no);

    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\nAccount created successfully !!\n");
}

void deposit_money() {
    FILE *file;
    file = fopen(ACCOUNT_FILE, "r+");
    if (file == NULL) {
        printf("\nFile doesn't exist\n");
        return;
    }

    int acc_no;
    float deposit_amount;
    Account acc_update;

    printf("\nEnter you account number: ");
    scanf("%d", &acc_no);
    printf("\nEnter amount to deposit: ");
    scanf("%f", &deposit_amount);

    while(fread(&acc_update, sizeof(acc_update), 1, file)) {
        if (acc_update.acc_no == acc_no) {
            acc_update.balance += deposit_amount;

            fseek(file, -sizeof(acc_update), SEEK_CUR);
            fwrite(&acc_update, sizeof(acc_update), 1, file);
            fclose(file);
            printf("\n%.2f deposited in your account.\n", deposit_amount);
            printf("Your current balance is Rs.%.2f\n", acc_update.balance);
            return;
        }
    }
    fclose(file);
    printf("\nAccount No: %d was not found.\n", acc_no);
}

void withdraw_money() {
    FILE *file;
    file = fopen(ACCOUNT_FILE, "r+");
    if (file == NULL) {
        printf("\nFile doesn't exist\n");
        return;
    }

    int acc_no;
    float withdraw_amount;
    Account acc_up;

    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    printf("\nEnter amount to withdraw: ");
    scanf("%f", &withdraw_amount);

    while(fread(&acc_up, sizeof(acc_up), 1, file)) {
        if (acc_up.acc_no == acc_no) {
            if (acc_up.balance >= withdraw_amount) {
                acc_up.balance -= withdraw_amount;

                fseek(file, -sizeof(acc_up), SEEK_CUR);
                fwrite(&acc_up, sizeof(acc_up), 1, file);
                printf("\n%.2f withdraw from your account.\n", withdraw_amount);
                printf("Your current balance is Rs.%.2f\n", acc_up.balance);
            } else {
                printf("\nInsufficient Balance !!\n");
            }
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("\nAccount No: %d was not found.\n", acc_no);
}

void check_balance() {
    FILE *file;
    file = fopen(ACCOUNT_FILE, "r");
    if (file == NULL) {
        printf("\nFile doesn't exist\n");
        return;
    }

    int acc_no;
    Account acc_read;

    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);

    while(fread(&acc_read, sizeof(acc_read), 1, file)) {
        if (acc_read.acc_no == acc_no) {
            printf("\nYour current balance is Rs.%.2f\n", acc_read.balance);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("\nAccount No: %d was not found.\n", acc_no);
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
        getchar();

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