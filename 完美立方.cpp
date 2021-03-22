#include <iostream>
using namespace std;


int Cube(int a){
    return a*a*a;
}

//a, b, c, d都 >= 2
int main() {
    int N;
    cin >> N;
    for(int i = 3; i <= N; i++){//a，一定大于2
        for(int j = 2; j <= i-1; j++){//b，一定比a小
            for(int k = j; k <= i-1; k++){//c，一定比a小且不比b小
                for(int h = k; h <= i-1; h++){//d，一定比a小且不比c小
                    if(Cube(i) == Cube(j) + Cube(k) + Cube(h)){
                        cout << "Cube = " << i << ", " << "Triple = (" << j << ", " << k << ", " << h << ")\n";
                    }
                }
            }
        }
    }
    return 0;
}