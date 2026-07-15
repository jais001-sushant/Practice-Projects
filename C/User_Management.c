#include<stdio.h>
#include<string.h>

#define MAX_USERS 10
#define CREDENTIAL_LENGTH 30

typedef struct {
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void register_user() {
    if (user_count >= MAX_USERS) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }

    printf("\nRegister a new user:\n");
    printf("Enter username: ");
    fgets(users[user_count].username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(users[user_count].username);
    input_password(users[user_count].password);

    user_count++;
    printf("User registered successfully!\n");
}
 
int login_user() {
    return -1;
}

void fix_fgets_input(char* string) {
    int index = strcspn(string, "\n");
    string[index] = '\0';
}

void input_password(char* password) {
    printf("Enter password: ");
    fgets(password, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(password);
}

int main(){
    int option;
    int user_index;

    while (1){
        printf("\nWelcome to the User Management System!\n");
        printf("Please select an option:\n");
        printf("1. Register User\n");
        printf("2. Login User\n");
        printf("3. Display Users\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("\nEnter your choice (1-5): ");
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
                register_user();
            break;

            case 2:
                user_index = login_user();
                if (user_index != -1) {
                    printf("User logged in successfully!\n");
                } else {
                    printf("Invalid username or password. Please try again.\n");
                }
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