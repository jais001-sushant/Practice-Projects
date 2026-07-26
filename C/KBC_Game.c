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
    while (fgets(str, sizeof(str), file) != NULL) {
        no_of_lines++;
    }
    int no_of_questions = no_of_lines / 8;
    questions = (Question*)malloc(no_of_questions * sizeof(Question));
}

int main() {
    Question* questions;
    read_questions("questions.txt", questions);

    return 0;
}