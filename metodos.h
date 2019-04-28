#ifndef METODOS_H
#define METODOS_H
#include <math.h>
#include <stdlib.h>

#include "structs.h"
#include "functions.h"

#define BISSEC(x,y) ((x + y)/2)
#define POS_FALSE(x,y,fun) ((x*fun(y) - y*fun(x))/(fun(y)-fun(x)))

//All Functions
Results* bisection(double (*func)(double), RaizAux aux, Results *resul);
Results* posicao_falsa(double (*func)(double), RaizAux aux, Results *resul);
Results* pegaso(double (*func)(double), RaizAux aux, Results *resul);
Results* newtonRhapson(double (*func)(double), double (*derivate)(double), RaizAux aux, Results *resul);
//end

Results* bisection(double (*func)(double), RaizAux aux, Results *resul){
    resul->iterations = 0;
    Interval interv = aux.interAB;
    double x0 = BISSEC(interv.a, interv.b);

    while(fabs(func(x0)) > aux.e){
        double raiz = func(x0);
        if(func(interv.a)*func(x0) < 0){
            interv.b = x0;
        }else{
            interv.a = x0;
        }
        x0 = BISSEC(interv.a, interv.b);
        resul->iterations++;
        
    }
    resul->x0 = x0;
    resul->fx0 = func(x0);
    resul->solutInterval.a = interv.a;
    resul->solutInterval.b = interv.b;
    return resul;
}   

Results* posicao_falsa(double (*func)(double), RaizAux aux, Results *resul){
    resul->iterations = 0;
    Interval interv = aux.interAB;
    double x0 = POS_FALSE(interv.a, interv.b, func);
    
    while(fabs(func(x0)) > aux.e){
        double raiz = func(x0);
        if(func(interv.a)*func(x0) < 0){
            interv.b = x0;
        }else{
            interv.a = x0;
        }
        x0 = POS_FALSE(interv.a, interv.b, func);
        resul->iterations++;
    }
    resul->x0 = x0;
    resul->fx0 = func(x0);
    resul->solutInterval.a = interv.a;
    resul->solutInterval.b = interv.b;
    return resul;
}

Results* pegaso(double (*func)(double), RaizAux aux, Results *resul){
    resul->iterations = 0;
    Interval interv = aux.interAB;
    double Fa = func(interv.a);
    double Fb = func(interv.b);
    double x0 = interv.b;
    double Fx = 0;

    double tooler2 = pow(aux.e, 2);

    while(true){
        x0 = (interv.a*Fb - interv.b*Fa)/(Fb - Fa);
        Fx = func(x0);

        if(Fa*Fx < 0){
            Fa = Fa*Fb/(Fb+Fx);
        }else{
            interv.a = interv.b;
            Fa = Fb;            
        }
        interv.b = x0;
        Fb = Fx;
        
        resul->iterations++;

        //condições de parada
        bool l1 = fabs(x0) > aux.e;
        bool l2 = fabs(Fa) > tooler2;
        bool l3 = fabs(Fb) > tooler2;
        if(!(l1 && l2 && l3)){
            break;
        }
    }
    resul->x0 = x0;
    resul->fx0 = func(x0);
    resul->solutInterval.a = interv.a;
    resul->solutInterval.b = interv.b;
    return resul;
}

Results* newtonRhapson(double (*func)(double), double (*derivate)(double), RaizAux aux, Results *resul){
    //xn+1 = xn - f(xn)/f'(xn)
    double xn = aux.interAB.b;

    while(true){

        xn = xn - func(xn)/derivate(xn);

        /*if(func(aux.interAB.a)*func(xn) < 0){
            aux.interAB.b = xn;
        }else{
            aux.interAB.a = xn;
        }*/


        bool l1 = fabs(func(xn)) > aux.e;
        //bool l2 = fabs(func(aux.interAB.a)) > aux.e;
        //bool l3 = fabs(func(aux.interAB.a)) > aux.e;
        bool l4 = derivate(xn) != 0;

        if(!(l1 /*&& l2 && l3*/ && l4)){
            break;
        }
        resul->iterations++;
    }
    resul->x0 = xn;
    resul->fx0 = func(xn);
    resul->solutInterval.a = aux.interAB.a;
    resul->solutInterval.b = aux.interAB.b;
    return resul;
}

#endif