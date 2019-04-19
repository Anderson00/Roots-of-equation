#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <math.h>
#include <stdlib.h>

//All Functions; Padrão: double <nome>(<double>);
double func1(double x);//2x^(3)-4x^(2)+3x
double func2(double x);//x^5 - 3x^4 - 3x^2 + 2
double func3(double x);//sqrt(x) - 5^-x
double func4(double x);//x^5 - x^4 - 4x + 1
double func5(double x);//0.05x^3 - 0.4x^2 +3*x*senx
//end


double func1(double x){    
    return 2*pow(x,3)-4*pow(x,2)+3*x;
}

double func2(double x){
    return pow(x,5) - 3*pow(x,4) - 3*pow(x,2) + 2;
}

double func3(double x){
    return sqrt(x) - pow(5,-1*x);
}

double func4(double x){
    return pow(x, 5) - pow(x, 4) - 4*x + 1;
}

//tive que converter x rad em angulos, pois o sin calcula em rad
//Na internet: func5(3) = -0.9799192;
//Aqui: func(3) = -10.516382;
double func5(double x){
    double radToAngle = ((180.0 * x) / (M_PI));//Precisao ruim
    return 0.005*pow(x, 3) - 0.4*pow(x, 2) - 3.0*x*sin(radToAngle);
}

#endif