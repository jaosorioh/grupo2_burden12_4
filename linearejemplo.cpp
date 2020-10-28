//Ejemplo del uso de las funciones del namespace LinearAlgebra.cpp

#include "linearalgebra.cpp"
using namespace std;
using namespace linearalgebra;

int main()
{ 
    // input matrix: La última columna es la parte derecha de las ecuaciones
    double mat[10][10+1] = {{1.0, 2.0,-1.0, 3.0, -8.0}, 
                          {2.0, 0.0, 2.0, -1.0, 13.0}, 
                          {-1.0, 1.0, 1.0, -1.0, 8},
			  {3.0, 3.0 , -1.0, 2.0, -1}}; 

    gaussianElimination(mat, 4); 

    double matrix[10][10] = {{1.5, 0.0, 0.0},
			    {0.0, 1.5 ,0.0},
			    {0.0, 0.0, 1.5}};
    //print(matrix);
//mostrar la matriz: 

	printdet(matrix, 3);
    cout<<"El determinante es: " << determinante(matrix, 3) <<endl;
    return 0; 
} 
