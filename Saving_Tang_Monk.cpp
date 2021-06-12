#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <queue>
using namespace std;


struct State{
    short r, c;
    short keys;
    int steps;
    short layout;
    State(short rr, short cc, short k, int s, short l): r(rr), c(cc), keys(k), steps(s), layout(l){}
    bool operator < (const State& s) const{
        return steps > s.steps;
    }
};
struct Point{
    int x;
    int y;
    Point(int xx, int yy):x(xx), y(yy){}
    bool operator < (const Point & p) const{
        return x == p.x? y < p.y: x < p.x;
    }
};
map<Point, int> snake;
priority_queue<State> qs;
short n, m;
short sx, sy;
short ex, ey;
char Map[110][110];
bool flag[110][110][10][33]; //在位置(r,c)，手里有k把钥匙，守卫的局面是x


int PushNew(short x, short y, State pre) { //x, y指新的位置，pre指到达这个位置之前的状态
    //检验是否能进入
    if (Map[x][y] != '#') {
        //检验是否是钥匙
        if (Map[x][y] >= '1' && Map[x][y] <= '9') {
            if(pre.keys + '0' == Map[x][y] - 1) { //能捡起这把钥匙
                if(flag[x][y][pre.keys+1][pre.layout]) //已经到过这个局面 剪枝
                    return 0;
                qs.push(State(x, y, pre.keys + 1, pre.steps + 1, pre.layout));
                flag[x][y][pre.keys+1][pre.layout] = true;
            }
            else{
                if(flag[x][y][pre.keys][pre.layout]) //已经到过这个局面 剪枝
                    return 0;
                qs.push(State(x, y, pre.keys, pre.steps + 1, pre.layout));
                flag[x][y][pre.keys][pre.layout] = true;
            }
        }
        //检验是否能救唐僧
        else if(x == ex && y == ey){
            if(pre.keys == m){
                cout << pre.steps + 1 << endl;
                return 1;
            }
            else{
                if(flag[x][y][pre.keys][pre.layout]) //已经到过这个局面 剪枝
                    return 0;
                qs.push(State(x, y, pre.keys, pre.steps + 1, pre.layout));
                flag[x][y][pre.keys][pre.layout] = true;
            }
        }
        //检验是否有snake
        else if(Map[x][y] == 'S'){
            if(1 << (snake[Point(x, y)]-1) & pre.layout){ //蛇还活着
                if(flag[x][y][pre.keys][pre.layout ^ short(1 << (snake[Point(x, y)]-1))]) //已经到过这个局面 剪枝
                    return 0;
                qs.push(State(x, y, pre.keys, pre.steps + 2, pre.layout ^ short(1 << (snake[Point(x, y)]-1))));
                flag[x][y][pre.keys][pre.layout ^ short(1 << (snake[Point(x, y)]-1))] = true;
            }
            else{ //蛇死了
                if(flag[x][y][pre.keys][pre.layout]) //已经到过这个局面 剪枝
                    return 0;
                qs.push(State(x, y, pre.keys, pre.steps + 1, pre.layout));
                flag[x][y][pre.keys][pre.layout] = true;
            }
        }
        //普通块
        else {
            if(flag[x][y][pre.keys][pre.layout]) //已经到过这个局面 剪枝
                return 0;
            qs.push(State(x, y, pre.keys, pre.steps + 1, pre.layout));
            flag[x][y][pre.keys][pre.layout] = true;
        }
    }
    return 0;
}
void bfs(State cur){
    qs.push(cur);
    flag[cur.r][cur.c][cur.keys][cur.layout] = true;
    while(!qs.empty()){
        State tmp = qs.top();
        qs.pop();
        if(tmp.r != 1){
            if(PushNew(tmp.r-1, tmp.c, tmp)){
                return;
            }
        }
        if(tmp.r != n){
            if(PushNew(tmp.r+1, tmp.c, tmp)){
                return;
            }
        }
        if(tmp.c != 1){
            if(PushNew(tmp.r, tmp.c-1, tmp)){
                return;
            }
        }
        if(tmp.c != n){
            if(PushNew(tmp.r, tmp.c+1, tmp)){
                return;
            }
        }
    }
    cout << "impossible" << endl;
}


int main(){
    cin >> n >> m;
    while(n != 0 || m != 0){
        short layout = 0;
        snake.clear();
        while(!qs.empty())
            qs.pop();
        memset(flag, 0 ,sizeof(flag));
        int index = 0;
        for(short i = 1; i <= n; i++){
            for(short j = 1; j <= n; j++){
                cin >> Map[i][j];
                if(Map[i][j] == 'S'){
                    index++;
                    snake.insert(pair<Point, int>(Point(i, j), index)); //snake[Point(i, j)] = 1;
                    layout |= short((1 << (index-1)));
                }
                else if(Map[i][j] == 'K'){
                    sx = i;
                    sy = j;
                }
                else if(Map[i][j] == 'T'){
                    ex = i;
                    ey = j;
                }
            }
        }
        State cur(sx, sy, 0, 0, layout);
        bfs(cur);
        cin >> n >> m;
    }
    return 0;
}