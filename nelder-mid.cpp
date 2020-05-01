#include <iostream>
#include <stdlib.h>
#include <math.h>
// #include <conio.h>
#define n  2
using namespace std;
double f (double x1, double x2) {
   return pow(x1, 3) - 3 * pow(x1, 2) + pow(x2, 2) + 4 * x2 + 9;
}

int main () {
   const double eps = 0.0001;
   double x[n + 5][n];
   double s;

   x[0][0] = -1;  x[0][1] = 5;
   x[1][0] = 0; x[1][1] = 1;
   x[2][0] = 1; x[2][1] = 1;

    
   int h, l, g;
   long int kol = 0;

   cout<<x[0][0]<<"      "<<x[0][1]<<endl;
   cout<<x[1][0]<<"      "<<x[1][1]<<endl;
   cout<<x[2][0]<<"      "<<x[2][1]<<endl;
   cout<<"_________________________________"<<endl;

   do {
   kol++;

   h = 0;
   l = 0;
   g = 0;
   double max = f(x[0][0], x[0][1]);
   double min = f(x[0][0], x[0][1]);
   for (int k = 1; k <= n; k ++) {
   if (f(x[k][0], x[k][1]) < min) {
   min = f(x[k][0], x[k][1]);
   l = k;
   }
   if (f(x[k][0], x[k][1]) > max) {
   max = f(x[k][0], x[k][1]);
   h = k;
   }
   }

   max = f(x[0][0], x[0][1]);

   for (int k = 1; k <= n; k ++) {
   if ((f(x[k][0], x[k][1]) > max) && (k != h)) {
   max = f(x[k][0], x[k][1]);
   g = k;
   }
   }

   x[n + 1][0] = (x[0][0] + x[1][0] + x[2][0] - x[h][0]) / n;
   x[n + 1][1] = (x[0][1] + x[1][1] + x[2][1] - x[h][1]) / n;


   for (int i = 0; i < n; i++)
   x[n + 2][i] = 2 * x[n + 1][i] - x[h][i];

   if (f(x[n + 2][0], x[n + 2][1]) < f(x[l][0], x[l][1])) {
   x[n + 3][0] = x[n + 1][0] + 2 * (x[n + 2][0] - x[n + 1][0]);
   x[n + 3][1] = x[n + 1][1] + 2 * (x[n + 2][1] - x[n + 1][1]);

   if (f(x[n + 3][0], x[n + 3][1]) < f(x[l][0], x[l][1])) {
   x[h][0] = x[n + 3][0];
   x[h][1] = x[n + 3][1];
   }
   else {
   x[h][0] = x[n + 2][0];
   x[h][1] = x[n + 2][1];
   }
   }

   else
   if (f(x[n + 2][0], x[n + 2][1]) > f(x[g][0], x[g][1])) {
   if (!(f(x[n + 2][0], x[n + 2][1]) > f(x[h][0], x[h][1]))) {
   x[h][0] = x[n + 2][0];
   x[h][1] = x[n + 2][1];
   }
   x[n + 4][0] = x[n + 1][0] + 0.5 * (x[h][0] - x[n + 1][0]);
   x[n + 4][1] = x[n + 1][1] + 0.5 * (x[h][1] - x[n + 1][1]);
   if (!(f(x[n + 4][0], x[n + 4][1]) > f(x[h][0], x[h][1]))) {
   x[h][0] = x[n + 4][0];
   x[h][1] = x[n + 4][1];
   }
   else {
   for (int k = 0; k < n; k++) {
   x[k][0] = x[k][0] + 0.5 * (x[k][0] - x[l][0]);
   x[k][1] = x[k][1] + 0.5 * (x[k][1] - x[l][1]);
   }
   }
   }
   else {
   x[h][0] = x[n + 2][0];
   x[h][1] = x[n + 2][1];
   }

   float s1 = 0, s2 = 0;
   for (int k = 0; k < n + 1; k++) {
   s1 += f(x[k][0], x[k][1]);
   s2 += f(x[k][0], x[k][1]) * f(x[k][0], x[k][1]);
   }
   s = s2 - s1 * s1 / (n + 1);
   s /= (n + 1);

   cout<<x[0][0]<<"      "<<x[0][1]<<endl;
   cout<<x[1][0]<<"      "<<x[1][1]<<endl;
   cout<<x[2][0]<<"      "<<x[2][1]<<endl;
   min = f(x[0][0], x[0][1]);
   for (int k = 1; k <= n; k++) {
   if (f(x[k][0], x[k][1]) < min) {
   min = f(x[k][0], x[k][1]);
   l = k;
   }
   }
   cout<<"f = " <<f(x[l][0], x[l][1])<<endl;
   cout<<"___________________"<<endl;


   } while (s > eps);

   cout << "x1 = " << x[n + 1][0] << endl;
   cout << "x2 = " << x[n + 1][1] << endl;
   cout << "minF = " << f(x[n + 1][0], x[n + 1][1]) << endl;
   cout << "iterations = " << kol;

}
