#include <stdio.h>

#include "metodos.h"


//Q-2 Compare os três métodos para encontrar uma raiz...
//tabela que relaciona E's com sua respectiva função
double (*table[])(double) = {func2,  func3,   func4, func5};
char *funcNames[] = {"x^5 - 3x^4 - 3x^2 + 2",
                     "sqrt(x) - 5^-x",
                     "x^5 - x^4 - 4x + 1",
                     "0.05x^3 - 0.4x^2 +3*x*senx"};
double    E[] = {2.0e-5, 10.0e-3, 0.001, 0.005};

int main(int argc, char **argv){  
    RaizAux aux = {};
    aux.e = 0.005;
    aux.interAB.a = 0.30;
    aux.interAB.b = 3;
    Results resultados = {};
    
    for(int i = 0; i < 4; i++){
        RaizAux aux = {};
        aux.e = E[i];
        aux.interAB.a = 0.30;
        aux.interAB.b = 3;
        Results resultados = {};
        
        printf("f(x) = %s, com e = %lf\n", funcNames[i], aux.e);
        
        bisection(table[i], aux, &resultados);
        printf("------------------| bissection |------------------\n");
        printf("x: \t\t\t%.8lf\n", resultados.x0);
        printf("Iterações: \t\t%d\n", resultados.iterations);
        printf("Inter da Solução: \t(%.8lf %.8lf)\n", resultados.solutInterval.a, resultados.solutInterval.b);
        printf("Erro Absoluto: \t\t%.8lf\n", resultados.fx0);
        printf("--------------------------------------------------\n");

        posicao_falsa(table[i], aux, &resultados);
        printf("----------------| Posição Falsa |-----------------\n");
        printf("x: \t\t\t%.8lf\n", resultados.x0);
        printf("Iterações: \t\t%d\n", resultados.iterations);
        printf("Inter da Solução: \t(%.8lf %.8lf)\n", resultados.solutInterval.a, resultados.solutInterval.b);
        printf("Erro Absoluto: \t\t%.8lf\n", resultados.fx0);
        printf("--------------------------------------------------\n");

        pegaso(table[i], aux, &resultados);
        printf("--------------------| Pégaso |--------------------\n");
        printf("x: \t\t\t%.8lf\n", resultados.x0);
        printf("Iterações: \t\t%d\n", resultados.iterations);
        printf("Inter da Solução: \t(%.8lf %.8lf)\n", resultados.solutInterval.a, resultados.solutInterval.b);
        printf("Erro Absoluto: \t\t%.8lf\n", resultados.fx0);
        printf("--------------------------------------------------\n\n");
    }
    
    return 0;
}