#include <stdio.h>
#include <stdlib.h>

// 마법 정사각형을 생성하는 함수
void generate_magic_square(int n) {
    int row, col, num;
    int **magic_square;

    // 2차원 배열 동적 할당
    magic_square = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        magic_square[i] = (int *)malloc(n * sizeof(int));
    }

    // 배열 초기화
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            magic_square[row][col] = 0;
        }
    }

    // 첫 번째 숫자 위치
    row = 0;
    col = n / 2;

    // 마방진 채우기
    for (num = 1; num <= n * n; num++) {
        magic_square[row][col] = num;
        row--;
        col++;

        // 배열 경계 검사 및 조정
        if (row == -1 && col == n) {
            row = 1;
            col = n - 1;
        } else if (row == -1) {
            row = n - 1;
        } else if (col == n) {
            col = 0;
        } else if (magic_square[row][col] != 0) {
            row += 2;
            col--;
        }
    }

    // 마방진 출력
    printf("Magic Square of size %d:\n\n", n);
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            printf("%4d", magic_square[row][col]);
        }
        printf("\n");
    }

    // 동적 할당 해제
    for (int i = 0; i < n; i++) {
        free(magic_square[i]);
    }
    free(magic_square);
}

int main() {
    int n;
    printf("Enter the size of Magic Square (odd number): ");
    scanf("%d", &n);

    if (n % 2 == 0) {
        printf("Error: Size must be an odd number.\n");
        return 1;
    }

    generate_magic_square(n);

    return 0;
}
