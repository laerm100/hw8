#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>

using namespace std;


typedef struct Vektor
{
double x; // 1
double y; // 2
} 
Vektor;

double dHdpx(Vektor p, Vektor q);
double dHdpy(Vektor p, Vektor q);

double dHdqx(Vektor p, Vektor q);
double dHdqy(Vektor p, Vektor q);

double H(Vektor p, Vektor q);


int main(void)
{

 Vektor p,q;
 double e = 0.6;

 p.x = 0.0;
 p.y = sqrt((1.0+e)/(1.0-e));

 q.x = 1.0 - e;
 q.y = 0.0;


 const double dt = 0.0005;  // dt=0.05
 const double tEnd = 20.0*M_PI;
 double t = 0.0;

 ofstream Datei("Kepler.dat");

 Datei << t << '\t' << H(p,q) << '\t' << q.x << '\t' << q.y << '\t' << endl;

 for (t = 0.0; t <= tEnd; t += dt)
 {
 p.x = p.x - dt*dHdqx(p,q); //nach der Ableitung ist die Fkt. nicht mehr von p abhängig
 p.y = p.y - dt*dHdqy(p,q);

 q.x = q.x + dt*dHdpx(p,q);
 q.y = q.y + dt*dHdpy(p,q);

 Datei << t << '\t' << H(p,q) << '\t' << q.x << '\t' << q.y << '\t' << endl;
 }
 Datei.close();
 exit(0);
}

double H(Vektor p, Vektor q)
{
 return 0.5*(p.x*p.x + p.y*p.y)-1.0/(sqrt(q.x*q.x + q.y*q.y));
}

double dHdqx(Vektor p, Vektor q)
{
 return q.x*pow(q.x*q.x + q.y*q.y, -1.5);
}

double dHdqy(Vektor p, Vektor q)
{
 return q.y*pow(q.x*q.x + q.y*q.y,-1.5);
}

double dHdpx(Vektor p, Vektor q)
{
 return p.x;
}

double dHdpy(Vektor p, Vektor q)
{
 return p.y;
} 