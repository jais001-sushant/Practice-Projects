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
    printf("Enter password: ");
    fflush(stdout);

    struct termios old_props, new_props;
    tcgetattr(STDIN_FILENO, &old_props);
    new_props = old_props;
    new_props.c_lflag = ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_props);

    char ch;
    int i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF){
        if (ch == '\n' || ch == 127){
            if (i > 0){
                i--;
                printf("\b \b");
            }
        }
        else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    tcsetattr(STDIN_FILENO, TCSANOW, &old_props);
}

void register_user() {
    if (user_count >= MAX_USERS) {
        printf("\nUser limit reached. Cannot register more users.\n");
        return;
    }

    printf("\nRegister a new user:\n");
    input_credentials(users[user_count].username, users[user_count].password);

    user_count++;
    printf("\nUser registered successfully!\n");
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

void display_users() {
    if (user_count == 0) {
        printf("\nNo user found!! Please register any.\n");
        return;
    }

    printf("\nRegistered Users:\n");
    for (int i = 0; i < user_count; i++) {
        printf("%d. %s\n", i+1, users[i].username);
    }
}

void delete_user(){
    char username[CREDENTIAL_LENGTH];

    if (user_count == 0) {
        printf("\nNo users available to delete.\n");
        return;
    }

    printf("\nEnter username to delete: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);

    int delete_index = -1;
    for (int i= 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0){
            delete_index = i;
            break;
        }
    }

    if (delete_index == -1){
        printf("\nUser not found.\n");
        return;
    }

    for (int i = delete_index; i < user_count-1; i++) {
        users[i] = users[i + 1];
    }

    user_count--;
    printf("\nUser deleted successfully!\n");
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
            printf("\nExiting the User Management System. Goodbye!\n\n");
            break;
        }
        else if (option < 1 || option > 5) {
            printf("\nInvalid choice! Please select a valid option.\n");
            continue;
        }

        switch(option){
            case 1:
                register_user();
            break;

            case 2:
                user_index = login_user();
                if (user_index != -1) {
                    printf("\nLogin successful! Welcome, %s\n", users[user_index].username);
                } else {
                    printf("\nInvalid username or password. Please try again.\n");
                }
            break;

            case 3:
                display_users();
            break;

            case 4:
                delete_user();
            break;
            default:
                printf("\nInvalid choice! Please select a valid option.\n");
                continue;
        }
    }

    return 0;
}