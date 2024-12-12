#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define LETRAS 4
#define TERMOS 10
#define ORS 2

#define TAM_VARIAVEL 1

int rRand(int min, int max){
    return rand() % (max - min) + min;
}

char* letras(){
    char* validas = (char *) malloc(sizeof(char) * LETRAS);

    for(int i = 0;i < LETRAS;i++){
        validas[i] = 'a' + i;
    }


    // bool usadas[127] = {0};

    // for(int i = 0;i < LETRAS;i++){
    //     char letra;
    //     do{
    //         letra = rRand(26) + 'a';
    //     }while(usadas[(int) letra]);

    //     validas[i] = letra;
    // }

    return validas;
}

char* seq(char *s_letras){
    char* termo = (char *) malloc(sizeof(char) * ORS * 2);

    int j = 0;

    int b;
    if(TAM_VARIAVEL) b = (1, ORS);
    else b = ORS;

    for(int i = 0;i < b;i++){
        if(rRand(0, 2)){
            termo[j] = '!';
            j++;
        }

        termo[j] = s_letras[rRand(0, LETRAS)];
        j++;
    }

    return termo;
}


int main() {
    srand(time(NULL));

    char* s_letras = letras();

    char aspas = '"';
    for(int i = 0;i < TERMOS;i++){
        printf("%c", aspas);
        printf("%s", seq(s_letras));
        printf("%c,", aspas);
    }
    // for (int i = 0; i < n; ++i) {
    //     char filename[50];
    //     sprintf(filename, "casos_teste/%d.in", i + 1);
        
    //     FILE *file = fopen(filename, "w");
    //     if (file == NULL) {
    //         perror("Failed to open file");
    //         return 1;
    //     }



    //     fprintf(file, "%d %d\n", LETRAS, TERMOS);
    //     for (int j = 0; j < TERMOS; ++j) {
    //         fprintf(file, "%d ", );
    //     }

    //     fclose(file);
    // }
}