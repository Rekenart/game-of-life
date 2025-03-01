#include <stdio.h>
#include <stdlib.h>

void field(int** mas, int size_x, int size_y);
void input(int** mas, int size_count_x, int size_count_y);
void field_count(int** mas, int** count, int size_x, int size_y, int size_count_x, int size_count_y);
void output(int** mas, int i, int j);
void new_field(int** mas, int** count, int size_x, int size_y);
int left_upper_corner_counter(int** mas, int size_count_x, int size_count_y, int i, int j);
int right_upper_corner_counter(int** mas, int size_count_x, int i, int j);
int left_lower_corner_counter(int** mas, int size_count_y, int i, int j);
int right_lower_corner_counter(int** mas, int i, int j);
int left_side_counter(int** mas, int size_count_y, int i, int j);
int right_side_counter(int** mas, int i, int j);
int upper_side_counter(int** mas, int size_count_x, int i, int j);
int lower_side_counter(int** mas, int i, int j);
int another_counter(int** mas, int i, int j);

int main() {
    int size_x = 25;
    int size_y = 80;
    int size_count_x = size_x - 2;
    int size_count_y = size_y - 2;
    int** mas = malloc(size_x * size_y * sizeof(int) + size_x * sizeof(int*));
    int* ptr = (int*)(mas + size_x);
    for (int i = 0; i < size_x; i++) {
        mas[i] = ptr + size_y * i;
    }
    int** count = malloc(size_x * size_y * sizeof(int) + size_x * sizeof(int*));
    int* prt = (int*)(count + size_x);
    for (int i = 0; i < size_x; i++) {
        count[i] = prt + size_y * i;
    }
    input(mas, size_count_x, size_count_y);
    field(mas, size_x, size_y);
    for (int x = 0; x < 300; x++) {
        system("clear");
        for (int i = 0; i < size_x; i++) {
            printf("\n");
            for (int j = 0; j < size_y; j++) {
                output(mas, i, j);
                field_count(mas, count, size_x, size_y, size_count_x, size_count_y);
            }
        }
        new_field(mas, count, size_x, size_y);
        printf("\n");
        system("sleep 0.25");
    }
    free(mas);
    free(count);
    printf("\033[0d\033[2J");
}

void field(int** mas, int size_x, int size_y) {
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            mas[0][j] = '#';
            mas[i][0] = '#';
            if ((i == size_x - 1 || j == size_y - 1)) {
                mas[i][j] = '#';
            }
        }
    }
}

void input(int** mas, int size_count_x, int size_count_y) {
    for (int i = 1; i < size_count_x + 1; i++) {
        for (int j = 1; j < size_count_y + 2; j++) {
            char a;
            scanf("%c", &a);
            if (a == '\n') continue;
            mas[i][j] = a;
        }
    }
}

void field_count(int** mas, int** count, int size_x, int size_y, int size_count_x, int size_count_y) {
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            if (i == 1 && j == 1)
                count[i][j] = left_upper_corner_counter(mas, size_count_x, size_count_y, i, j);
            if (i == 1 && j == 78) count[i][j] = right_upper_corner_counter(mas, size_count_x, i, j);
            if (i == 23 && j == 1) count[i][j] = left_lower_corner_counter(mas, size_count_y, i, j);
            if (i == 23 && j == 78) count[i][j] = right_lower_corner_counter(mas, i, j);
            if (j == 1 && i > 1 && i < 23) count[i][j] = left_side_counter(mas, size_count_y, i, j);
            if (j == 78 && i > 1 && i < 23) count[i][j] = right_side_counter(mas, i, j);
            if (i == 1 && j != 1 && j != 78) count[i][j] = upper_side_counter(mas, size_count_x, i, j);
            if (i == 23 && j != 1 && j != 78) count[i][j] = lower_side_counter(mas, i, j);
            if (i > 1 && j > 1 && i < 23 && j < 78) count[i][j] = another_counter(mas, i, j);
            count[0][j] = 9;
            count[i][0] = 9;
            if ((i == size_x - 1 || j == size_y - 1)) {
                count[i][j] = 9;
            }
        }
    }
}

void new_field(int** mas, int** count, int size_x, int size_y) {
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            if (count[i][j] >= 4 || count[i][j] <= 1) mas[i][j] = '0';
            if (count[i][j] == 9) mas[i][j] = '#';
            if (count[i][j] == 3) mas[i][j] = '1';
        }
    }
}

void output(int** mas, int i, int j) {
    if (mas[i][j] == '1') printf("*");
    if (mas[i][j] == '#') printf("#");
    if (mas[i][j] == '0') printf(" ");
}

int left_upper_corner_counter(int** mas, int size_count_x, int size_count_y, int i, int j) {
    int counter = 0;
    if (mas[i + 1][j] == '1') counter += 1;
    if (mas[i][j + 1] == '1') counter += 1;
    if (mas[i + 1][j + 1] == '1') counter += 1;
    if (mas[size_count_x][size_count_y] == '1') counter += 1;
    if (mas[size_count_x][j] == '1') counter += 1;
    if (mas[size_count_x][j + 1] == '1') counter += 1;
    if (mas[i][size_count_y] == '1') counter += 1;
    if (mas[i + 1][size_count_y] == '1') counter += 1;
    return counter;
}

int right_upper_corner_counter(int** mas, int size_count_x, int i, int j) {
    int counter = 0;
    if (mas[i][j - 1] == '1') counter += 1;
    if (mas[i + 1][j - 1] == '1') counter += 1;
    if (mas[i + 1][j] == '1') counter += 1;
    if (mas[size_count_x][1] == '1') counter += 1;
    if (mas[1][1] == '1') counter += 1;
    if (mas[size_count_x][j] == '1') counter += 1;
    if (mas[i + 1][1] == '1') counter += 1;
    if (mas[size_count_x][j - 1] == '1') counter += 1;
    return counter;
}

int left_lower_corner_counter(int** mas, int size_count_y, int i, int j) {
    int counter = 0;
    if (mas[i - 1][j] == '1') counter += 1;
    if (mas[i - 1][j + 1] == '1') counter += 1;
    if (mas[i][j + 1] == '1') counter += 1;
    if (mas[1][1] == '1') counter += 1;
    if (mas[1][size_count_y] == '1') counter += 1;
    if (mas[i][size_count_y] == '1') counter += 1;
    if (mas[i - 1][size_count_y] == '1') counter += 1;
    if (mas[1][j + 1] == '1') counter += 1;
    return counter;
}

int right_lower_corner_counter(int** mas, int i, int j) {
    int counter = 0;
    if (mas[i - 1][j - 1] == '1') counter += 1;
    if (mas[i - 1][j] == '1') counter += 1;
    if (mas[i][j - 1] == '1') counter += 1;
    if (mas[1][1] == '1') counter += 1;
    if (mas[1][j] == '1') counter += 1;
    if (mas[i][1] == '1') counter += 1;
    if (mas[1][j - 1] == '1') counter += 1;
    if (mas[i - 1][1] == '1') counter += 1;
    return counter;
}

int left_side_counter(int** mas, int size_count_y, int i, int j) {
    int counter = 0;
    if (mas[i + 1][j] == '1') counter += 1;
    if (mas[i - 1][j] == '1') counter += 1;
    if (mas[i][j + 1] == '1') counter += 1;
    if (mas[i - 1][j + 1] == '1') counter += 1;
    if (mas[i + 1][j + 1] == '1') counter += 1;
    if (mas[i - 1][size_count_y] == '1') counter += 1;
    if (mas[i][size_count_y] == '1') counter += 1;
    if (mas[i + 1][size_count_y] == '1') counter += 1;
    return counter;
}

int right_side_counter(int** mas, int i, int j) {
    int counter = 0;
    if (mas[i + 1][j] == '1') counter += 1;
    if (mas[i - 1][j] == '1') counter += 1;
    if (mas[i][j - 1] == '1') counter += 1;
    if (mas[i - 1][j - 1] == '1') counter += 1;
    if (mas[i + 1][j - 1] == '1') counter += 1;
    if (mas[i][1] == '1') counter += 1;
    if (mas[i + 1][1] == '1') counter += 1;
    if (mas[i - 1][1] == '1') counter += 1;
    return counter;
}

int upper_side_counter(int** mas, int size_count_x, int i, int j) {
    int counter = 0;
    if (mas[i + 1][j + 1] == '1') counter += 1;
    if (mas[i][j + 1] == '1') counter += 1;
    if (mas[i + 1][j] == '1') counter += 1;
    if (mas[i + 1][j - 1] == '1') counter += 1;
    if (mas[i][j - 1] == '1') counter += 1;
    if (mas[size_count_x][j] == '1') counter += 1;
    if (mas[size_count_x][j - 1] == '1') counter += 1;
    if (mas[size_count_x][j + 1] == '1') counter += 1;
    return counter;
}

int lower_side_counter(int** mas, int i, int j) {
    int counter = 0;
    if (mas[i][j - 1] == '1') counter += 1;
    if (mas[i][j + 1] == '1') counter += 1;
    if (mas[i - 1][j + 1] == '1') counter += 1;
    if (mas[i - 1][j] == '1') counter += 1;
    if (mas[i - 1][j - 1] == '1') counter += 1;
    if (mas[1][j + 1] == '1') counter += 1;
    if (mas[1][j - 1] == '1') counter += 1;
    if (mas[1][j] == '1') counter += 1;
    return counter;
}

int another_counter(int** mas, int i, int j) {
    int counter = 0;
    if (mas[i + 1][j] == '1') counter += 1;
    if (mas[i][j + 1] == '1') counter += 1;
    if (mas[i + 1][j + 1] == '1') counter += 1;
    if (mas[i - 1][j - 1] == '1') counter += 1;
    if (mas[i - 1][j] == '1') counter += 1;
    if (mas[i - 1][j + 1] == '1') counter += 1;
    if (mas[i][j - 1] == '1') counter += 1;
    if (mas[i + 1][j - 1] == '1') counter += 1;
    return counter;
}
