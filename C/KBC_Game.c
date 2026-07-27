#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_QUES_LEN 300
#define MAX_OPTION_LEN 100

const char* PINK = "\033[1;35m";
const char* BLUE = "\033[1;34m";
const char* GREEN = "\033[1;32m";
const char* YELLOW = "\033[1;33m";
const char* RED = "\033[1;31m";
const char* CYAN = "\033[1;36m";
const char* COLOR_END = "\033[0m";

typedef struct {
    char text[MAX_QUES_LEN];
    char options[4][MAX_OPTION_LEN];
    char correct_option;
    int timeout;
    int prize_money;
} Question;

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
    printf("\n%s%s%s", YELLOW, question.text, COLOR_END);
    for (int i = 0; i < 4; i++) {
        printf("%s%c. %s%s", CYAN, 'A' + i, question.options[i], COLOR_END);
    }
    printf("\n%sHurry up! You have %d seconds to answer...%s\n", YELLOW, question.timeout, COLOR_END);
    printf("%sEnter your answer (A/B/C/D) or L for Lifeline: %s", GREEN, COLOR_END);

    // printf("Correct Option: %c\n", question.correct_option);
    // printf("Timeout: %d seconds\n", question.timeout);
    // printf("Prize Money: Rs.%d\n", question.prize_money);
}

void play_game(Question* questions, int no_of_questions){
    int money_won = 0;
    for (int i = 0; i < no_of_questions; i++) {
        print_formatted_question(questions[i]);
        char ch = getchar();
        ch = toupper(ch);

        if (ch == 'L') {
            printf("No lifelines available yet.\n");
            break;
        }

        if (ch == questions[i].correct_option) {
            printf("%sCorrect answer!%s\n", GREEN, COLOR_END);
            money_won += questions[i].prize_money;
            printf("%sYou have won Rs.%d%s\n", BLUE, questions[i].prize_money, COLOR_END);
        } else {
            printf("%sWrong answer! The correct answer was %c.%s\n", RED, questions[i].correct_option, COLOR_END);
            break;
        }
    }

    printf("\n\n%sGame Over! You have won a total of Rs.%d%s\n", BLUE, money_won, COLOR_END);
}

int main() {
    printf("\n%sChalo Khelte hain KAUN BANEGA CROREPATI !!!%s\n", PINK, COLOR_END);

    Question* questions;
    int no_of_questions = read_questions("questions.txt", &questions);

    play_game(questions, no_of_questions);

    return 0;
}