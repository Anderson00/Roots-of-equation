#include <stdio.h>

#include "metodos.h"


//Q-2 Compare os três métodos para encontrar uma raiz...
//tabela que relaciona E's com sua respectiva função
double (*table[])(double) = {func2,  func3,   func4, func5};
char *funcNames[] = {"x^5 - 3x^4 - 3x^2 + 2",
                     "sqrt(x) - 5^-x",
                     "x^5 - x^4 - 4x + 1",
                     "0.05x^3 - 0.4x^2 +3*x*senx"};
double E[] = {2.0e-5, 10.0e-3, 0.001, 0.005};

//All fun
void printFunctions(void);//Printa todos os calculos de todos os metodos e funcões
void printFunctionsInCSV(void);//Printa no padrão CSV
void GenerateCSV(const char *filename);//redireciona o stdout para o arquivo *filename
//End

int main(int argc, char **argv){  
    //GenerateCSV("Resultados.csv");
    //printFunctionsInCSV();
    //printFunctions();

    RaizAux aux = {};
    aux.e = 0.001;
    aux.interAB.a = -1.0;
    aux.interAB.b = -2.44;
    Results resultados = {};

    newtonRhapson(func0, func0Dx, aux, &resultados);
    printf("------------------| Newton Raphson |------------------\n");
    printf("x: \t\t\t%.8lf\n", resultados.x0);
    printf("Iterações: \t\t%d\n", resultados.iterations);
    printf("Inter da Solução: \t(%.8lf %.8lf)\n", resultados.solutInterval.a, resultados.solutInterval.b);
    printf("Erro Absoluto: \t\t%.8lf\n", resultados.fx0);
    printf("--------------------------------------------------\n");
    

    return 0;
}

void GenerateCSV(const char *filename){
    freopen(filename, "w", stdout);
}

void printFunctionsInCSV(void){
    RaizAux aux = {};
    aux.e = 0.005;
    aux.interAB.a = 0.30;
    aux.interAB.b = 3;
    Results resultados = {};
    
    for(int i = 0; i < 4; i++){
        RaizAux aux = {};
        aux.e = E[i];//Precisão e
        aux.interAB.a = 0.30;//[A,
        aux.interAB.b = 3;//    B]
        Results resultados = {};
        Results resultados2 = {};
        Results resultados3 = {};

        printf(",\n");

        printf("f(x) = %s, com e = %lf\n\n", funcNames[i], aux.e);
        
        bisection(table[i], aux, &resultados);
        posicao_falsa(table[i], aux, &resultados2);
        pegaso(table[i], aux, &resultados3);
        printf(",\n");
        printf(",Bisection,Posição Falsa,Pégaso\n");
        printf("x,%.8lf,%.8lf,%.8lf\n", resultados.x0, resultados2.x0, resultados3.x0);
        printf("Iterações,%d,%d,%d\n", resultados.iterations, resultados2.iterations, resultados3.iterations);
        printf("Interv da Solução,\"(%.8lf, %.8lf)\",\"(%.8lf, %.8lf)\",\"(%.8lf, %.8lf)\"\n", 
            resultados.solutInterval.a, resultados.solutInterval.b,
            resultados2.solutInterval.a, resultados2.solutInterval.b,
            resultados3.solutInterval.a, resultados3.solutInterval.b);
        printf("Erro Absoluto,%.8lf,%.8lf,%.8lf\n\n", resultados.fx0, resultados2.fx0, resultados3.fx0);
    }
}

void printFunctions(void){
    RaizAux aux = {};
    aux.e = 0.005;
    aux.interAB.a = 0.30;
    aux.interAB.b = 3;
    Results resultados = {};
    
    for(int i = 0; i < 4; i++){
        RaizAux aux = {};
        aux.e = E[i];//Precisão e
        aux.interAB.a = 0.30;//[A,
        aux.interAB.b = 3;//    B]
        Results resultados = {};
        
        printf("f(x) = %s, com e = %lf\n", funcNames[i], aux.e);
        
        bisection(table[i], aux, &resultados);
        printf("------------------| Bisection |------------------\n");
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
}