#define POP_MAX 2 // Indivíduos na população
#define GEN_MAX 200 // Limite de gerações
#define TERM_MAX 2 // Máximo de termos em uma única cláusula
#define NUM_VAR 7 // Número de variáveis
#define NUM_CLS 7 // Número de cláusulas na equação

// Vetor de chars denota todas as cláusulas.
char *operacoes_t[] = {
    "x1 0 x2 0",
    "x1 0 x2 1",
    "x1 1 x2 0",
    "x3 1 x2 0",
    "x4 1 x5 0",
    "x6 1 x7 1",
    "x5 1 x7 2"
};