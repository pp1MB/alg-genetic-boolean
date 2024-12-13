#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define VARIAVEIS 10
#define ANDS 10
#define ORS 3


int rRand(int min, int max){
    return rand() % (max - min) + min;
}


int main(int argc, char *argv[]) {

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Deve ser um número positivo.\n");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < n; ++i) {
        char filename[50];
        sprintf(filename, "entradas/%d.in", i + 1);
        
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Failed to open file");
            return 1;
        }


        for (int j = 0; j < ANDS; j++) {
            for(int k = 0; k < ORS; k++){
                fprintf(file, "x%d %d ", rRand(1, VARIAVEIS + 1), rRand(0, 2));
            }
            fprintf(file, "\n");
        }

        fprintf(file, "\n");
        fclose(file);
    }

    return 0;
}