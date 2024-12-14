#ifndef _AGBINARY_H
    #define _AGBINARY_H

    #include <stdbool.h>
    bool **createPop(int pop_size, int var_size);

    // Reproduction Crossover
    void singlePoint_crossover(bool *origin, bool *destiny);
    void twoPoint_crossover(bool *origin, bool *destiny);
    void fixedPoint_crossover(bool *origin, bool *destiny);

    void single_mutation(bool *crom);
    void multiple_mutation(bool *crom, int tax);

    void genocide(bool **pop, int bestindex);
#endif
