
#include <stdio.h>

#define MAX 100

typedef struct {
    int row;
    int col;
    int value;
} term;

void display(term a[]) {
    int i;

    printf("Row\tColumn\tValue\n");

    for (i = 0; i <= a[0].value; i++) {
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
    }
}

void fast_transpose(term a[], term b[]) {
    int row_terms[MAX] = {0};
    int starting_pos[MAX] = {0};
    int i, j, num_cols;

    num_cols = a[0].col;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;

    for (i = 1; i <= a[0].value; i++) {
        row_terms[a[i].col]++;
    }

    printf("\nrow_terms[]:\n");

    for (i = 0; i < num_cols; i++) {
        printf("%d ", row_terms[i]);
    }

    printf("\n");

    starting_pos[0] = 1;

    for (i = 1; i < num_cols; i++) {
        starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
    }

    printf("\nstarting_pos[]:\n");

    for (i = 0; i < num_cols; i++) {
        printf("%d ", starting_pos[i]);
    }

    printf("\n");

    for (i = 1; i <= a[0].value; i++) {
        j = starting_pos[a[i].col]++;

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;
    }
}

int main() {
    int matrix[MAX][MAX];
    int rows, cols, i, j, count = 0;
    term a[MAX], b[MAX];

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    if (rows <= 0 || cols <= 0 ||
        rows >= MAX || cols >= MAX ||
        rows * cols >= MAX) {
        printf("Invalid matrix dimensions.\n");
        return 1;
    }

    printf("Enter matrix elements row by row:\n");

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);

            if (matrix[i][j] != 0) {
                count++;
            }
        }
    }

    a[0].row = rows;
    a[0].col = cols;
    a[0].value = count;

    count = 1;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                a[count].row = i;
                a[count].col = j;
                a[count].value = matrix[i][j];
                count++;
            }
        }
    }

    printf("\nOriginal matrix triples:\n");
    display(a);

    fast_transpose(a, b);

    printf("\nTransposed matrix triples:\n");
    display(b);

    printf("\nThe transposed triples are in row-major order.\n");

    return 0;
}

