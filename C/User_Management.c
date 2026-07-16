#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<termios.h>

#define MAX_USERS 10
#define CREDENTIAL_LENGTH 30

typedef struct {
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void fix_fgets_input(char* string) {
    int index = strcspn(string, "\n");
    string[index] = '\0';
}

void input_credentials(char* username, char* password) {
    printf("Enter username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);
    printf("Enter password: \n");

    struct termios old_props, new_props;
    tcgetattr(STDIN_FILENO, &old_props);
    new_props = old_props;
    new_props.c_lflag = ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_props);

    char ch;
    int i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF){
        password[i++] = ch;
    }
    password[i] = '\0';
    tcsetattr(STDIN_FILENO, TCSANOW, &old_props);
}

void register_user() {
    if (user_count >= MAX_USERS) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }

    printf("\nRegister a new user:\n");
    input_credentials(users[user_count].username, users[user_count].password);

    user_count++;
    printf("User registered successfully!\n");
}
 
int login_user() {
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];

    printf("\nLogin:\n");
    input_credentials(username, password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
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
        scanf("%d", &option);
        getchar();

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
                    printf("Login successful! Welcome, %s\n", users[user_index].username);
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