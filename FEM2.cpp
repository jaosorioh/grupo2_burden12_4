#include "include/Triangulation.h"
#include <algorithm>
#include <iostream>
#include <functional>
#include "include/linearalgebra.cpp"
#include "include/Integrals.h"
//prototipos

using namespace std;

int findNodeIndex(vector<Point>& nodes, Point& p);
//step 4-Nicole

void doubleIntegrals(vector<Triangle>& T, vector<vector<vector<double> > >& Z, vector<vector<double> >& H, vector<vector<double>> &A, vector<vector<double>> &B, vector<vector<double>> &C, function<double(const double & x, const double &y)> &p, function<double(const double &x , const double &y)> &q, function<double(const double & x, const double &y)> &r, function<double(const double &x, const double &y)> &f, Integrals & I){
    const int M = T.size();
    for(int i = 0; i<M; i++)
    {
        for(int j = 0; j<3; j++)
        {
            for(int k = 0; k<j; k++)
            {
                function<double(const double & , const double &)> inte = [r, A, B, C, i, j, k](const double & x, const double &y){
                    return r(x, y)*(A[i][j] + B[i][j]*x + C[i][j]*y)*(A[i][k] + B[i][k]*x + C[i][k]*y);
                };
                Z[i][j][k] = B[i][j]*B[i][k]*I.Integration2D(T[i], p)+C[i][j]*C[i][k]*I.Integration2D(T[i], q) -I.Integration2D(T[i], inte);
            }
            
            function<double(const double & , const double &)> inte2 = [f, A, B, C, i, j](const double & x, const double &y){
                    return f(x, y)*(A[i][j] + B[i][j]*x + C[i][j]*y);
                };
            
           H[i][j] =-I.Integration2D(T[i], inte2);
            cout << H[i][j];
        }
    }
}

//step 5-Nicole
void lineIntegrals(vector<Triangle> & T, vector<vector<vector<double> > >& J, vector<vector<double> >& I, vector<vector<double>> &A, vector<vector<double>> &B, vector<vector<double>> &C, function<double(const double &x, const double &y)> &g1, function<double(const double &x , const double &y)> &g2, Point (*SE)(const double &_t ), const double & ta, const double &tb){
    const int M = T.size();
    Integrals I2;
    for(int i = 0; i<M; i++)
    {
        for(int j = 0; j<3; j++)
        {
            for(int k = 0; k<j; k++)
            {
                function<double(const double & , const double &)> inte = [g1, A, B, C, i, j, k](const double & x, const double &y){
                    return g1(x, y)*(A[i][j] + B[i][j]*x + C[i][j]*y)*(A[i][k] + B[i][k]*x + C[i][k]*y);
                };
                J[i][k][j] = I2.lineIntegration(inte, SE, ta, tb);
            }
            
            function<double(const double & , const double &)> inte2 = [g2, A, B, C, i, j](const double & x, const double &y){
                    return g2(x, y)*(A[i][j] + B[i][j]*x + C[i][j]*y);
                };
            I[i][j] = I2.lineIntegration(inte2, SE, ta, tb);
            
        }
    }
}

//step 6-12-Brayan
void assembleDoubleIntegrals(vector<Triangle> T, vector<Point>& nodes, vector<Point>& nodesS2, vector<vector<double> >& alpha, vector<double>& beta, vector<double>& gamma, vector<vector<vector<double> > >& Z, vector<vector<double> >& H);

void assembleLineIntegrals(vector<Triangle>& TS2, vector<vector<double> >& alpha, vector<double>& beta, vector<double>& gamma, vector<vector<vector<double> > >& J, vector<vector<double> >& I);

/* Función del paso 6-12
INPUT: Vector de triángulos que alberga todos los triángulos, vector de nodos en S2, alfa, beta, gamma, Z, H.
OUTPUT: vacía, solo llena los alfa y beta */
void assembleDoubleIntegrals(vector<Triangle> T, vector<Point>& nodesS2, vector<vector<double> >& alpha, vector<double>& beta, vector<double>& gamma, vector<vector<vector<double> > >& Z, vector<vector<double> >& H)
{
    //Paso 6: correr sobre todos los triangulos
    const int Mt = T.size(); //Numero total de triángulos, el primer for va hasta aquí
    const int n = nodesS2.size();
    for (int i = 0; i < Mt; i++) {
        vector<Point> Nodesi = T[i].getVertices(); //Los 3 Nodos del triángulo i
   
        //Paso 7: correr k = 1,2,3 (En nuestro caso 0,1,2)
        for (int k = 0; k < 3; k++) {
            //Paso 8: Encontramos el indice l en la lista de todos los nodos en S1US2
            int l = findNodeIndex(nodesS2, Nodesi[k]);

            //Paso 9:
            if (k > 0) { //If k != 0
                for (int j = 0; j < k-1; j++) { // j =0,1...k-1

                    //Paso 10:
                    int t = findNodeIndex(nodesS2, Nodesi[j]);

                    //Paso 11:
                    if (l < n) {
                        if (t < n) {
                            alpha[l][t] = alpha[l][t] + Z[i][k][j];
                            alpha[t][l] = alpha[t][l] + Z[i][k][j];
                        }
                        else {
                            beta[l] = beta[l] - gamma[t] * Z[i][k][j];
                        }
                    }
                    else if (t < n) {
                        beta[t] = beta[t] - gamma[l] * Z[i][k][j];
                    }
                }
                //Paso 12:
                if (l < n) {
                    alpha[l][l] = alpha[l][l] + Z[i][k][k];
                    beta[l] = beta[l] + H[i][k];
                }
            }
        }
    }

} //Fin :D

/* Función del paso 13-19
INPUT: Los triángulos que tienen  al menos un nodo en S2, alfa, beta, gamma, J, I.
OUTPUT: vacía, solo llena los alfa y beta */
void assembleLineIntegrals(vector<Triangle>& TS2, vector<Point> nodesS2, vector<vector<double> >& alpha, vector<double>& beta, vector<double>& gamma, vector<vector<vector<double> > >& J, vector<vector<double> >& I)
{
    //Paso 13: correr sobre los triangulos con al menos un edge en S2
    const int K = TS2.size(); //Triángulos con al menos un edge en S2, sobre esto corre el for
    const int n = nodesS2.size();
    for (int i = 0; i < K; i++) {
        vector<Point> Nodesi = TS2[i].getVertices();        
        //Los 3 Nodos del triángulo i

        //Paso 14: correr sobre k = 1,2,3 (0,1,2 en nuestro caso)
        for (int k = 0; k < 3; k++) {
            //Paso 15: encontrar l en la lista de nodos

            int l = findNodeIndex(nodesS2, Nodesi[k]); //Encontramos el indice l en la lista de todos los nodos en S1US2

            //Paso 16:
            if (k > 0) { //If k != 0
                for (int j = 0; j < k-1; j++) { // j =0,1...k-1

                    //Paso 17: encontrar t
                    int t = findNodeIndex(nodesS2, Nodesi[j]);

                    //Paso 18:
                    if (l < n) {
                        if (t < n) {
                            alpha[l][t] = alpha[l][t] + J[i][k][j];
                            alpha[t][l] = alpha[t][l] + J[i][k][j];
                        }
                        else {
                            beta[l] = beta[l] - gamma[t] * J[i][k][j];
                        }
                    }
                    else if (t < n) {
                        beta[t] = beta[t] - gamma[l] * J[i][k][j];
                    }
                }

                //Paso 19:
                if (l < n) {
                    alpha[l][l] = alpha[l][l] + J[i][k][k];
                    beta[l] = beta[l] + I[i][k];
                }
            }
        }
    }

} //Fin :D

//Calcula los vectores a, b, c del triángulo i
void coefABC(Triangle& T, vector<double>& a, vector<double>& b, vector<double>& c, vector<function<double(const double & , const double &)>> & Ni)
{
    double x1, x2, x3, y1, y2, y3;
    x1 = T.getV1().getX();
    y1 = T.getV1().getY();
    x2 = T.getV2().getX();
    y2 = T.getV2().getY();
    x3 = T.getV3().getX();
    y3 = T.getV3().getY();

    vector<vector<double> > matrix = { { 1.0, x1, y1 },
        { 1.0, x2, y2 },
        { 1.0, x3, y3 } };

    double delta = linearalgebra::det(matrix);
    double a1, a2, a3;
    a1 = (x2 * y3 - y2 * x3) / delta;
    a2 = (x3 * y1 - y3 * x1) / delta;
    a3 = (x1 * y2 - y1 * x2) / delta;
    a.insert(a.end(), { a1, a2, a3 });

    double b1, b2, b3;
    b1 = (y2 - y3) / delta;
    b2 = (y3 - y1) / delta;
    b3 = (y1 - y2) / delta;
    b.insert(b.end(), { b1, b2, b3 });

    double c1, c2, c3;
    c1 = (x3 - x2) / delta;
    c2 = (x1 - x3) / delta;
    c3 = (x2 - x1) / delta;

    c.insert(c.end(), { c1, c2, c3 });
    
    for (int i = 0; i < 3; i++) {
        function<double(const double &, const double &)> Nj;
        Nj = [a, b, c, i](const double &x, const double &y){return a[i] + b[i] * x + c[i] * y;};
        Ni.push_back(Nj);
    }
}

//Agrupa cada uno de los vectores a, b, c para cada triangulo en las matrices A, B, y C respectivamente. Sobrecargo del anterior
void coefABC(vector<Triangle> triangles, vector<vector<double> >& A, vector<vector<double> >& B, vector<vector<double> >& C, vector<vector<function<double(const double & , const double &)>>> &N)
{
    for (int i = 0; i < triangles.size(); i++) {
        vector<double> a;
        vector<double> b;
        vector<double> c;
        vector<function<double(const double & , const double &)>> Ni;
        coefABC(triangles.at(i), a, b, c, Ni);
        A.push_back(a);
        B.push_back(b);
        C.push_back(c);
        N.push_back(Ni);
    }
}


//step 8, 10, 15, 17
int findNodeIndex(vector<Point>& nodes, Point& p)
{
    int i = 0;
    while (i < nodes.size()) {
        if (p.getX() == nodes.at(i).getX() && p.getY() == nodes.at(i).getY())
            break;
        i++;
    }
    return i;
}

void solve(double* (*S2Fx)(const double&, double&), double* (*S2Fy)(double&, const double&), function<double(const double &x, const double &y)> &p, function<double(const double &x, const double &y)> &q, function<double(const double &x, const double &y)> &r, function<double(const double &x, const double &y)> &f, function<double(const double &x, const double &y)> &g, function<double(const double &x, const double &y)> &g1, function<double(const double &x, const double &y)> &g2, vector<double>& x_i, vector<double>& y_i, int& N, int& M, Point (*SE)(const double &_t ), const double &ta, const double &tb)
{
    //step 0
    vector<Point> nodesS1;
    vector<Point> nodesS2;
    vector<Triangle> trianglesS1;
    vector<Triangle> trianglesS2;
    vector<Triangle> trianglesnotS1S2;

    vector<double> x;

    vector<double> y;

    Triangulation t;
    linearalgebra::multi_linspace(x_i, N, x);
    linearalgebra::multi_linspace(y_i, M, y);

    t.buildTrianglesAndNodes(trianglesS1, trianglesS2, trianglesnotS1S2, nodesS1, nodesS2, S2Fx, S2Fy, x, y);
    
    vector<Triangle> AB = trianglesS2;
    AB.insert(AB.end(), trianglesS1.begin(), trianglesS1.end());
    AB.insert(AB.end(), trianglesnotS1S2.begin(), trianglesnotS1S2.end());
    /*string fname = "dat/S1Triangles.dat";
    t.saveTriangles(trianglesS1, fname);
    fname = "dat/S2Triangles.dat";
    t.saveTriangles(trianglesS2, fname);
    fname = "dat/NotS1S2Triangles.dat";
    t.saveTriangles(trianglesnotS1S2, fname);

    fname = "dat/nodesS1.dat";
    t.saveNodes(nodesS1, fname);
    fname = "dat/nodesS2.dat";
    t.saveNodes(nodesS2, fname);

    */
    //step 1
    
    const int n = nodesS2.size();
    const int m = nodesS1.size();
    
    const int MM = AB.size();
    
    vector<double> gammaS1;

    for (int i = 0; i < m - 1; i++) {
        gammaS1.push_back(g(nodesS1.at(i).getX(), nodesS1.at(i).getY()));
    }
    //step 2

    vector<vector<double> > alpha(n, vector<double>(n, 0));
    vector<double> beta(n, 0);

    //step 3

    vector<vector<double> > A;
    vector<vector<double> > B;
    vector<vector<double> > C;
    vector<vector<function<double(const double & , const double &)>>> Nij;
    
    coefABC(AB, A, B, C, Nij);
    
    Integrals I2;
    vector<vector<vector<double>>> Z(MM, vector<vector<double>>(3, vector<double>(3, 0)));
    vector<vector<double> > H(MM, vector<double>(3, 0));
    doubleIntegrals(AB, Z, H, A, B, C, p, q, r, f, I2);
    
    vector<vector<vector<double>>> J(trianglesS2.size(), vector<vector<double>>(3, vector<double>(3, 0)));
    vector<vector<double> > I(trianglesS2.size(), vector<double>(3, 0));
    
    lineIntegrals(trianglesS2, J, I, A, B, C, g1, g2, SE, ta, tb);
    
    assembleDoubleIntegrals(AB, nodesS2, alpha, beta, gammaS1, Z, H);
    assembleLineIntegrals(trianglesS2, nodesS2, alpha, beta, gammaS1, J, I);
    cout << "alpha:" << endl;
    for(int i = 0; i<alpha.size(); i++)
    {
        cout << "{";
        for(int j = 0; j<alpha[i].size();j++)
        {
            cout <<  alpha[i][j] << ", ";
        }
        cout << "}"<< endl;
    }
    
    cout << "beta:" << endl;
    for(int i = 0; i<beta.size(); i++)
    {
        
        cout << beta[i] << " ";
    }
    cout << endl;
    
    vector<double> gamma = linearalgebra::gaussianElimination(alpha, beta); 

    for(int i =0; i<gamma.size();i++){cout<<"x"<<i<<": "<<gamma[i]<<endl;} //Mostrar el contenido de C


}
