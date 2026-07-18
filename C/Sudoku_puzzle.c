#include<stdio.h>

int puzzle[9][9] = {
    {3,0,0,0,2,0,0,7,0},
    {9,0,0,5,0,0,0,1,4},
    {0,1,6,3,7,0,0,0,8},
    {2,0,0,8,0,0,0,0,1},
    {5,0,0,0,4,1,8,0,0},
    {0,8,9,0,0,0,0,5,0},
    {0,0,5,0,1,0,2,8,0},
    {0,4,0,0,0,6,0,9,3},
    {7,3,1,0,8,2,0,0,0}
};

int valid_move(int puzzle[9][9], int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (puzzle[row][i] == num) {
            return 0;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (puzzle[i][col] == num) {
            return 0;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[i + startRow][j + startCol] == num) {
                return 0;
            }
        }
    }

    return 1;
}

void print_puzzle(int puzzle[9][9]) {
    printf("\n\n+-------+-------+-------+\n");
    
    for (int row = 0; row < 9; row++){
        if (row % 3 == 0 && row != 0) {
            printf("|-------+-------+-------|\n");
        }
        for (int col = 0; col < 9; col++){
            if (col % 3 == 0) {
                printf("| ");
            }
            if (puzzle[row][col] != 0){
                printf("%d ", puzzle[row][col]);
            }
            else {
                printf("  ");
            }
        }
        printf("|\n");
    }

    printf("+-------+-------+-------+\n\n");
}

int main() {
    print_puzzle(puzzle);

    return 0;
}