//Namespace

#include<bits/stdc++.h>
#include<iostream>
#include<math.h>

using namespace std;


// ######### DECLARACIÓN DE FUNCIONES ############## //

//#### Funcion para resolver determinante:
float determinante( double mat[10][10], int n);

// mostrar determinante:
void printdet(double mat[10][10], int n);

//#### Funciones para resolver sistema lineal (Solo hay que implementar gaussianElimination):

// function to get matrix content
void gaussianElimination(double mat[10][10+1], int N);

// function to reduce matrix to r.e.f.  Returns a value to
// indicate whether matrix is singular or not
int forwardElim(double mat[10][10+1], int N);

// function to calculate the values of the unknowns
void backSub(double mat[10][10+1], int N);

//Muestra las matrices
void print(double mat[10][10+1], int N);

// function for elementary operation of swapping two rows
void swap_row(double mat[10][10+1], int N, int i, int j);

// function to reduce matrix to r.e.f.
int forwardElim(double mat[10][10+1], int N);

// function to calculate the values of the unknowns
void backSub(double mat[10][10+1], int N);

//#########################################


double det(vector<vector<double>> & matrix)
{
    return (matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2])
           -matrix[1][0] * (matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2])
           +matrix[2][0] * (matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2]));
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

void gaussianElimination(double mat[10][10+1], int N)
{
    cout<<"Sistema a resolver: "<<endl;
    print(mat, N); //Mostrar el sistema a resolver
    /* reduction into r.e.f. */
    int singular_flag = forwardElim(mat, N);

    /* if matrix is singular */
    if (singular_flag != -1)
    {
        printf("Singular Matrix.\n");

        /* if the RHS of equation corresponding to
           zero row  is 0, * system has infinitely
           many solutions, else inconsistent*/
        if (mat[singular_flag][N])
            printf("Inconsistent System.");
        else
            printf("May have infinitely many "
                   "solutions.");

        return;
    }

    /* get solution to system and print it using
       backward substitution */
    backSub(mat, N);
}

// function for elementary operation of swapping two rows
void swap_row(double mat[10][10+1],int N, int i, int j)
{
    //printf("Swapped rows %d and %d\n", i, j);

    for (int k=0; k<=N; k++)
    {
        double temp = mat[i][k];
        mat[i][k] = mat[j][k];
        mat[j][k] = temp;
    }
}

// function to print matrix content at any stage
void print(double mat[10][10+1], int N)
{
    for (int i=0; i<N; i++, printf("\n"))
        for (int j=0; j<=N; j++) {
            cout<< setw(5)<< setprecision(1) <<mat[i][j];
            if(j == N-1) {
                cout<<"|";
            }
        }

    printf("\n");
}

// function to reduce matrix to r.e.f.
int forwardElim(double mat[10][10+1], int N)
{
    for (int k=0; k<N; k++)
    {
        // Initialize maximum value and index for pivot
        int i_max = k;
        int v_max = mat[i_max][k];

        /* find greater amplitude for pivot if any */
        for (int i = k+1; i < N; i++)
            if (abs(mat[i][k]) > v_max)
                v_max = mat[i][k], i_max = i;

        /* if a prinicipal diagonal element  is zero,
         * it denotes that matrix is singular, and
         * will lead to a division-by-zero later. */
        if (!mat[k][i_max])
            return k; // Matrix is singular

        /* Swap the greatest value row with current row */
        if (i_max != k)
            swap_row(mat, N, k, i_max);


        for (int i=k+1; i<N; i++)
        {
            /* factor f to set current row kth element to 0,
             * and subsequently remaining kth column to 0 */
            double f = mat[i][k]/mat[k][k];

            /* subtract fth multiple of corresponding kth
               row element*/
            for (int j=k+1; j<=N; j++)
                mat[i][j] -= mat[k][j]*f;

            /* filling lower triangular matrix with zeros*/
            mat[i][k] = 0;
        }

        //print(mat);        //for matrix state
    }
    cout<<"matrix triangular: "<<endl;
    print(mat, N);            //for matrix state
    return -1;
}

// function to calculate the values of the unknowns
void backSub(double mat[10][10+1], int N)
{
    double x[N];  // An array to store solution

    /* Start calculating from last equation up to the
       first */
    for (int i = N-1; i >= 0; i--)
    {
        /* start with the RHS of the equation */
        x[i] = mat[i][N];

        /* Initialize j to i+1 since matrix is upper
           triangular*/
        for (int j=i+1; j<N; j++)
        {
            /* subtract all the lhs values
             * except the coefficient of the variable
             * whose value is being calculated */
            x[i] -= mat[i][j]*x[j];
        }

        /* divide the RHS by the coefficient of the
           unknown being calculated */
        x[i] = x[i]/mat[i][i];
    }

    printf("\nSolución del sistema:\n");
    for (int i=0; i<N; i++) {
        cout<<"x"<<i<<" = "<< setprecision(2) << x[i]<<endl;
    }
    cout<<endl;
}

void linspace(double &i, double &f, int &N, bool &endpoint, vector<double> &a) {
    if (N == 1) {
        a.push_back(i);
    } else if (N > 1) {
        a.push_back(i);
        double h;
        h = (f - i) / (static_cast < double > (N - (endpoint ? 1 : 0)));

        for (int j = 1; j < N - 1; j++) {
            a.push_back(a.back() + h);
        }

        a.push_back(endpoint == true ? f : a.back() + h);
    } else {
        cout << "Debe tener al menos 1 elemento para linspace";
    }
}

void multi_linspace(vector < double > & v, int & N, vector < double > & a) {
    for (int i = 1; i < v.size(); i++) {
        double dvi = v.at(i) - v.at(i - 1);
        bool ep = true;//i == (v.size() - 1);
        vector < double > b;
        linspace(v.at(i - 1), v.at(i), N, ep, b);
        a.insert(a.end(), b.begin(), b.end());
    }

}    

//Fin namespace


