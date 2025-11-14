#include <stdio.h>
#include <stdbool.h>

#define N 10
#define SHIP_SIZE 3
#define WATER 0
#define SHIP 3
#define EFFECT 5

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

/* Habilidades */
#define SKILL_SIZE 5
void construir_cone(int skill[SKILL_SIZE][SKILL_SIZE]);
void construir_cruz(int skill[SKILL_SIZE][SKILL_SIZE]);
void construir_octaedro(int skill[SKILL_SIZE][SKILL_SIZE]);
void aplicar_habilidade(int board[N][N], int skill[SKILL_SIZE][SKILL_SIZE], int origin_row, int origin_col);

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

    int cone_skill[SKILL_SIZE][SKILL_SIZE];
    int cruz_skill[SKILL_SIZE][SKILL_SIZE];
    int octa_skill[SKILL_SIZE][SKILL_SIZE];

    int cone_origin_row = 4;
    int cone_origin_col = 2;

    int cruz_origin_row = 7;
    int cruz_origin_col = 7;

    int octa_origin_row = 2;
    int octa_origin_col = 5;

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

    construir_cone(cone_skill);
    construir_cruz(cruz_skill);
    construir_octaedro(octa_skill);

    aplicar_habilidade(board, cone_skill, cone_origin_row, cone_origin_col);
    aplicar_habilidade(board, cruz_skill, cruz_origin_row, cruz_origin_col);
    aplicar_habilidade(board, octa_skill, octa_origin_row, octa_origin_col);

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

void construir_cone(int skill[SKILL_SIZE][SKILL_SIZE]) {
    int center_col = SKILL_SIZE / 2;
    for (int r = 0; r < SKILL_SIZE; ++r) {
        for (int c = 0; c < SKILL_SIZE; ++c) {
            skill[r][c] = 0;
        }
    }
    int height = 3;
    for (int r = 0; r < height; ++r) {
        int left = center_col - r;
        int right = center_col + r;
        for (int c = left; c <= right; ++c) {
            if (c >= 0 && c < SKILL_SIZE) skill[r][c] = 1;
        }
    }
}

void construir_cruz(int skill[SKILL_SIZE][SKILL_SIZE]) {
    int center = SKILL_SIZE / 2;
    for (int r = 0; r < SKILL_SIZE; ++r) {
        for (int c = 0; c < SKILL_SIZE; ++c) {
            if (r == center || c == center) skill[r][c] = 1;
            else skill[r][c] = 0;
        }
    }
}

void construir_octaedro(int skill[SKILL_SIZE][SKILL_SIZE]) {
    int center = SKILL_SIZE / 2;
    for (int r = 0; r < SKILL_SIZE; ++r) {
        for (int c = 0; c < SKILL_SIZE; ++c) {
            int manhattan = (r > center ? r - center : center - r) + (c > center ? c - center : center - c);
            if (manhattan <= 2) skill[r][c] = 1;
            else skill[r][c] = 0;
        }
    }
}

void aplicar_habilidade(int board[N][N], int skill[SKILL_SIZE][SKILL_SIZE], int origin_row, int origin_col) {
    int center = SKILL_SIZE / 2;
    for (int r = 0; r < SKILL_SIZE; ++r) {
        for (int c = 0; c < SKILL_SIZE; ++c) {
            if (skill[r][c] == 1) {
                int target_row = origin_row + (r - center);
                int target_col = origin_col + (c - center);
                if (target_row >= 0 && target_row < N && target_col >= 0 && target_col < N) {
                    board[target_row][target_col] = EFFECT;
                }
            }
        }
    }
}

void imprimir_tabuleiro(int board[N][N]) {
    printf("Tabuleiro (0 = agua, 3 = navio, 5 = area de habilidade):\n\n");
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
