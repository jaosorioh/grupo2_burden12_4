#include "../include/linearalgebra.h"

using namespace std;

vector<vector<double> > linearalgebra::fillSystem(vector<vector<double> > matrix, vector<double> row)
{
    if (matrix.size() == row.size()) {
        for (int i = 0; i < matrix.size(); i++) {
            matrix[i].push_back(row[i]);
        }
    }
    else if (matrix.size() > row.size()) {
        cout << "Cuidado, el sistema no es cuadrado. (Matriz mayor que columna)" << endl;
    }
    else {
        cout << "Cuidado, el sistema no es cuadrado. (Columna mayor que matriz)" << endl;
    }
    return matrix;
}

double linearalgebra::det(vector<vector<double> >& matrix)
{
    return (matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2])
        - matrix[1][0] * (matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2])
        + matrix[2][0] * (matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2]));
}

/*
función principal GaussianElimination - soluciona AC = B: para obtener el contenido de la matriz y llamar las otras funciones
INPUT: Matriz A NxN y vector B de tamaño N
OUTPUT: Vector solución C de tamaño N
*/
vector<double> linearalgebra::gaussianElimination(vector<vector<double> > A, vector<double> B)
{
    vector<vector<double> > mat = fillSystem(A, B);
    int N = mat.size();

    // Reducción
    int singular_flag = forwardElim(mat);

    // Si la matriz es singular
    if (singular_flag != -1) {
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
void linearalgebra::swap_row(vector<vector<double> > mat, int i, int j)
{
    int N = mat.size();

    for (int k = 0; k <= N; k++) {
        double temp = mat[i][k];
        mat[i][k] = mat[j][k];
        mat[j][k] = temp;
    }
}

// Función para reducir la matriz
int linearalgebra::forwardElim(vector<vector<double> > mat)
{
    int N = mat.size();
    for (int k = 0; k < N; k++) {
        // Inicializar valor máximo e índice para pivote
        int i_max = k;
        int v_max = mat[i_max][k];

        // Encontrar mayor amplitud para el pivote si lo hay
        for (int i = k + 1; i < N; i++)
            if (abs(mat[i][k]) > v_max)
                v_max = mat[i][k], i_max = i;

        // si un elemento diagonal principal es cero, denota que la matriz es singular y conducirá a una división por cero más adelante
        if (!mat[k][i_max])
            return k; // La Matriz es singular

        // Intercambiar la fila de mayor valor con la fila actual
        if (i_max != k)
            swap_row(mat, k, i_max);

        for (int i = k + 1; i < N; i++) {
            //factor f para setear el k-ésimo elemento de la fila actual en 0 y la k-ésima columna restante en 0
            double f = mat[i][k] / mat[k][k];

            // Restar el f multiplo of correspondiente al elemento de la fila k
            for (int j = k + 1; j <= N; j++)
                mat[i][j] -= mat[k][j] * f;

            // Llenar la matriz triangular inferior con ceros
            mat[i][k] = 0;
        }

        //Estado de la matriz
    }
    return -1;
}

// función que calcula el valor de las incógnitas
vector<double> linearalgebra::backSub(vector<vector<double> > mat)
{
    int N = mat.size();
    vector<double> x(N); // Vector para guardar la solución

    // Comenzamos a calcular de la última ecuación a la primera
    for (int i = N - 1; i >= 0; i--) {
        // Empezamos con el lado derecho de la ecuación
        x[i] = mat[i][N];

        // Initializamos j en i+1 ya que la matriz es superior triangular
        for (int j = i + 1; j < N; j++) {
            // restar todos los valores de lhs excepto el coeficiente de la variable cuyo valor se está calculando
            x[i] -= mat[i][j] * x[j];
        }

        // dividir el RHS por la incógnita que se está calculando
        x[i] = x[i] / mat[i][i];
    }
    return x;
}

void linearalgebra::linspace(double& i, double& f, int& N, bool& endpoint, vector<double>& a)
{
    if (N == 1) {
        a.push_back(i);
    }
    else if (N > 1) {
        a.push_back(i);
        double h;
        h = (f - i) / (static_cast<double>(N - (endpoint ? 1 : 0)));

        for (int j = 1; j < N - 1; j++) {
            a.push_back(a.back() + h);
        }

        a.push_back(endpoint == true ? f : a.back() + h);
    }
    else {
        cout << "Debe tener al menos 1 elemento para linspace";
    }
}

void linearalgebra::multi_linspace(vector<double>& v, int& N, vector<double>& a)
{
    for (int i = 1; i < v.size(); i++) {
        double dvi = v.at(i) - v.at(i - 1);
        bool ep = true; //i == (v.size() - 1);
        vector<double> b;
        linspace(v.at(i - 1), v.at(i), N, ep, b);
        a.insert(a.end(), b.begin(), b.end());
    }
}
