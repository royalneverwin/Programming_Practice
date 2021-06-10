#include <iostream>
using namespace std;


int t;
int r,c;
char Map[510][510];


void Change(int i, int j){
    Map[i][j] = 'M';
    if(i != 1 && Map[i-1][j] == 'O'){
        Change(i-1, j);
    }
    if(i != r && Map[i+1][j] == 'O'){
        Change(i+1, j);
    }
    if(j != 1 && Map[i][j-1] == 'O'){
        Change(i, j-1);
    }
    if(j != c && Map[i][j+1] == 'O'){
        Change(i, j+1);
    }
}


int main(){
    cin >> t;
    while(t--){
        cin >> r >> c;
        for(int i = 1; i <= r; i++){
            for(int j = 1; j <= c; j++){
                cin >> Map[i][j];
            }
        }
        for(int i = 1; i <= r; i++){
            if(Map[i][1] == 'O'){
                Change(i, 1);
            }
            if(Map[i][c] == 'O'){
                Change(i, c);
            }
        }
        for(int j = 1; j <= c; j++){
            if(Map[1][j] == 'O'){
                Change(1, j);
            }
            if(Map[r][j] == 'O'){
                Change(r, j);
            }
        }
        for(int i = 1; i <= r; i++){
            for(int j = 1; j <= c; j++){
                if(Map[i][j] == 'O'){
                    Map[i][j] = 'X';
                } else if(Map[i][j] == 'M'){
                    Map[i][j] = 'O';
                }
            }
        }
        for(int i = 1; i <= r; i++){
            for(int j = 1; j <= c; j++){
                cout << Map[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}