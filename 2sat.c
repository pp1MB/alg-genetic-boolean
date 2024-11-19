#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "agbinary.h"

#define POP_MAX 10 // Indivíduos na população
#define GEN_MAX 100 // Limite de gerações
#define TERM_MAX 100 // Máximo de termos em uma única clausula.
#define NUM_VAR 2 // Número de variáveis
#define NUM_CLS 4 // Número de clausulas na equação 

// "ab", "!ab", "a!b", "!a!b" INCOERÊNCIA 1 = Se existe a tabela verdade toda de dois booleanos, nunca acontece
// "ac", "bc", "a!c", "b!c", "!a!b" INCOERÊNCIA 2 = A e B precisam ser 1 obrigatoriamente, C se alterna e os obriga a serem
// "ab", "bc", "ac", "!a!b", "!b!c", "!a!c" INCOERÊNCIA 3 = Se são completamente opostos
// 
// Vetor de chars denota todas as cláusulas.
char *operacoes_t[] = {
  "ab", "!ab", "a!b", "!a!b"
};

// Função para testar a função dentro de cada cláusula.
bool funcao_cls(bool *b, int n){
    bool res = 0;
    for(int i = 0; i < n; i++){
        res = res || b[i];
    }
    return res;
}

bool fitnessPop(bool **pop);
int calcularFunc(bool *vet);

int main(void){
    srand(time(NULL)); // Declara a seed

    bool **pop = createPop(POP_MAX, NUM_VAR); // Gera a população

    for(int i = 0; i < 100000; i++){
        printf("%d° Geração\n", i+1); // Printa as gerações

        if(fitnessPop(pop)) // Caso a solução seja encontrada, encerra o programa.
            break;
    }

    return 0;
}

bool fitnessPop(bool **pop){
    int fit[POP_MAX];
    int bestfit = 0;
    int bestindex = 0;

    printf("Fit: ");
    for(int i = 0; i < POP_MAX; i++){
        fit[i] = calcularFunc(pop[i]);
        printf("%d ", fit[i]);

        if(fit[i] == NUM_CLS){
            printf("Achou!\n");
            for(int j = 0; j < NUM_VAR; j++)
                printf("%c = %d\n", 'a' + j, pop[i][j]);
            return true;
        }

        if(fit[i] > bestfit){
            bestfit = fit[i];
            bestindex = i;
        }
    }

    printf("\nMelhor indivíduo: %d\n", bestindex + 1);

    // elitismo
    for(int i = 0; i < POP_MAX; i++){
        if(i == bestindex)
            continue;

        singlePoint_crossover(pop[bestindex], pop[i]);
        multiple_mutation(pop[i], 5);
    }
    //

    return false;
}

int calcularFunc(bool *vet){
    int fit = 0, k = 0;
    bool b[TERM_MAX] = {false};

    for(int i = 0; i < NUM_CLS; i++){
        for(int j = 0; operacoes_t[i][j] != '\0'; j++)
            if(operacoes_t[i][j] >= 'a' && operacoes_t[i][j] <= 'z'){
                if(j-1 >= 0 && operacoes_t[i][j-1] == '!')
                    b[k] = !vet[operacoes_t[i][j] - 'a'];
                else
                    b[k] = vet[operacoes_t[i][j] - 'a'];

                k++;
            }
            if(funcao_cls(b, k)){
                fit++;
                k = 0;
            }
    }

    return fit;
}

