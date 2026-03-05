// ==================================================================
// Desafio Batalha Naval - MateCheck
// Versão 1.1 - Nível aventureiro
// ==================================================================

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
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


void proxima_casa(const int direcao, int *x, int *y) {
    *x += direcoes[direcao][0];
    *y += direcoes[direcao][1];
}

bool verificar_validade_do_posicionamento(const Tabuleiro *matriz, const int linha, const int coluna, const intptr_t direcao, const size_t tamanho) {
    int x = linha, y = coluna;

    // Verifica casa por casa que será ocupada.
    for (size_t i = 0; i < tamanho; i++) {

        // Verifica se a casa ainda está dentro do tabuleiro.
        if (x >= TAMANHO_TABULEIRO || y >= TAMANHO_TABULEIRO) return false;
        if (x < 0 || y < 0) return false;

        // Verifica se a casa já está ocupada.
        if (matriz->casas[x][y]) return false;

        proxima_casa(direcao, &x, &y);
    }
    return true;
}

void limpar_tela() {
    printf("\033[H\033[J");
}



/* ========================== Funcionalidades ========================== */


void distribuir_navios(Tabuleiro *matriz) {

    int num_navios = sizeof(FROTA) / sizeof(FROTA[0]);

    // Itera sobre a frota, posicionando cada navio aleatoriamente na matriz do tabuleiro.
    for (int i = 0; i < num_navios; i++) {

        // Busca as propriedades do navio.
        EstadoCasa navio = FROTA[i].tipo;
        size_t tamanho = FROTA[i].tamanho;

        // Tenta aleatoriamente achar um posicionamento valido pro navio.
        int linha, coluna, direcao;
        do {
            linha = rand() % TAMANHO_TABULEIRO;
            coluna = rand() % TAMANHO_TABULEIRO;
            direcao = rand() % 8;
        } while (!verificar_validade_do_posicionamento(matriz, linha, coluna, direcao, tamanho));
        
        // Posiciona o navio
        int x = linha, y = coluna; 
        for (size_t j = 0; j < tamanho; j++) {
            matriz->casas[x][y] = navio;
            proxima_casa(direcao, &x, &y);
        }  
    }
}

void imprimir_tabuleiro(const Tabuleiro *matriz) {
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            if (matriz->casas[linha][coluna]) {
                printf(" %i ", matriz->casas[linha][coluna]);
            } else {
                printf("%s ~ %s", BG_AZUL, RESET);
            }
        }
        puts("");
    }
}



/* ========================== Função principal ========================== */


int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(NULL));

    Tabuleiro matriz = {AGUA}; // Inicialização do tabuleiro.

    distribuir_navios(&matriz);

    limpar_tela();
    imprimir_tabuleiro(&matriz);

    return 0;
}