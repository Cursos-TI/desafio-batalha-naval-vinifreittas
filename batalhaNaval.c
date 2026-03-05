// ==================================================================
// Desafio Batalha Naval - MateCheck
// Versão 1.0 - nível novato
// ==================================================================

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

// Codificação para o tipo de navio.
typedef enum {
    tipo_null = 0,
    tipo_navio,
    tipo_submarino,
    tipo_cruzador,
    tipo_porta_avioes
} tipoNavio;

// Codificação para a direção do navio.
typedef enum{
    cima = 0,
    baixo,
    esquerda,
    direita
} tipoDirecao;

// Estrutura do tabuleiro (uma matriz 10x10).
typedef struct {
    int casas[10][10];
} Tabuleiro;

// Base para construção do vetor de cada navio.
tipoNavio listaNavios[] = { tipo_navio, tipo_submarino, tipo_cruzador, tipo_porta_avioes, tipo_null};
int listaTamanho[] = { 1, 2, 3, 4 };



/* ========================== Utilitários ========================== */


int verificar_validade_do_posicionamento(const Tabuleiro *matriz, int linha, int coluna, tipoDirecao direcao, int tamanho) {
    int resultado = 1;

    // Verifica casa por casa que será ocupada.
    for (int i = 0; i < tamanho; i++) {

        // Verifica se a casa ainda está dentro do tabuleiro.
        if (linha > 9 || coluna > 9) { resultado = 0; break; }
        if (linha < 0 || coluna < 0) { resultado = 0; break; }

        // Verifica se a casa já está ocupada.
        if (matriz->casas[linha][coluna]) { resultado = 0; break; }

        // Modifica a posição de acordo com a direção.
        switch (direcao) {
            case cima: 
                linha--; break;
            case baixo: 
                linha++; break;
            case esquerda:
                coluna--; break;
            case direita: 
                coluna++; break;
        }
    }

    return resultado;
}



/* ========================== Funcionalidades ========================== */


void distribuir_navios(Tabuleiro *matriz) {

    // Itera sobre listaNavios e listaTamanho, posicionando cada navio aleatoriamente na matriz do tabuleiro.
    for (int i = 0, rodando = 1; rodando; i++) {

        // Busca as propriedades do navio.
        tipoNavio navio = listaNavios[i];
        if (navio == tipo_null) { rodando = 0; continue;} // Finaliza quando não tiver navio.
        int tamanho = listaTamanho[i];

        // Tenta aleatoriamente achar um posicionamento valido pro navio.
        int linha, coluna;
        tipoDirecao direcao;
        do {
            linha = rand() % 10;
            coluna = rand() % 10;
            direcao = rand() % 4;
        } while (!verificar_validade_do_posicionamento(matriz, linha, coluna, direcao, tamanho));
        
        // Posiciona o navio
        int x = linha, y = coluna; 
        for (int j = 0; j < tamanho; j++) {
            matriz->casas[x][y] = navio;

            // Modifica a posição de acordo com a direção.
            switch (direcao) {
                case cima: 
                    x--; break;
                case baixo: 
                    x++; break;
                case esquerda:
                    y--; break;
                case direita: 
                    y++; break;
            }
        }  
    }
}

void imprimir_tabuleiro(Tabuleiro *matriz) {
    for (int linha = 0; linha < 10; linha++) {
        for (int coluna = 0; coluna < 10; coluna++) {
            printf("  %i  ", matriz->casas[linha][coluna]);
        }
        puts("");
    }
}



/* ========================== Função principal ========================== */


int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(NULL));

    // Inicializção da matriz do tabuleiro.
    Tabuleiro matriz = {0};

    distribuir_navios(&matriz);

    imprimir_tabuleiro(&matriz);

    return 0;
}
