#include <iostream>
#include <cmath>
using namespace std;


char Square[1025][2049];


void BuildSquare(int x, int y, int size){// 构造size维的三角形，三角形的左下角为(x, y)
    if(size == 1){
        Square[x][y] = '/';
        Square[x][y+1]  = Square[x][y+2] = '_';
        Square[x][y+3] = '\\';
        Square[x-1][y+1] = '/';
        Square[x-1][y+2] = '\\';
    } else{
        int lengthx = pow(2, size - 1);
        int lengthy = pow(2, size);

        BuildSquare(x, y, size - 1);
        BuildSquare(x, y + lengthy, size - 1);
        BuildSquare(x - lengthx, y + lengthy / 2, size - 1);
    }
}

int main(){
    int n;
    cin >> n;
    while(n){
        int lengthx = pow(2, n);
        int lengthy = pow(2, n+1);
        for(int i = 1; i <= lengthx; i++){
            for(int j = 1; j <= lengthy; j++){
                Square[i][j] = ' ';
            }
        }
        BuildSquare(lengthx, 1, n);
        for(int i = 1; i <= lengthx; i++){
            for(int j = 1; j <= lengthy; j++){
                cout << Square[i][j];
            }
            cout << endl;
        }
        cin >> n;
        if(n != 0){
            cout << endl;
        }
    }
    return 0;
}