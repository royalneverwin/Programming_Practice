#include <iostream>
#include <cstring>
using namespace std;


int Map[17][17];
int n;
int totalTime[17][1 << 16]; //状态为totalTime[i][j]时所用的最短时间
int ans;


void F(int pos, int state){
    for(int i = 0; i < n; i++){
        if(i == pos)
            continue;
        if(pos == n-1) //走到终点
            return;
        if(((1 << i) & state ) != 0) //已经走过了
            continue;
        if(totalTime[i][state | (1 << i)] == 0 || totalTime[pos][state] + Map[pos][i] < totalTime[i][state | (1 << i)]) {
            totalTime[i][state | (1 << i)] = totalTime[pos][state] + Map[pos][i];
//            cout << pos << ' ' << i << ' ' << totalTime[i][state | (1 << i)] << endl;
            F(i, state | (1 << i));
        }
    }
}


int main(){
    cin >> n;
    memset(totalTime, 0, sizeof(totalTime));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> Map[i][j];
        }
    }
    F(0, 1);
    cout << totalTime[n-1][(1 << n)-1];
    return 0;
}