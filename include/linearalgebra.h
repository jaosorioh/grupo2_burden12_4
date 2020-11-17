//Namespace
#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H
#include <bits/stdc++.h>
#include <iostream>
#include <math.h>

using namespace std;

class linearalgebra {
    
public:
    
    //Funcion para resolver determinante:
    double det(vector<vector<double> >& matrix);

    //función principal
    vector<double> gaussianElimination(vector<vector<double> > A, vector<double> B);

    void multi_linspace(vector<double>&, int&, vector<double>&);
    void linspace(double&, double&, int&, bool&, vector<double>&);

private:
    // función para reducir la matriz a r.e.f. Devuelve un valor para indicar si la matriz es singular o no(r.e.f = reduction to echoleon form = reduccion a forma escalonada)
    int forwardElim(vector<vector<double> > mat);

    // Funcion para calcular el valor de las incognitas
    vector<double> backSub(vector<vector<double> > mat);

    //Muestra las matrices

    // Función para la operación de elementaria de intercambiar filas
    void swap_row(vector<vector<double> > mat, int i, int j);

    // función para llenar matriz del sistema AC = B con los vectores A y B (el sistema es una matriz con la última columna el lado derecho de la ecuación)
    vector<vector<double> > fillSystem(vector<vector<double> > A, vector<double> B);

};

#endif
