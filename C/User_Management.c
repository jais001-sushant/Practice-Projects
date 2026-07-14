#include<stdio.h>

int main(){
    int option;

    while (1){
        printf("\nWelcome to the User Management System!\n");
        printf("Please select an option:\n");
        printf("1. Register User\n");
        printf("2. Login User\n");
        printf("3. Display Users\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        if(scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while(getchar() != '\n');
            continue;
        }
        if (option == 5) {
            printf("Exiting the User Management System. Goodbye!\n");
            break;
        }
        else if (option < 1 || option > 5) {
            printf("Invalid choice! Please select a valid option.\n");
            continue;
        }

        switch(option){
            case 1:
                printf("Registering User...\n");
            break;

            case 2:
                printf("Logging in User...\n");
            break;

            case 3:
                printf("Displaying Users...\n");
            break;

            case 4:
                printf("Deleting User...\n");
            break;
            default:
                printf("Invalid choice! Please select a valid option.\n");
                continue;
        }
    }

    return 0;
}