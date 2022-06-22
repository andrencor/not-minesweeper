#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>

int grid[15][15];
int x, y;
int spawn;

// Inicializa um novo jogo
void init_game() {
    // Seleciona a dificuldade
    int dif;
    while (true) {
        printf("v==============================================================<\n");
        printf("|                    Escolha a dificuldade                      \n");
        printf("|                                                               \n");
        printf("|     1 - Fácil (5%%)   2 - Médio (15%%)   3 - Difícil (25%%)   \n");
        printf("|==============================================================+\n");
        printf("|                                                               \n");
        printf("V                                                               \n");
        scanf_s("%d", &dif);
        printf("\n");
        switch (dif) {
            case 1:
                dif = 5;
                break;
            case 2:
                dif = 15;
                break;
            case 3:
                dif = 25;
                break;
            default:
                continue;
        }
        break;
    }

    // Coloca as bombas
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (rand() % 100 + 1 <= dif) grid[i][j] = 1;
            else grid[i][j] = 0;
        }
    }

    // Escolhe um spawn
    switch (spawn = rand() % 4) {
        case 0:
            x = 0;
            y = rand() % 13 + 1;
            break;
        case 1:
            x = 14;
            y = rand() % 13 + 1;
            break;
        case 2:
            x = rand() % 13 + 1;
            y = 0;
            break;
        case 3:
            x = rand() % 13 + 1;
            y = 14;
            break;
    }
    // Tira bomba do spawn
    grid[x][y] = 0;
}

// Imprime a matriz
void print_grid(int x, int y) {
    printf("     1   2   3   4   5   6   7   8   9  10  11  12  13  14  15\n");
    for (int i = 0; i < 15; i++) {
        printf("   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+");
        printf("\n");
        if (i < 9) printf("%d  ", i + 1);
        else printf("%d ", i + 1);

        for (int j = 0; j < 15; j++) {
            printf("|");
            if (i == x && j == y) printf(" X ");
            else printf("   ");
        }
        printf("|");
        printf("\n");
    }
    printf("   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
}

// Movimentação
void move() {
    int mov;
    while (true) {
        printf("v==============================================================<\n");
        printf("|                     Faça seu movimento                        \n");
        printf("|                                                               \n");
        printf("|      1 - Cima   2 - Baixo   3 - Esquerda   4 - Direita        \n");
        printf("|==============================================================+\n");
        printf("|                                                               \n");
        printf("V                                                               \n");
        scanf_s("%d", &mov);
        printf("\n");
        switch (mov) {
            case 1:
                if (x > 0) x--;
                break;
            case 2:
                if (x < 14) x++;
                break;
            case 3:
                if (y > 0) y--;
                break;
            case 4:
                if (y < 14) y++;
                break;
            default:
                continue;
            }
        break;
    }
}

// Tela de vitória
void win_screen() {
    printf("v==============================================================<\n");
    printf("|                                                               \n");
    printf("|                          ___________                          \n");
    printf("|                         '._==_==_=_.'                         \n");
    printf("|                         .-\\:      /-.                        \n");
    printf("|                        | (|:.     |) |                        \n");
    printf("|                         '-|:.     |-'                         \n");
    printf("|                           \\::.    /                          \n");
    printf("|                            '::. .'                            \n");
    printf("|                              ) (                              \n");
    printf("|                            _.' '._                            \n");
    printf("|                            '''''''                            \n");
    printf("|==============================================================+\n");
    printf("|                                                               \n");
    printf("|                    Parabéns, você ganhou!                     \n");
    printf("|                                                               \n");
    printf("|==============================================================+\n");
}

// Tela de derrota
void lose_screen() {
    printf("v==============================================================<\n");
    printf("|                                                               \n");
    printf("|                                ____                           \n");
    printf("|                        __,-~~/~    `---.                      \n");
    printf("|                      _/_,---(      ,    )                     \n");
    printf("|                __ /        <    /   )  /___                   \n");
    printf("|       - --===;;;'====------------------===;;;===- -- -        \n");
    printf("|                     /  ~'~'~'~'~'~/~'~)~'/                    \n");
    printf("|                     (_ (   /  (     >    /)                   \n");
    printf("|                      (_( _ <         >_>'                     \n");
    printf("|                         ~ `-i' ::>|--'                        \n");
    printf("|                             I;|.|.|                           \n");
    printf("|                            <|i::|i|`.                         \n");
    printf("|                           (` ^''`-' ')                        \n");
    printf("|==============================================================+\n");
    printf("|                                                               \n");
    printf("|                     BOOOOOOOOOOOOOOOM!!!!!                    \n");
    printf("|                                                               \n");
    printf("|==============================================================+\n");
}

// Testa a vitória
bool win_check() {
    switch (spawn) {
        case 0:
            if (x == 14) {
                win_screen();
                return true;
            }
            break;
        case 1:
            if (x == 0) {
                win_screen();
                return true;
            }
            break;
        case 2:
            if (y == 14) {
                win_screen();
                return true;
            }
            break;
        case 3:
            if (y == 0) {
                win_screen();
                return true;
            }
            break;
    }
    return false;
}

// Testa a derrota
bool lose_check() {
    if (grid[x][y] == 1) {
        lose_screen();
        return true;
    }
    return false;
}

// Main
int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    while (true) {
        init_game();
        print_grid(x, y);
        while (true) {
            move();
            print_grid(x, y);
            if (lose_check()) break;
            if (win_check()) break;
        }
    }
    return 0;
}
