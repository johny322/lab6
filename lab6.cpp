#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;

double function(double x1, double x2) {
	return pow(x1, 3) - 3 * pow(x1, 2) + pow(x2, 2) + 4 * x2 + 9;
}

double fir_derivative_x1(double x1, double x2) {
    return 3 * pow(x1, 2) - 6 * x1;
}

double fir_derivative_x2(double x1, double x2) {
    return 2 * x2 + 4;
}

double sec_derivative_x1(double x1, double x2) {
    return 6 * x1 - 6;
}

double sec_derivative_x2(double x1, double x2) {
    return 2;
}

double sec_derivative_x1_x2(double x1, double x2) {
    return 0;
}

void ober_matr(double a[2][2])
{
    double det, aa;
    det = a[0][0] * a[1][1] - a[0][1] * a[1][0];
    aa = a[0][0];
    a[0][0] = a[1][1] / det;
    a[1][1] = aa / det;
    aa = a[0][1];
    a[0][1] = -a[0][1] / det;
    a[1][0] = -a[1][0] / det;
}


void swenn_x1(double &h, double a[2], double &x)
{
    
    a[1] = a[0] + h;
    if (function(a[1], x) > function(a[0], x))
    {
        h = -h;
        a[1] = a[0] + h;
    }
    while (function(a[1], x) < function(a[0], x))
    {
        a[0] = a[1];
        a[1] = a[0] + h;
        h = h * 2;
    }
}

void swenn_x2(double &h, double b[2], double &x)
{
    b[1] = b[0] + h;
    if (function(x, b[1]) > function(x, b[0]))
    {
        h = -h;
        b[1] = b[0] + h;
    }
    while (function(x, b[1]) < function(x, b[0]))
    {
        b[0] = b[1];
        b[1] = b[0] + h;
        h = h * 2;
    }
}

void alfa_x1(double &alfa, double a0, double a1, double x_const) {
    double c;
    double x1, x2, x3, x_min, x_, dx, e;
    double f1, f2, f3, f_min, f_, F;
    if (a1 < a0) { c = a1; a1 = a0; a0 = c; }
    dx = 0.01; // прирощение
    e = 0.0001; //точность
    x1 = a0;
    do {
        x2 = x1 + dx;
        f1 = function(x1, x_const);
        f2 = function(x2, x_const);
        if (f1 > f2) { x3 = x1 + 2 * dx; }
        else if (f1 <= f2) { x3 = x1 - dx; }
        f3 = function(x3, x_const);
        f_min = min(f1, f2);
        f_min = min(f_min, f3);
        if (f_min == f1) { x_min = x1; }
        else if (f_min == f2) { x_min = x2; }
        else if (f_min == f3) { x_min = x3; }
        x_ = ((x2 * x2 - x3 * x3) * f1 + (x3 * x3 - x1 * x1) * f2 + (x1 * x1 - x2 * x2) * f3) /
            (((x2 - x3) * f1 + (x3 - x1) * f2 + (x1 - x2) * f3) * 2);
        f_ = function(x_, x_const);
        if ((((x2 - x3) * f1 + (x3 - x1) * f2 + (x1 - x2) * f3) * 2) == 0) {
            x1 = x_min; continue; 
        }
        if (fabs(((f_min - f_)) >= e )|| (fabs((x_min - x_)) >= e)) {
            if ((x_ < x1) || (x_ > x3)) { x1 = x_; continue; }
            else if ((x_ >= x1) && (x_ <= x3)) {
                F = min(f_min, f_);
                if (F == f_min) { x1 = x_min; continue; }
                else if (F == f_) { x1 = x_; continue; }
            }
        }
        
    } while ((fabs(f_min - f_)  >= e) && (fabs(x_min - x_) >=e));
    alfa = x_;
}
void alfa_x2(double &alfa, double b0, double b1, double x_const) {
    double c;
    double x1, x2, x3, x_min, x_, dx, e;
    double f1, f2, f3, f_min, f_, F;
    if (b1 < b0) { c = b1; b1 = b0; b0 = c; }
    dx = 0.01; // прирощение
    e = 0.0001; //точность
    x1 = b0;
    do {
        x2 = x1 + dx;
        f1 = function(x_const, x1);
        f2 = function(x_const, x2);
        if (f1 > f2) { x3 = x1 + 2 * dx; }
        else if (f1 <= f2) { x3 = x1 - dx; }
        f3 = function(x_const, x3);
        f_min = min(f1, f2);
        f_min = min(f_min, f3);
        if (f_min == f1) { x_min = x1; }
        else if (f_min == f2) { x_min = x2; }
        else if (f_min == f3) { x_min = x3; }
        x_ = ((x2 * x2 - x3 * x3) * f1 + (x3 * x3 - x1 * x1) * f2 + (x1 * x1 - x2 * x2) * f3) /
            (((x2 - x3) * f1 + (x3 - x1) * f2 + (x1 - x2) * f3) * 2);
        f_ = function(x_, x_const);
        if ((((x2 - x3) * f1 + (x3 - x1) * f2 + (x1 - x2) * f3) * 2) == 0) {
            x1 = x_min; continue;
        }
        if (fabs(((f_min - f_)) >= e) || (fabs((x_min - x_)) >= e)) {
            if ((x_ < x1) || (x_ > x3)) { x1 = x_; continue; }
            else if ((x_ >= x1) && (x_ <= x3)) {
                F = min(f_min, f_);
                if (F == f_min) { x1 = x_min; continue; }
                else if (F == f_) { x1 = x_; continue; }
            }
        }
        

    } while ((fabs(f_min - f_) >= e) && (fabs(x_min - x_) >= e));
    alfa = x_;
}

double proizv(double gessian[2][2], double gradient[2], double p[2]) {
    
    p[0] = gessian[0][0] * gradient[0] + gessian[0][1] * gradient[1];
    p[1] = gessian[1][0] * gradient[0] + gessian[1][1] * gradient[1];
    return p[1], p[0];
}


int main() {
    fstream f;
    int count = 0;
    double a0, a1, b0, b1;
    double x[2], gradient[2], gessian[2][2], p[2], a[2], b[2], h;
    double x1, x2, x11 = 0, x22 = 0, det_grad, alfa, alfa1, alfa2;
    alfa = 1.0;
    h = 0.1;
    
    x[0] = 1.5;  x[1] = 5;
    
    x1 = x[0]; x2 = x[1];
    
    gessian[0][0] = sec_derivative_x1(x1, x2);
    gessian[0][1] = sec_derivative_x1_x2(x1, x2);
    gessian[1][0] = gessian[0][1];
    gessian[1][1] = sec_derivative_x2(x1, x2);
    ober_matr(gessian);
    gradient[0] = fir_derivative_x1(x1, x2);
    gradient[1] = fir_derivative_x2(x1, x2);
    
    det_grad = sqrt(gradient[0] * gradient[0] + gradient[1] * gradient[1]);
    f.open("vec_p.txt", ios::out);
    
    proizv(gessian, gradient, p);
    

    double e = 0.25, u = 0.5, proizv_grad_and_p;
    double func1, func2;  //левая и правая части неравенства
    proizv_grad_and_p = fir_derivative_x1(x1, x2) * p[0] + fir_derivative_x2(x1, x2) * p[1];
    func1 = function(x1 + alfa * p[0], x2 + alfa * p[1]);
    func2 = function(x1, x2) + e * alfa * proizv_grad_and_p;
    
    while (det_grad > 0.0001)
    { 
        alfa = 1;
        h = 0.1;
        a[0] = x1;
        b[0] = x2;
        swenn_x1(h, a, x2);
        swenn_x2(h, b, x1);
        cout << "a: " << a[0] << "   " << a[1] << endl;
        cout << "b: " << b[0] << "   " << b[1] << endl;
        
        
        gessian[0][0] = sec_derivative_x1(x1, x2);
        gessian[0][1] = sec_derivative_x1_x2(x1, x2);
        gessian[1][0] = gessian[0][1];
        gessian[1][1] = sec_derivative_x2(x1, x2);
        
        ober_matr(gessian);

        gradient[0] = fir_derivative_x1(x1, x2);
        gradient[1] = fir_derivative_x2(x1, x2);

        det_grad = sqrt(gradient[0] * gradient[0] + gradient[1] * gradient[1]);
        
        proizv(gessian, gradient, p);
        
        if (f) {
            f << x1 << "     " << x2 << endl;// "   " << "a:" << a[0] << " " << a[1] << "    " << "b:" << b[0] << " " << b[1] << "  p " << p[0] << " " << p[1] << endl;
        }


        while (func1 > func2) {
            alfa = alfa * u;
            func1 = function(x1 + alfa * p[0], x2 + alfa * p[1]);
            func2 = function(x1, x2) + e * alfa * proizv_grad_and_p;
            break;
        }
        

        a0 = a[0]; a1 = a[1];
        alfa_x1(alfa1, a0, a1, x2);
        //alfa1 = alfa;
        x11 = x1 - alfa * p[0];
        
        b0 = b[0]; b1 = b[1];
        alfa_x2(alfa2, b0, b1, x1);
        //alfa2 = alfa;
        x22 = x2 - alfa * p[1];
        
        x1 = x11; 
        
        x2 = x22;
        
        
        count++;
    }
    f.close();
    cout << "x1 = " << x1 << "    " << "x2 = " << x2 << endl;
    cout << "alfa1 = " << alfa1 << "    " << "alfa2 = " << alfa2 << endl << "iterations = " << count << endl;
    
    return 0;
    

}