#include "../include/FEM.h"
#include "../include/linearalgebra.h"
#include <iomanip>
using namespace std;

/*
El constructor recibe toda la información del usuario sobre el problema e inicia la triangulación
INPUTS: funciones S2x, S2y, p, q, r, f, g, g1, g2, vectores x_i, y_i, números N, M, contorno parametrizado SE, DSE (derivada), puntos extremos ta,tb 
*/
FEM::FEM(double* (*S2Fx_)(const double& x, double& y), double* (*S2Fy_)(double& x, const double& y), function<double(const double& x_, const double& y_)>& p_, function<double(const double& x_, const double& y_)>& q_, function<double(const double& x_, const double& _y)>& r_, function<double(const double& x_, const double& y_)>& f_, function<double(const double& x_, const double& y_)>& g_, function<double(const double& x_, const double& y_)>& g1_, function<double(const double& x_, const double& y_)>& g2_, vector<double>& x_i, vector<double>& y_i, int& N_, int& M_, function<Point(const double& t_)>& SE_, function<Point(const double& t_)>& DSE_, const double& ta_, const double& tb_)
{
    //---------------STEP 0 ---------------
    vector<Triangle> trianglesnotS1S2;
    vector<Triangle> trianglesS2;
    vector<Triangle> trianglesS1;

    la.multi_linspace(x_i, N_, xx);
    la.multi_linspace(y_i, M_, yy);

    triang.buildTrianglesAndNodes(trianglesS1, trianglesS2, trianglesnotS1S2, S2Fx_, S2Fy_, xx, yy);

    Triangles = trianglesnotS1S2;
    K = Triangles.size();

    Triangles.insert(Triangles.end(), trianglesS2.begin(), trianglesS2.end());
    N = Triangles.size();
    Triangles.insert(Triangles.end(), trianglesS1.begin(), trianglesS1.end());

    M = Triangles.size();
    for (int i = 0; i < N; i++) {
        vector<Point> nodes = Triangles[i].getVertices();
        for (int j = 0; j < nodes.size(); j++) {
            int l = findNodeIndex(nodes[j]);
            if (Nodes.size() == 0 || l >= Nodes.size()) {
                Nodes.push_back(nodes[j]);
            }
        }
    }
    n = Nodes.size();

    for (int i = N; i < M; i++) {
        vector<Point> nodes = Triangles[i].getVertices();
        for (int j = 0; j < nodes.size(); j++) {
            int l = findNodeIndex(nodes[j]);
            if (Nodes.size() == 0 || l >= Nodes.size()) {
                Nodes.push_back(nodes[j]);
            }
        }
    }

    m = Nodes.size();
    //---------------VALORES K, N, M, n, m---------------
    cout << "n: " << n << ", m: " << m << endl;
    cout << "K: " << K << ", N: " << N << ", M: " << M << endl;
    //---------------STEP 1---------------
    gamma = vector<double>(m, 0);
    for (int i = n; i < m; i++) {

        gamma[i] = g_(Nodes[i].getX(), Nodes[i].getY());
    }

    //---------------STEP 2---------------
    alpha = vector<vector<double> >(n, vector<double>(n, 0));

    beta = vector<double>(n, 0);

    Z = vector<vector<vector<double> > >(M, vector<vector<double> >(3, vector<double>(3, 0)));
    H = vector<vector<double> >(M, vector<double>(3, 0));

    J = vector<vector<vector<double> > >(N - K, vector<vector<double> >(3, vector<double>(3, 0)));
    I = vector<vector<double> >(N - K, vector<double>(3, 0));

    p = p_;
    q = q_;
    r = r_;
    f = f_;
    g = g_;
    g1 = g1_;
    g2 = g2_;
    SE = SE_;
    DSE = DSE_;
    ta = ta_;
    tb = tb_;
}

//---------------STEP 3---------------
//Calcula los vectores a, b, c del triángulo i
void FEM::coefABC(Triangle& T, vector<double>& a, vector<double>& b, vector<double>& c)
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
    double delta = la.det(matrix);
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
}

//Agrupa cada uno de los vectores a, b, c para cada triangulo en las matrices A, B, y C respectivamente. Sobrecargo del anterior
void FEM::coefABC()
{
    for (int i = 0; i < M; i++) {
        vector<double> a;
        vector<double> b;
        vector<double> c;
        coefABC(Triangles[i], a, b, c);

        A.push_back(a);
        B.push_back(b);
        C.push_back(c);
    }
}

//---------------STEP 4---------------
void FEM::doubleIntegrals()
{
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k <= j; k++) {
                function<double(const double&, const double&)> inte = [this, &i, &j, &k](const double& x, const double& y) {
                    return this->r(x, y) * (this->A[i][j] + this->B[i][j] * x + this->C[i][j] * y) * (this->A[i][k] + this->B[i][k] * x + this->C[i][k] * y);
                };
                Z[i][j][k] = B[i][j] * B[i][k] * Integrator.Integration2D(Triangles[i], p) + C[i][j] * C[i][k] * Integrator.Integration2D(Triangles[i], q) - Integrator.Integration2D(Triangles[i], inte);
            }

            function<double(const double&, const double&)> inte2 = [this, &i, &j](const double& x, const double& y) {
                return this->f(x, y) * (this->A[i][j] + this->B[i][j] * x + this->C[i][j] * y);
            };

            H[i][j] = -Integrator.Integration2D(Triangles[i], inte2);
        }
    }
}

//---------------STEP 5---------------
void FEM::lineIntegrals()
{
    for (int i = K; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k <= j; k++) {
                function<double(const double&, const double&)> inte = [this, &i, &j, &k](const double& x, const double& y) {
                    return this->g1(x, y) * (this->A[i][j] + this->B[i][j] * x + this->C[i][j] * y) * (this->A[i][k] + this->B[i][k] * x + this->C[i][k] * y);
                };

                J[i - K][j][k] = Integrator.lineIntegration(inte, SE, DSE, ta, tb);
            }

            function<double(const double&, const double&)> inte2 = [this, &i, &j](const double& x, const double& y) {
                return this->g2(x, y) * (this->A[i][j] + this->B[i][j] * x + this->C[i][j] * y);
            };

            I[i - K][j] = Integrator.lineIntegration(inte2, SE, DSE, ta, tb);
        }
    }
}

//---------------STEP 6---------------

int FEM::findNodeIndex(Point& p)
{
    int i = 0;
    while (i < Nodes.size()) {
        //cout << i <<" - (" << Nodes[i].toStr() <<") and (" << p.toStr() <<") are " << ((p.getX() == Nodes[i].getX() && p.getY() == Nodes[i].getY()) ? "equal" : "diferent") << endl;
        if (p.getX() == Nodes[i].getX() && p.getY() == Nodes[i].getY())
            break;
        i++;
    }
    return i;
}

int FEM::findNodeIndex(Point& p, vector<Point> nd)
{
    int i = 0;
    while (i < nd.size()) {
        if (p.getX() == nd[i].getX() && p.getY() == nd[i].getY())
            break;
        i++;
    }
    return i;
}

/* Función del paso 6-12
INPUT: Vector de triángulos que alberga todos los triángulos, vector de nodos en S2, alfa, beta, gamma, Z, H.
OUTPUT: vacía, solo llena los alfa y beta 
*/
void FEM::assembleDoubleIntegrals()
{
    for (int i = 0; i < M; i++) {
        vector<Point> Nodesi = Triangles[i].getVertices(); //Los 3 Nodos del triángulo i

        //Paso 7: correr k = 1,2,3 (En nuestro caso 0,1,2)
        for (int k = 0; k < 3; k++) {
            //Paso 8: Encontramos el indice l en la lista de todos los nodos en S1US2
            int l = findNodeIndex(Nodesi[k]);
            //Paso 9:
            if (k > 0) { //If k != 0/
                for (int j = 0; j < k - 1; j++) { // j =0,1...k-1

                    //Paso 10:
                    int t = findNodeIndex(Nodesi[j]);
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
            }
            //Paso 12:

            if (l < n) {
                alpha[l][l] = alpha[l][l] + Z[i][k][k];
                beta[l] = beta[l] + H[i][k];
            }
        }
    }

} //Fin :D

//---------------STEP 13---------------
/* Función del paso 13-19
INPUT: Los triángulos que tienen  al menos un nodo en S2, alfa, beta, gamma, J, I.
OUTPUT: vacía, solo llena los alfa y beta 
*/
void FEM::assembleLineIntegrals()
{
    //Paso 13: correr sobre los triangulos con al menos un edge en S2
    //Triángulos con al menos un edge en S2, sobre esto corre el for
    for (int i = K; i < N; i++) {
        vector<Point> Nodesi = Triangles[i].getVertices();
        //Los 3 Nodos del triángulo i

        //Paso 14: correr sobre k = 1,2,3 (0,1,2 en nuestro caso)
        for (int k = 0; k < 3; k++) {
            //Paso 15: encontrar l en la lista de nodos

            int l = findNodeIndex(Nodesi[k]); //Encontramos el indice l en la lista de todos los nodos en S1US2
            //Paso 16:
            if (k > 0) { //If k != 0
                for (int j = 0; j < k - 1; j++) { // j =0,1...k-1

                    //Paso 17: encontrar t
                    int t = findNodeIndex(Nodesi[j]);

                    //Paso 18:
                    if (l < n) {
                        if (t < n) {
                            alpha[l][t] = alpha[l][t] + J[i - K][k][j];
                            alpha[t][l] = alpha[t][l] + J[i - K][k][j];
                        }
                        else {
                            beta[l] = beta[l] - gamma[t] * J[i - K][k][j];
                        }
                    }
                    else if (t < n) {
                        beta[t] = beta[t] - gamma[l] * J[i - K][k][j];
                    }
                }
            }
            //Paso 19:
            if (l < n) {
                alpha[l][l] = alpha[l][l] + J[i - K][k][k];
                beta[l] = beta[l] + I[i - K][k];
            }
        }
    }

} //Fin :D

//función que soluciona usando todos los pasos 
void FEM::solve()
{
    coefABC();
    doubleIntegrals();
    assembleDoubleIntegrals();
    lineIntegrals();
    assembleLineIntegrals();
    //---------------STEP 20---------------
    vector<double> gamma2 = la.gaussianElimination(alpha, beta);

    for (int i = 0; i < n; i++) {
        gamma[i] = gamma2[i];
    }

    ofstream resultsFile("dat/Results.dat");

    if (resultsFile.fail()) {
        cout << "Results file cannot be opened." << endl;
        exit(1);
    }
    //---------------STEP 21-22---------------
    for (int i = 0; i < M; i++) {
        vector<Point> vtx = Triangles[i].getVertices();
        for (int j = 0; j < 3; j++) {
            int m = findNodeIndex(vtx[j]);
            resultsFile << A[i][j] << " " << B[i][j] << " " << C[i][j] << " " << gamma[m] << endl;
        }
    }
    triang.saveTriangles(Triangles, "dat/Triangles.dat");

    triang.saveNodes(Nodes, "dat/Nodes.dat");
}
