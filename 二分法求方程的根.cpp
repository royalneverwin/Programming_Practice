#include <iostream>
using namespace std;


const double EPS = 1E-6;

inline double f(double x){
    return x*x*x -5*x*x + 10*x -80;
}


//二分法求x^3-5x^2+10x-80的根
int main(){
    double root, x1 = 0, x2 = 100, y;
    root = x1 + (x2-x1)/2;
    int triedTime = 1;
    y = f(root);
    while(fabs(y) > EPS){
        if(y > 0)
            x2 = root;
        else
            x1 = root;
        root = x1 + (x2-x1)/2;
        y = f(root);
        triedTime++;
    }
    printf("%.8f\n", root);
    printf("%d\n", triedTime);
    return 0;
}