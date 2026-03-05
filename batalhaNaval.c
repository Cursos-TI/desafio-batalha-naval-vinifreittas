// ==================================================================
// Desafio Batalha Naval - MateCheck
// Versão 1.1 - Nível aventureiro
// ==================================================================

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>

// Constantes
#define TAMANHO_TABULEIRO 10

// Estilos de texto (ANSI)
#define BG_AZUL "\033[44m"
#define RESET "\033[0m"

// Codificação para o estado de cada do tabuleiro.
typedef enum {
    AGUA = 0,
    NAVIO,
    SUBMARINO,
    CRUZADOR,
    PORTA_AVIOES
} EstadoCasa;

// Estrutura do tabuleiro (uma matriz quadrada).
typedef struct {
    EstadoCasa casas[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
} Tabuleiro;

// Estrutura de um navio (base para um vetor).
typedef struct {
    EstadoCasa tipo;
    size_t tamanho;
} Navio;

// Definição da lista de navios.
const Navio FROTA[] = { 
    {NAVIO, 1}, 
    {SUBMARINO, 2}, 
    {CRUZADOR, 3}, 
    {PORTA_AVIOES, 4}
};

// Vetores de deslocamento para cada direção.
const int direcoes[8][2] = {
    {-1, 0},  // NORTE
    {+1, 0},  // SUL
    {0, -1},  // LESTE
    {0, +1},  // OESTE
    {-1, -1}, // NORDESTE
    {-1, +1}, // NOROESTE
    {+1, -1}, // SUDESTE
    {+1, +1}  // SUDOESTE
};



/* ========================== Utilitários ========================== */

void limpar_tela(void) {
    printf("\033[H\033[J");
}


/* ========================== Funcionalidades ========================== */

// Função recursiva pra posicionar o navio apenas se sua posição for inteiramente válida.
bool posicionar_navio(Tabuleiro *matriz, const Navio navio, const int x, const int y, const int direcao) {
    if (navio.tamanho == 0) return true;

    // Validação da posição
    if ((x < 0 || x >= TAMANHO_TABULEIRO) || (y < 0 || y >= TAMANHO_TABULEIRO)) return false;
    if (matriz->casas[x][y] != AGUA) return false;
    
    // Verifica o restante do navio a partir da proxima posição.
    int proximo_x = x + direcoes[direcao][0];
    int proximo_y = y + direcoes[direcao][1];
    Navio restante = { navio.tipo, navio.tamanho - 1 };

    if (!posicionar_navio(matriz, restante, proximo_x, proximo_y, direcao)) return false;

    // Marca posição atual
    matriz->casas[x][y] = navio.tipo;
    return true;
}

// Itera sobre a frota, posicionando cada navio aleatoriamente na matriz do tabuleiro.
void distribuir_navios(Tabuleiro *matriz) {
    int num_navios = sizeof(FROTA) / sizeof(FROTA[0]);

    for (int i = 0; i < num_navios; i++) {
        Navio navio = FROTA[i];

        int linha, coluna, direcao;
        do {
            linha = rand() % TAMANHO_TABULEIRO;
            coluna = rand() % TAMANHO_TABULEIRO;
            direcao = rand() % 8;
        } while (!posicionar_navio(matriz, navio, linha, coluna, direcao));
    }
}

void imprimir_tabuleiro(const Tabuleiro *matriz) {
    printf("   ");
    for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) printf(" %i ", coluna);
    puts("");   
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        printf(" %i ", linha);
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            matriz->casas[linha][coluna] ? printf(" %i ", matriz->casas[linha][coluna]) : printf("%s ~ %s", BG_AZUL, RESET); 
        }
        puts("");
    }
}


/* ========================== Função principal ========================== */

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(NULL));

    Tabuleiro matriz = {AGUA}; 
    distribuir_navios(&matriz);

    limpar_tela();
    imprimir_tabuleiro(&matriz);
    return 0;
}