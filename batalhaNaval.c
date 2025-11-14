#include <stdio.h>
#include <stdbool.h>

#define N 10
#define SHIP_SIZE 3
#define WATER 0
#define SHIP 3

void inicializar_tabuleiro(int board[N][N]);
bool pode_posicionar_horizontal(int board[N][N], int row, int col_start);
bool pode_posicionar_vertical(int board[N][N], int row_start, int col);
bool pode_posicionar_diagonal_inc(int board[N][N], int row_start, int col_start);
bool pode_posicionar_diagonal_dec(int board[N][N], int row_start, int col_start);
void posicionar_horizontal(int board[N][N], int row, int col_start);
void posicionar_vertical(int board[N][N], int row_start, int col);
void posicionar_diagonal_inc(int board[N][N], int row_start, int col_start);
void posicionar_diagonal_dec(int board[N][N], int row_start, int col_start);
void imprimir_tabuleiro(int board[N][N]);

int main(void) {
    int board[N][N];

    int h_row = 2;
    int h_col_start = 4;

    int v_row_start = 5;
    int v_col = 7;

    int d1_row_start = 0;
    int d1_col_start = 0;

    int d2_row_start = 1;
    int d2_col_start = 9;

    inicializar_tabuleiro(board);

    if (!pode_posicionar_horizontal(board, h_row, h_col_start)) {
        printf("Erro: nao eh possivel posicionar o navio horizontal nas coordenadas (%d,%d).\n",
               h_row, h_col_start);
        return 1;
    }
    posicionar_horizontal(board, h_row, h_col_start);

    if (!pode_posicionar_vertical(board, v_row_start, v_col)) {
        printf("Erro: nao eh possivel posicionar o navio vertical nas coordenadas (%d,%d).\n",
               v_row_start, v_col);
        return 1;
    }
    posicionar_vertical(board, v_row_start, v_col);

    if (!pode_posicionar_diagonal_inc(board, d1_row_start, d1_col_start)) {
        printf("Erro: nao eh possivel posicionar o navio diagonal crescente nas coordenadas (%d,%d).\n",
               d1_row_start, d1_col_start);
        return 1;
    }
    posicionar_diagonal_inc(board, d1_row_start, d1_col_start);

    if (!pode_posicionar_diagonal_dec(board, d2_row_start, d2_col_start)) {
        printf("Erro: nao eh possivel posicionar o navio diagonal decrescente nas coordenadas (%d,%d).\n",
               d2_row_start, d2_col_start);
        return 1;
    }
    posicionar_diagonal_dec(board, d2_row_start, d2_col_start);

    imprimir_tabuleiro(board);

    return 0;
}

void inicializar_tabuleiro(int board[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = WATER;
        }
    }
}

bool pode_posicionar_horizontal(int board[N][N], int row, int col_start) {
    if (row < 0 || row >= N) return false;
    if (col_start < 0 || col_start + SHIP_SIZE - 1 >= N) return false;
    for (int c = col_start; c < col_start + SHIP_SIZE; ++c) {
        if (board[row][c] != WATER) return false;
    }
    return true;
}

bool pode_posicionar_vertical(int board[N][N], int row_start, int col) {
    if (col < 0 || col >= N) return false;
    if (row_start < 0 || row_start + SHIP_SIZE - 1 >= N) return false;
    for (int r = row_start; r < row_start + SHIP_SIZE; ++r) {
        if (board[r][col] != WATER) return false;
    }
    return true;
}

bool pode_posicionar_diagonal_inc(int board[N][N], int row_start, int col_start) {
    if (row_start < 0 || col_start < 0) return false;
    if (row_start + SHIP_SIZE - 1 >= N) return false;
    if (col_start + SHIP_SIZE - 1 >= N) return false;
    for (int i = 0; i < SHIP_SIZE; ++i) {
        if (board[row_start + i][col_start + i] != WATER) return false;
    }
    return true;
}

bool pode_posicionar_diagonal_dec(int board[N][N], int row_start, int col_start) {
    if (row_start < 0 || col_start >= N) return false;
    if (row_start + SHIP_SIZE - 1 >= N) return false;
    if (col_start - (SHIP_SIZE - 1) < 0) return false;
    for (int i = 0; i < SHIP_SIZE; ++i) {
        if (board[row_start + i][col_start - i] != WATER) return false;
    }
    return true;
}

void posicionar_horizontal(int board[N][N], int row, int col_start) {
    for (int c = col_start; c < col_start + SHIP_SIZE; ++c) {
        board[row][c] = SHIP;
    }
}

void posicionar_vertical(int board[N][N], int row_start, int col) {
    for (int r = row_start; r < row_start + SHIP_SIZE; ++r) {
        board[r][col] = SHIP;
    }
}

void posicionar_diagonal_inc(int board[N][N], int row_start, int col_start) {
    for (int i = 0; i < SHIP_SIZE; ++i) {
        board[row_start + i][col_start + i] = SHIP;
    }
}

void posicionar_diagonal_dec(int board[N][N], int row_start, int col_start) {
    for (int i = 0; i < SHIP_SIZE; ++i) {
        board[row_start + i][col_start - i] = SHIP;
    }
}

void imprimir_tabuleiro(int board[N][N]) {
    printf("Tabuleiro (0 = agua, 3 = navio):\n\n");
    printf("   ");
    for (int c = 0; c < N; ++c) {
        printf("%2d ", c);
    }
    printf("\n");
    printf("   ");
    for (int c = 0; c < N; ++c) printf("---");
    printf("\n");
    for (int r = 0; r < N; ++r) {
        printf("%2d |", r);
        for (int c = 0; c < N; ++c) {
            printf("%2d ", board[r][c]);
        }
        printf("\n");
    }
}
