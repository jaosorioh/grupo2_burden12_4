//Namespace

#include<bits/stdc++.h> 
#include<iostream>
#include<math.h>

using namespace std; 

namespace linearalgebra
{
// ######### DECLARACIÓN DE FUNCIONES ############## //

//#### Funcion para resolver determinante:
float determinante( double mat[10][10], int n);

// mostrar determinante:
void printdet(double mat[10][10], int n);

//#### Funciones para resolver sistema lineal (Solo hay que implementar gaussianElimination): 

// Función principal, soluciona AC = B: para obtener el contenido de la matriz y llamar las otras funciones
//INPUT: Matriz A NxN y vector B de tamaño N
//OUTPUT: Vector solución C de tamaño N
vector<double> gaussianElimination(vector<vector<double>> A, vector<double> B);

// función para reducir la matriz a r.e.f. Devuelve un valor para indicar si la matriz es singular o no(r.e.f = reduction to echoleon form = reduccion a forma escalonada)
int forwardElim(vector<vector<double>> mat); 
  
// Funcion para calcular el valor de las incognitas 
vector<double> backSub(vector<vector<double>> mat); 

//Muestra las matrices
void print(vector<vector<double>> mat);

// Función para la operación de elementaria de intercambiar filas 
void swap_row(vector<vector<double>> mat, int i, int j);

// Función para reducir la matriz a r.e.f. (reduction to echelon form)
int forwardElim(vector<vector<double>> mat);

// función para llenar matriz del sistema AC = B con los vectores A y B (el sistema es una matriz con la última columna el lado derecho de la ecuación)
vector<vector<double>> fillSystem(vector<vector<double>> A, vector<double> B);

//#########################################


vector<vector<double>> fillSystem(vector<vector<double>> matrix, vector<double> row)
{
	if( matrix.size() == row.size() )
	{
		for(int i = 0; i<matrix.size(); i++){
		matrix[i].push_back(row[i]);}
	}
	else if(matrix.size() > row.size()){cout<<"Cuiado, el sistema no es cuadrado. (Matriz mayor que columna)"<<endl;}
	else{cout<<"Cuiado, el sistema no es cuadrado. (Columna mayor que matriz)"<<endl;}
	return matrix;
}

float determinante( double matrix[10][10], int n)
{
    float det = 0.0;
    double submatrix[10][10];
    if (n == 2)
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    else {
        for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j == x)
                        continue;
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            det = det + (pow(-1, x) * matrix[0][x] * determinante( submatrix, n - 1 ));
        }
    }
    return det;
}

void printdet(double matrix[10][10], int n)
{
    cout<<"Determinante a resolver: "<<endl;
    for (int i = 0; i < n; i++) {
        cout<<"|";
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] <<" ";
        }
        cout<<"|"<<endl;
    }
}

vector<double> gaussianElimination(vector<vector<double>> A, vector<double> B) 
{ 
	vector<vector<double>> mat = fillSystem(A,B);
	int N = mat.size();

	//Para ver el sistema a resolver, descomentar lo siguiente:
	/*cout<<"Sistema a resolver: "<<endl;
	print(mat); //Mostrar el sistema a resolver */

    // Reducción
    int singular_flag = forwardElim(mat); 
  
    // Si la matriz es singular
    if (singular_flag != -1) 
    { 
        printf("Matriz Singular.\n"); 
  
        // si el RHS de la ecuación correspondiente a la fila cero es 0, el sistema tiene infinitas soluciones, de lo contrario es inconsistente
        if (mat[singular_flag][N]) 
            printf("Sistema inconsistente"); 
        else
            printf("May have infinitely many "
                   "solutions."); 
    } 
  
    // Obtener la solución y guardarla en un vector
    vector<double> Solutions = backSub(mat); 
    return Solutions;
} 
  
// Función para operaciones elementarias entre filas
void swap_row(vector<vector<double>> mat, int i, int j) 
{ 
    int N = mat.size();
    //printf("Filas cambiadas %d and %d\n", i, j); //Mostrar cambios entre filas
  
    for (int k=0; k<=N; k++) 
    { 
        double temp = mat[i][k]; 
        mat[i][k] = mat[j][k]; 
        mat[j][k] = temp; 
    } 
} 
  
// Función para mostrar estado de la matriz
void print(vector<vector<double>> mat) 
{ 
    int N = mat.size();
    for (int i=0; i<N; i++, printf("\n")) 
        for (int j=0; j<=N; j++){
	    cout<< setw(5)<< setprecision(4) <<mat[i][j];
	    if(j == N-1){cout<<"|";}}
  
    printf("\n"); 
} 
  
// Función para reducir la matriz 
int forwardElim(vector<vector<double>> mat) 
{ 
    int N = mat.size();
    for (int k=0; k<N; k++) 
    { 
        // Inicializar valor máximo e índice para pivote
        int i_max = k; 
        int v_max = mat[i_max][k]; 
  
        // Encontrar mayor amplitud para el pivote si lo hay
        for (int i = k+1; i < N; i++) 
            if (abs(mat[i][k]) > v_max) 
                v_max = mat[i][k], i_max = i; 
  
        // si un elemento diagonal principal es cero, denota que la matriz es singular y conducirá a una división por cero más adelante
        if (!mat[k][i_max]) 
            return k; // La Matriz es singular
  
        // Intercambiar la fila de mayor valor con la fila actual
        if (i_max != k) 
            swap_row(mat, k, i_max); 
  
  
        for (int i=k+1; i<N; i++) 
        { 
	    //factor f para setear el k-ésimo elemento de la fila actual en 0 y la k-ésima columna restante en 0
            double f = mat[i][k]/mat[k][k]; 
  
            // Restar el f multiplo of correspondiente al elemento de la fila k
            for (int j=k+1; j<=N; j++) 
                mat[i][j] -= mat[k][j]*f; 
  
            // Llenar la matriz triangular inferior con ceros
            mat[i][k] = 0; 
        } 
  
        //print(mat);        //Estado de la matriz
    } 
	//Para ver la matriz triangular final, descomentar lo siguiente:
    /*cout<<"Matriz triangular: "<<endl;
    print(mat);*/            //Estado de la matriz 
    return -1; 
} 
  
// función que calcula el valor de las incógnitas
vector<double> backSub(vector<vector<double>> mat) 
{ 
    int N = mat.size();
    vector<double> x(N);  // Vector para guardar la solución
  
    // Comenzamos a calcular de la última ecuación a la primera
    for (int i = N-1; i >= 0; i--) 
    { 
        // Empezamos con el lado derecho de la ecuación
        x[i] = mat[i][N]; 
  
        // Initializamos j en i+1 ya que la matriz es superior triangular
        for (int j=i+1; j<N; j++) 
        { 
            // restar todos los valores de lhs excepto el coeficiente de la variable cuyo valor se está calculando
            x[i] -= mat[i][j]*x[j]; 
        } 
  
        // dividir el RHS por la incógnita que se está calculando
        x[i] = x[i]/mat[i][i]; 
    } 
    
	//Para ver la solución, descomentar lo siguiente:
 
    /*printf("\nSolución del sistema:\n"); 
    for (int i=0; i<N; i++){
        cout<<"x"<<i<<" = "<< setprecision(4) << x[i]<<endl;}
	cout<<endl;*/

	return x;
} 

}//Fin namespace

