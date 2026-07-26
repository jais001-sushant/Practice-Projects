#include<stdio.h>
#include<stdlib.h>

#define MAX_QUES_LEN 300
#define MAX_OPTION_LEN 100

typedef struct {
    char text[MAX_QUES_LEN];
    char options[4][MAX_OPTION_LEN];
    char correct_option;
    int timeout;
    int prize_money;
} Question;

void read_questions(char* filename, Question* questions) {
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
    questions = (Question*)malloc(no_of_questions * sizeof(Question));

    rewind(file);
    for (int i = 0; i < no_of_questions; i++) {
        fgets(questions[i].text, MAX_QUES_LEN, file);
        
        for (int j = 0; j < 4; j++) {
            fgets(questions[i].options[j], MAX_OPTION_LEN, file);
        }

        char option[5];
        fgets(option, 5, file);
        questions[i].correct_option = option[0];

        char timeout[10];
        fgets(timeout, 10, file);
        questions[i].timeout = atoi(timeout);

        char prize_money[10];
        fgets(prize_money, 10, file);
        questions[i].prize_money = atoi(prize_money);
    }

    fclose(file);
}

int main() {
    Question* questions;
    read_questions("questions.txt", questions);

    return 0;
}