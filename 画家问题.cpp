#include <iostream>
#include <string>
using namespace std;



int map[16];
int copyMap[16];


int changeWay = 0;


void Flip(int &num, int pos){
    num ^= 1 << pos;
}


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int n;
    string row;
    cin >> n;
    for(int i = 0; i < n ;i++){
        cin >> row;
        map[i] = 0;
        for(int j = 0; j < n; j++){
            if(row[j] == 'y')
                map[i] += 1 << j;
        }
    }
    int max = 1 << n;
    int minCnt = (1 << 31) - 1;
    while(changeWay < max){
        int curWay;
        int curCnt = 0;
        for(int i = 0; i < n; i++){
            copyMap[i] = map[i];
        }
        for(int i = 0; i < n; i++) {
            if(i == 0){
                curWay = changeWay;
            }
            for (int j = 0; j < n; j++) {
                if((curWay >> j) & 1){
                    curCnt++;
                    Flip(copyMap[i], j);
                    if(i != n-1)
                        Flip(copyMap[i+1], j);
                    if(j != 0)
                        Flip(copyMap[i], j-1);
                    if(j != n-1)
                        Flip(copyMap[i], j+1);
                }
            }
            if(i != n-1) {
                curWay = ~copyMap[i] & (max - 1);
            }
        }
        if(copyMap[n-1] == max - 1){
            if(curCnt < minCnt){
                minCnt = curCnt;
            }
        }
        changeWay++;
    }
    if(minCnt != (1 << 31) - 1){
        cout << minCnt << endl;
    } else{
        cout << "inf" << endl;
    }
}