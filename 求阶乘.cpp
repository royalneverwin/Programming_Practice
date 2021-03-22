#include <iostream>
using namespace std;


int Factorial(int n){
    if(n == 0){
        return 1;
    }
    else{
        return n * Factorial(n-1);
    }
}


int main(){
    int n;
    cin >> n;
    cout << Factorial(n);
    return 0;
}
