#include<stdio.h>
#include<time.h>

void display_time(char* buffer, int format){
    time_t raw_time;
    struct tm *current_time;

    time(&raw_time);
    current_time = localtime(&raw_time);

    if(format == 2) {
        strftime(buffer, 50, "%H:%M:%S", current_time);
    }
    else if (format < 1 || format > 2) {
        printf("Invalid format choice. Defaulting to 12-hour format.\n");
        strftime(buffer, 50, "%I:%M:%S %p", current_time);
    }
    else {
        strftime(buffer, 50, "%I:%M:%S %p", current_time);
    }
}

int format_choice(int format) {
    printf("\nSelect time format:\n");
    printf("1. 12-hour format (default)\n");
    printf("2. 24-hour format\n");
    printf("Enter your choice (1 or 2): ");
    if(scanf("%d", &format) != 1) {
        printf("Invalid input. Defaulting to 12-hour format.\n");
        return 1;
    }
    return format;
}

int main(){
    char time[50];
    int format = format_choice(format);

    display_time(time, format);

    printf("Current Time: %s\n\n", time);

    return 0;
}