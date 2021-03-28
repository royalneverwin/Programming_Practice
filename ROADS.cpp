#include <iostream>
#include <vector>
#include <cstring>
using namespace std;


int K, N, R;
struct Road{
    int d, L, t;
};

vector<vector<Road>> G(110);
int minLen;
int totalLen;
int totalCost;
int visited[110];

/*
普通深搜，很容易会TLE。需要进行改进，进行所谓的"剪枝"！
void dfs(int s){
    if(s == N){
        minLen = min(minLen, totalLen);
        return;
    }
    for(int i = 0; i < G[s].size(); i++){
        Road r = G[s][i];
        if(totalCost + r.t > K){//如果走到他花费大于K，不走，可行性剪枝
            continue;
        }
        if(!visited[r.d]){//如果destination已经走过了，不走
            totalLen += r.L;
            totalCost += r.t;
            visited[r.d] = 1;
            dfs(r.d);
            visited[r.d] = 0;
            totalLen -= r.L;
            totalCost -= r.t;
        }
    }
}
*/


//进行最优性剪枝
int minL[110][10010];//记录走到城市k时恰好花费m的最短路径




void dfs(int s){
    if(s == N){
        minLen = min(minLen, totalLen);
        return;
    }
    for(int i = 0; i < G[s].size(); i++){
        Road r = G[s][i];
        if(totalCost + r.t > K){//如果走到他花费大于K，不走，可行性剪枝
            continue;
        }
        if(!visited[r.d]){//如果destination已经走过了，不走
            if(totalLen + r.L >= minLen){//最优性剪枝，即使能走到也不是最优路径了
                continue;
            }
            if(totalLen + r.L >= minL[r.d][totalCost + r.t]){//更强的最优性剪枝，到达r.d且花费totalCost + r.t 的总长度已经超过最短路径
                continue;
            }
            minL[r.d][totalCost+r.t] = totalLen + r.L;
            totalLen += r.L;
            totalCost += r.t;
            visited[r.d] = 1;
            dfs(r.d);
            visited[r.d] = 0;
            totalLen -= r.L;
            totalCost -= r.t;
        }
    }
}



int main(){
    cin >> K >> N >> R;
    for(int i = 0; i < R; i++){
        int s;
        Road r;
        cin >> s >> r.d >> r.L >> r.t;
        if(s != r.d){//当source不等于destination时才需要把边加到邻接表中
            G[s].push_back(r);
        }
    }
    memset(visited, 0, sizeof(visited));
    totalLen = 0;
    minLen = 1 << 10;
    totalCost = 0;
    visited[1] = 1;//从城市1开始
    for(int i = 0; i < 110; i++){
        for(int j = 0; j < 10010; j++){
            minL[i][j] = 1 << 10;
        }
    }
    dfs(1);//找路
    if(minLen < (1 << 10)){
        cout << minLen << endl;
    }
    else{
        cout << -1 << endl;
    }
    return 0;
}