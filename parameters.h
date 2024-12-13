#define POP_MAX 2 // Indivíduos na população
#define GEN_MAX 200 // Limite de gerações
#define TERM_MAX 3 // Máximo de termos em uma única cláusula
#define NUM_VAR 10 // Número de variáveis
#define NUM_CLS 10 // Número de cláusulas na equação

// Vetor de chars denota todas as cláusulas.
char *operacoes_t[] = {
    "x6 1 x3 0 x10 0 ",
    "x7 1 x6 1 x1 0 ",
    "x2 0 x8 0 x2 1 ",
    "x7 1 x2 1 x1 0 ",
    "x7 0 x2 1 x7 0 ",
    "x2 1 x4 1 x9 0 ",
    "x10 0 x7 0 x5 0 ",
    "x5 0 x6 1 x2 1 ",
    "x8 0 x2 1 x6 0 ",
    "x7 1 x7 1 x10 1 "
};