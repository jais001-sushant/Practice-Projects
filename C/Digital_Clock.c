#include<stdio.h>
#include<time.h>

void display_time(char* buffer){
    time_t raw_time;
    struct tm *current_time;

    time(&raw_time);
    current_time = localtime(&raw_time);
    strftime(buffer, 50, "%I:%M:%S %p", current_time);
}

int main(){
    char buffer[50];
    display_time(buffer);

    printf("Current Time: %s\n", buffer);

    return 0;
}