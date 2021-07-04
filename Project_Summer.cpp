#include <iostream>
#include <queue>
#include <cstring>
#include <map>
using namespace std;


int t;
int n, m;
char Map[110][110];
int Ix, Iy;
int Bx, By;
bool ifGet[110][110];


struct Point{
    int x1, y1, x2, y2;
    Point(int xx1, int yy1, int xx2, int yy2): x1(xx1), y1(yy1), x2(xx2), y2(yy2){}
    Point(): x1(0), y1(0), x2(0), y2(0){}
};
bool ifCatch[27];
map<char, Point> mmap;


struct Pos{
    int x;
    int y;
    int cnt;
    Pos(int xx, int yy, int c): x(xx), y(yy), cnt(c){}
};
queue<Pos> qp;
bool win;
bool ifWin(int x, int y, int cnt, int Case){
    if(x == Ix && y == Iy){
        win = true;
        cout << "Case #" << Case << ": " << cnt << endl;
        return true;
    }
    return false;
}
void AddNew(const Pos& tmp, int Case){
    if(Map[tmp.x][tmp.y] >= 'a' && Map[tmp.x][tmp.y] <= 'z'){ //有传送门
        Point cur = mmap[Map[tmp.x][tmp.y]];
        if(tmp.x == cur.x1 && tmp.y == cur.y1){ //跳到2
            if(!ifGet[cur.x2][cur.y2]){
                if(ifWin(cur.x2, cur.y2, tmp.cnt + 1, Case)){
                    return;
                }
                ifGet[cur.x2][cur.y2] = true;
                qp.push(Pos(cur.x2, cur.y2, tmp.cnt + 1));
            }
        }
        else if(tmp.x == cur.x2 && tmp.y == cur.y2){ //跳到1
            if(!ifGet[cur.x1][cur.y1]){
                if(ifWin(cur.x1, cur.y1, tmp.cnt + 1, Case)){
                    return;
                }
                ifGet[cur.x1][cur.y1] = true;
                qp.push(Pos(cur.x1, cur.y1, tmp.cnt + 1));
            }
        }
    }
    if(tmp.x != 0 && Map[tmp.x-1][tmp.y] != '#' && !ifGet[tmp.x-1][tmp.y]){
            if(ifWin(tmp.x-1, tmp.y, tmp.cnt + 1, Case)){
                return;
            }
            ifGet[tmp.x-1][tmp.y] = true;
            qp.push(Pos(tmp.x-1, tmp.y, tmp.cnt + 1));
    }
    if(tmp.x != n-1 && Map[tmp.x+1][tmp.y] != '#' && !ifGet[tmp.x+1][tmp.y]){
        if(ifWin(tmp.x+1, tmp.y, tmp.cnt + 1, Case)){
            return;
        }
        ifGet[tmp.x+1][tmp.y] = true;
        qp.push(Pos(tmp.x+1, tmp.y, tmp.cnt + 1));
    }
    if(tmp.y != 0 && Map[tmp.x][tmp.y-1] != '#' && !ifGet[tmp.x][tmp.y-1]){
        if(ifWin(tmp.x, tmp.y-1, tmp.cnt + 1, Case)){
            return;
        }
        ifGet[tmp.x][tmp.y-1] = true;
        qp.push(Pos(tmp.x, tmp.y-1, tmp.cnt + 1));
    }
    if(tmp.y != m-1 && Map[tmp.x][tmp.y+1] != '#' && !ifGet[tmp.x][tmp.y+1]){
        if(ifWin(tmp.x, tmp.y+1, tmp.cnt + 1, Case)){
            return;
        }
        ifGet[tmp.x][tmp.y+1] = true;
        qp.push(Pos(tmp.x, tmp.y+1, tmp.cnt + 1));
    }
}
void bfs(int Case){
    qp.push(Pos(Bx, By, 0));
    while(!qp.empty()){
        Pos tmp = qp.front();
        qp.pop();
        AddNew(tmp, Case);
        if(win)
            return;
    }
    cout << "Case #" << Case << ": " << -1 << endl;
}
int main(){
    cin >> t;
    for(int Case = 1; Case <= t; Case++){
        mmap.clear();
        memset(ifCatch, 0, sizeof(ifCatch));
        memset(ifGet, 0, sizeof(ifGet));
        while(!qp.empty())
            qp.pop();
        win = false;
        cin >> n >> m;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> Map[i][j];
                if(Map[i][j] >= 'a' && Map[i][j] <= 'z'){
                       if(!ifCatch[Map[i][j] - 'a']){
                           mmap.insert(pair<char, Point>(Map[i][j], Point(i, j, -1, -1)));
                           ifCatch[Map[i][j] - 'a'] = true;
                       }
                       else{
                           mmap[Map[i][j]].x2 = i;
                           mmap[Map[i][j]].y2 = j;
                       }
                }
                else if(Map[i][j] == 'B'){
                    Bx = i;
                    By = j;
                }
                else if(Map[i][j] == 'I'){
                    Ix = i;
                    Iy = j;
                }
            }
        }
        bfs(Case);
    }
    return 0;
}