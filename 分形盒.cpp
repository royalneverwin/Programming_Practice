#include <iostream>
#include <cstring>
using namespace std;


char Map[800][800];


void Build(int dim, int x, int y){
    if(dim == 1){
        Map[x][y] = 'X';
        return;
    }
    int size = 1;
    for(int i = 2; i <= dim-1; i++){
        size *= 3;
    }
    Build(dim-1, x, y);
    Build(dim-1, x + 2*size, y);
    Build(dim-1, x + size, y + size);
    Build(dim-1, x, y + 2*size);
    Build(dim-1, x + 2*size, y + 2*size);
}


int main(){
    int n;
    cin >> n;
    while(n != -1){
        memset(Map, 0x20, sizeof(Map));
        Build(n, 1, 1);
        int size = 1;
        for(int i = 2; i <= n; i++){
            size *= 3;
        }
        for(int i = 1; i <= size; i++){
            for(int j = 1; j <= size; j++){
                cout << Map[i][j];
            }
            cout << endl;
        }
        cout << '-' << endl;
        cin >> n;
    }
}