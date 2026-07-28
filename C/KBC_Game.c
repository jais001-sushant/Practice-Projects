#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<termios.h>
#include<unistd.h>

#define MAX_QUES_LEN 300
#define MAX_OPTION_LEN 100

const char* PINK = "\033[1;35m";
const char* BLUE = "\033[1;34m";
const char* GREEN = "\033[1;32m";
const char* YELLOW = "\033[1;33m";
const char* RED = "\033[1;31m";
const char* CYAN = "\033[1;36m";
const char* COLOR_END = "\033[0m";
int Q = 0;

typedef struct {
    char text[MAX_QUES_LEN];
    char options[4][MAX_OPTION_LEN];
    char correct_option;
    int timeout;
    int prize_money;
} Question;

struct termios oldt;

void reset_terminal_attributes() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void set_terminal_attributes() {
    tcgetattr(STDIN_FILENO, &oldt);
    atexit(reset_terminal_attributes);
    struct termios newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

int read_questions(char* filename, Question** questions) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File doesn't exist\n");
        exit(0);
    }

    char str[MAX_QUES_LEN];
    int no_of_lines = 0;
    while (fgets(str, MAX_QUES_LEN, file) != NULL) {
        no_of_lines++;
    }
    int no_of_questions = no_of_lines / 8;
    *questions = (Question*)malloc(no_of_questions * sizeof(Question));
    rewind(file);
    for (int i = 0; i < no_of_questions; i++) {
        fgets((*questions)[i].text, MAX_QUES_LEN, file);

        for (int j = 0; j < 4; j++) {
            fgets((*questions)[i].options[j], MAX_OPTION_LEN, file);
        }

        char option[5];
        fgets(option, 5, file);
        (*questions)[i].correct_option = option[0];

        char timeout[10];
        fgets(timeout, 10, file);
        (*questions)[i].timeout = atoi(timeout);

        char prize_money[10];
        fgets(prize_money, 10, file);
        (*questions)[i].prize_money = atoi(prize_money);
    }

    fclose(file);
    return no_of_questions;
}

void print_formatted_question(Question question) {
    printf("\n%sQ%d: %s%s", YELLOW, ++Q, question.text, COLOR_END);
    for (int i = 0; i < 4; i++) {
        if (question.options[i][0] != '\0') {
            printf("%s%c. %s%s", CYAN, 'A' + i, question.options[i], COLOR_END);
        }
    }
    printf("\n%sHurry up! You have %d seconds to answer...%s\n", YELLOW, question.timeout, COLOR_END);
    printf("%sEnter your answer (A/B/C/D) or L for Lifeline: %s", GREEN, COLOR_END);

    // printf("Timeout: %d seconds\n", question.timeout);
    // printf("Prize Money: Rs.%d\n", question.prize_money);
}

int use_lifeline(Question* question, int* lifeline) {
    printf("\n%sAvailable Lifelines:%s", PINK, COLOR_END);
    if (lifeline[0]) printf("\n%s1. Fifty-Fifty (50-50)%s", PINK, COLOR_END);
    if (lifeline[1]) printf("\n%s2. Skip the Question%s", PINK, COLOR_END);
    printf("\n%sChoose a lifeline or 0 to return: %s", PINK, COLOR_END);

    char ch = getchar();
    printf("%c\n", toupper(ch));
    ch = toupper(ch);

    switch(ch){
        case '1':
            if (lifeline[0]) {
                lifeline[0] = 0;
                printf("\n%sFifty-Fifty Lifeline used! Two incorrect options removed.%s\n", PINK, COLOR_END);
                int correct_index = question->correct_option - 'A';
                int removed_count = 0;
                for (int i = 0; i < 4; i++) {
                    if (i != correct_index && removed_count < 2) {
                        question->options[i][0] = '\0';
                        removed_count++;
                    }
                }
            } else {
                printf("\n%sFifty-Fifty Lifeline already used!%s\n", RED, COLOR_END);
            }
            return 1;
        break;
        case '2':
            if (lifeline[1]) {
                lifeline[1] = 0;
                printf("\n%sSkip the Question Lifeline used! Moving to the next question.%s\n", PINK, COLOR_END);
                return 2;
            } else {
                printf("\n%sSkip the Question Lifeline already used!%s\n", RED, COLOR_END);
            }
            return 0;
        break;
        case '0':
            printf("\n%sReturning to the question...%s\n", PINK, COLOR_END);
            return 0;
        break;
        default:
            printf("\n%sInvalid input! Returning to the Question...%s\n", RED, COLOR_END);
        break;
    }

    return 0;
}

void play_game(Question* questions, int no_of_questions){
    int money_won = 0;
    int lifeline[] = {1, 1};
    for (int i = 0; i < no_of_questions; i++) {
        print_formatted_question(questions[i]);
        char ch = getchar();
        printf("%c\n", toupper(ch));
        ch = toupper(ch);

        if (ch != 'A' && ch != 'B' && ch != 'C' && ch != 'D' && ch != 'L') {
            printf("\n%sInvalid input! Please enter A, B, C, D or L.%s\n", RED, COLOR_END);
            i--;
            Q--;
            continue;
        }

        if (ch == 'L') {
            int value = use_lifeline(&questions[i], lifeline);
            if (value == 1) {
                i--;
                Q--;
            }
            else if (value == 2) {
                continue;
            }
            else if (value == 0) {
                i--;
                Q--;
            }
            else {
                printf("\n%sInvalid input! Returning to the Question...%s\n", RED, COLOR_END);
            }
            continue;
        }

        if (ch == questions[i].correct_option) {
            printf("%s\nCorrect answer!%s\n", GREEN, COLOR_END);
            money_won += questions[i].prize_money;
            printf("%sYou have won Rs.%d%s\n", BLUE, questions[i].prize_money, COLOR_END);
        } else {
            printf("%s\nWrong answer! The correct answer was %c.%s\n", RED, questions[i].correct_option, COLOR_END);
            break;
        }
    }

    printf("\n%sGame Over! You have won a total of Rs.%d%s\n", BLUE, money_won, COLOR_END);
}

int main() {
    set_terminal_attributes();

    printf("\n%sChalo Khelte hain KAUN BANEGA CROREPATI !!!%s\n", PINK, COLOR_END);

    Question* questions;
    int no_of_questions = read_questions("questions.txt", &questions);

    play_game(questions, no_of_questions);

    return 0;
}