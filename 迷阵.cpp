#include <iostream>
#include <cstring>
#include <queue>
using namespace std;


struct me{
    int x;
    int y;
    int h;
    int cnt;
    me(int xx, int yy, int hh, int c):x(xx), y(yy), h(hh), cnt(c){}
};

queue<me> qm;
int t;
int m, n, h;
char Map[260][260];
bool flag[260][260][6]; //代表这个状态有没有走到


void AddNew(int x, int y, me pre){ //看看是否能增加新节点进queue
    if(Map[x][y] != '#'){ //不是墙
        if(Map[x][y] == '*'){ //被神兽攻击
            if(pre.h == 1) //会死
                return;
            if(flag[x][y][pre.h-1]) //这个状态已经遍历过了
                return;
            flag[x][y][pre.h-1] = true;
            qm.push(me(x, y, pre.h-1, pre.cnt + 1));
        }
        else{
            if(flag[x][y][pre.h]) //这个状态已经遍历过了
                return;
            flag[x][y][pre.h] = true;
            qm.push(me(x, y, pre.h, pre.cnt + 1));
        }
    }
}

void bfs(me start){ //广搜
    qm.push(start);
    flag[start.x][start.y][start.h] = true;
    while(!qm.empty()){
        me tmp = qm.front();
        qm.pop();
        if(tmp.x == m && tmp.y == n){
            cout << tmp.cnt << endl;
            return;
        }
        if(tmp.x != 1){
            AddNew(tmp.x-1, tmp.y, tmp);
        }
        if(tmp.x != m){
            AddNew(tmp.x+1, tmp.y, tmp);
        }
        if(tmp.y != 1){
            AddNew(tmp.x, tmp.y-1, tmp);
        }
        if(tmp.y != n){
            AddNew(tmp.x, tmp.y+1, tmp);
        }
    }
}

int main(){
    cin >> t;
    while(t--){
        while(!qm.empty())
            qm.pop();
        memset(flag, 0, sizeof(flag));
        cin >> m >> n >> h;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                cin >> Map[i][j];
            }
        }
        bfs(me(1, 1, h, 0));
    }
}