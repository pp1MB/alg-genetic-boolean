#include <stdio.h>
#include <stdlib.h>
#include "agbinary.h"

int var_global_size = 0;

bool **createPop(int pop_size, int var_size){
    bool **pop = (bool **) malloc(sizeof(bool *) * pop_size);
    if(pop == NULL)
        return NULL;

    for(int i = 0; i < pop_size; i++){
        pop[i] = (bool *) malloc(sizeof(bool) * var_size);

        // Tratamento para caso algum dos cromossomos não seja inicializado.
        if(pop[i] == NULL){
            for(int j = i-1; j >= 0; j--){
                free(pop[j]);
                pop[j] = NULL;
            }

            free(pop);
            pop = NULL;

            return NULL;
        }

        for(int j = 0; j < var_size; j++)
            pop[i][j] = rand() % 2;
    }

    var_global_size = var_size;
    return pop;
}

// Crossover
void singlePoint_crossover(bool *origin, bool *destiny){
    for(int i = rand() % var_global_size; i < var_global_size; i++){
        destiny[i] = origin[i];
    }

    return;
}

void twoPoint_crossover(bool *origin, bool *destiny){
    for(int i = rand() % var_global_size; i < rand() % var_global_size; i++){
        destiny[i] = origin[i];
    }

    return;
}

// Uniform
// Greedy

// Mutation
void single_mutation(bool *crom){
    crom[rand() % var_global_size] = !crom[rand() % var_global_size];

    return;
}

void multiple_mutation(bool *crom, int tax){
    for(int i = 0; i < var_global_size; i++){
        if(rand() % 100 <= tax)
            crom[rand() % var_global_size] = !crom[rand() % var_global_size];
    }
}