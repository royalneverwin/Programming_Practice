#include <iostream>
using namespace std;
int a[5][5];
bool ifRight(int x, int y){
    int tmp = a[x][y];
    for(int j = 0; j < 5; j++){
        if(a[x][j] > tmp)
            return false;
        if(a[j][y] < tmp)
            return false;
    }
    return true;
}
int main(){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cin >> a[i][j];
        }
    }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(ifRight(i, j)){
                cout << i+1 << ' ' << j+1 << ' ' << a[i][j] << endl;
                return 0;
            }
        }
    }
    cout << "not found" << endl;
    return 0;
}