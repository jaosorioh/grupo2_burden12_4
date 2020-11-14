#include "include/Triangulation.h"
#include <algorithm>
#include <iostream>
#include "include/linearalgebra.cpp"
//prototipos

using namespace std;

int findNodeIndex(vector<Point>& nodes, Point& p);
//step 4-Nicole
void doubleIntegrals(Triangle& triangles, vector<vector<vector<double> > >& Z, vector<vector<double> >& H);

//step 5-Nicole
void lineIntegrals(Triangle& trianglesS2, vector<vector<vector<double> > >& J, vector<vector<double> >& I);

//step 6-12-Brayan
void assembleDoubleIntegrals1( vector<Triangle> T, vector<Point>& nodes, vector<Point>& nodesS2, vector<vector<double>>& alpha, vector<double>& beta, vector<double>& gamma, vector<vector<vector<double>>>& Z, vector<vector<double>>& H);

/* Función del paso 6-12
INPUT: Vector de triángulos que alberga todos los triángulos, vector de nodos, vector de nodos en S2, alfa, beta, gamma, Z, H.
OUTPUT: vacía, solo llena los alfa y beta */
void assembleDoubleIntegrals1( vector<Triangle> T, vector<Point>& nodes, vector<Point>& nodesS2, vector<vector<double>>& alpha, vector<double>& beta, vector<double>& gamma, vector<vector<vector<double>>>& Z, vector<vector<double>>& H)
{	
	//Paso 6: correr sobre todos los triangulos
	int Mt = T.size();	//Numero total de triángulos, el primer for va hasta aquí
	for(int i = 0; i<=Mt; i++)
	{	
		vector<Point> Nodesi = {T[i].getE1.(),T[i].getE2,T[i].getE3()}; //Los 3 Nodos del triángulo i
		int m = nodes.size();
		int n = nodesS2.size();
		
		//Paso 7: correr k = 1,2,3 (En nuestro caso 0,1,2)
		for(int k=0;k<3;k++)
		{	
			//Paso 8: Encontramos el indice l en la lista de todos los nodos en S1US2
			Point p1 = Nodesi[k];
			int l = findNodeIndex(nodes, p1);

			//Paso 9:
			if(k>0){				//If k != 0
				for(int j=0;j < k;j++){		// j =0,1...k-1

					//Paso 10:
					Point p2 = Nodesi[j];
					int t = findNodeIndex(nodes, p2);

					//Paso 11:
					if(l<=n){
						if(t<=n){ alpha[l][t] = alpha[l][t] + Z[i][k][j];
							alpha[t][l] = alpha[t][l] + Z[i][k][j];
							}
						else{beta[l] = beta[l] - gamma[l]*Z[i][k][j];}
						}
					else if(t<=n){beta[t] = beta[t] - gamma[l]*Z[i][k][j];}
							}
				//Paso 12:
				if(l<=n){a[l][l] = alpha[l][l] + Z[i][k][k];
					beta[l] = beta[l] + H[i][k];}
				}
		}
	}

}//Fin :D

//step 13-19-Brayan
void assembleDoubleIntegrals2(vector<Triangle>& TS2, vector<vector<double> >& alpha, vector<double>& beta, vector<double>& gamma, vector<vector<vector<double>>>& J, vector<vector<double> >& I);

/* Función del paso 13-19
INPUT: Los triángulos que tienen  al menos un nodo en S2, alfa, beta, gamma, J, I.
OUTPUT: vacía, solo llena los alfa y beta */
void assembleDoubleIntegrals2(vector<Triangle>& TS2, vector<vector<double> >& alpha, vector<double>& beta, vector<double>& gamma, vector<vector<vector<double>>>& J, vector<vector<double> >& I)
{
	//Paso 13: correr sobre los triangulos con al menos un edge en S2
	int K = TS2.size()	//Triángulos con al menos un edge en S2, sobre esto corre el for
	for(int i = 0; i<=K; i++)
	{
		vector<Point> Nodesi = {T[i].getE1.(),T[i].getE2,T[i].getE3()}; //Los 3 Nodos del triángulo i

		//Paso 14: correr sobre k = 1,2,3 (0,1,2 en nuestro caso)
		for(int k = 0; k<3; k++)
		{
			//Paso 15: encontrar l en la lista de nodos
			Point p1 = Nodesi[k];
			int l = findNodeIndex(nodes, p1);	//Encontramos el indice l en la lista de todos los nodos en S1US2

			//Paso 16:
			if(k>0){				//If k != 0
				for(int j=0;j < k;j++){		// j =0,1...k-1

					//Paso 17: encontrar t
					Point p2 = Nodesi[j];
					int t = findNodeIndex(nodes, p2);

					//Paso 18:
					if(l<=n){
						if(t<=n){ alpha[l][t] = alpha[l][t] + J[i][k][j];
							alpha[t][l] = alpha[t][l] + J[i][k][j];
							}
						else{beta[l] = beta[l] - gamma[l]*J[i][k][j];}
						}
					else if(t<=n){beta[t] = beta[t] - gamma[l]*J[i][k][j];}
							}

				//Paso 19:
				if(l<=n){alpha[l][l] = alpha[l][l] + J[i][k][k];
					beta[l] = beta[l] + I[i][k];}
				}
		}
	}


}//Fin :D

//Calcula los vectores a, b, c del triángulo i
void coefABC(Triangle& T, vector<double>& a, vector<double>& b, vector<double>& c)
{
    double x1, x2, x3, y1, y2, y3;
    x1 = T.getE1().getX();
    y1 = T.getE1().getY();
    x2 = T.getE2().getX();
    y2 = T.getE2().getY();
    x3 = T.getE3().getX();
    y3 = T.getE3().getY();

    vector<vector<double>> matrix= { { 1.0, x1, y1 },
        { 1.0, x2, y2 },
        { 1.0, x3, y3 } };
     

    double delta = det(matrix);
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
void coefABC(vector<Triangle> triangles, vector<vector<double> >& A, vector<vector<double> >& B, vector<vector<double> >& C)
{
    for (int i = 0; i < triangles.size(); i++) {
        vector<double> a;
        vector<double> b;
        vector<double> c;
        coefABC(triangles.at(i), a, b, c);
        A.push_back(a);
        B.push_back(b);
        C.push_back(c);
    }
}

//N_i, recibe a, b, c y además x e y
vector<double> Ni(vector<double>& a, vector<double>& b, vector<double>& c, double x, double y)
{
    vector<double> N = {};
    for (int i = 0; i < 3; i++) {
        N.push_back(a[i] + b[i] * x + c[i] * y);
    }
    return N;
}

//Todo en una sola (sobrecargo de la función Ni anterior)
/*vector<double> Ni(Triangle T, double x, double y)
{
    double delta = DeltaT(T);
    vector<double> a = coef_a(T, delta);
    vector<double> b = coef_b(T, delta);
    vector<double> c = coef_c(T, delta);
    vector<double> N = Ni(a, b, c, x, y);
    return N;
}*/

//step 8, 10, 15, 17
int findNodeIndex(vector<Point>& nodes, Point& p)
{
    int i = 0;
    while (i < nodes.size()) {
        if (p.getX() == nodes.at(i).getX() && p.getY() == nodes.at(i).getY())
            break;
        i++;
    }
    if (i == nodes.size())
        i = -1;
    return i;
}

void solve(double* (*S2Fx)(const double&, double&), double* (*S2Fy)(double&, const double&), double (*g)(const double&, const double&), vector<double>& x_i, vector<double>& y_i, int& N, int& M)
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
    t.multi_linspace(x_i, N, x);
    t.multi_linspace(y_i, M, y);

    t.buildTrianglesAndNodes(trianglesS1, trianglesS2, trianglesnotS1S2, nodesS1, nodesS2, S2Fx, S2Fy, x, y);
    string fname = "dat/S1Triangles.dat";
    t.saveTriangles(trianglesS1, fname);
    fname = "dat/S2Triangles.dat";
    t.saveTriangles(trianglesS2, fname);
    fname = "dat/NotS1S2Triangles.dat";
    t.saveTriangles(trianglesnotS1S2, fname);

    fname = "dat/nodesS1.dat";
    t.saveNodes(nodesS1, fname);
    fname = "dat/nodesS2.dat";
    t.saveNodes(nodesS2, fname);

    const int n = nodesS1.size();
    const int m = nodesS2.size();
    //step 1
    vector<double> gammaS1;

    for (int i = 0; i < n - 1; i++) {
        gammaS1.push_back(g(nodesS1.at(i).getX(), nodesS1.at(i).getY()));
    }
    //step 2

    vector<vector<double> > alpha(n, vector<double>(n, 0));
    vector<double> beta(n, 0);
    
    //step 3
    
    vector<vector<double>> A;
    vector<vector<double>> B;
    vector<vector<double>> C;
    
    coefABC(trianglesnotS1S2, A, B, C);    
}
