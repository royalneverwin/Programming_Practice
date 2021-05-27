#include <iostream>
using namespace std;


int main(){
    int n;
    cin >> n;
    int h;
    int sum = 6 * n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n / i; j++){
            if(n % (i*j) != 0){
                continue;
            }
            h = n / (i * j);
            sum = min(sum, 2 * i * j + 2 * i * h + 2 * j * h);
        }
    }
    cout << sum << endl;
}