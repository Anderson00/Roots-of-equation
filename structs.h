#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdbool.h>

#define POSITIVE(x) ((x >= 0)? true : false) 
#define NEGATIVE(x) ((x < 0)? true : false)

//structs
//intervalo [a, b]
typedef struct{
    double a, b;
}Interval;

typedef struct{
    double e;
    Interval interAB;
} RaizAux;

typedef struct{
    double x0;
    double fx0; //f(x0) = Erro Absoluto
    Interval solutInterval; // Intervalo da solução
    int iterations;
}Results;
//end


#endif