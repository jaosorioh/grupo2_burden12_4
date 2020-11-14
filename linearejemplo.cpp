//Ejemplo del uso de las funciones del namespace LinearAlgebra.cpp

#include "linearalgebra.cpp"
using namespace std;
using namespace linearalgebra;

int main()
{ 
    //AC = B. Matriz A 4x4:
    vector<vector<double>> A = {{1.0, 2.0,-1.0, 1.0 }, 
                          	  {2.0, 0.0, 2.0, 1.0 }, 
                           	  {-1.0, 1.0, 1.0, 1.0 },
				  {1.0, 1.0, 1.0, 1.0}};
    //Vector B tamaño 4:
    vector<double> B = {-8.0, 13.0, 8.0, 1.0};
    
    //Vector solución C tamaño 4:
    vector<double> C = gaussianElimination(A,B); 

	for(int i =0; i<C.size();i++){cout<<"x"<<i<<": "<<C[i]<<endl;} //Mostrar el contenido de C

    double matrix[10][10] = {{1.5, 0.0, 0.0},
			    	     {0.0, 1.5 ,0.0},
			    	     {0.0, 0.0, 1.5}};

	printdet(matrix,3);
    cout<<"El determinante es: " << determinante(matrix, 3) <<endl;
 
    return 0; 
} 
