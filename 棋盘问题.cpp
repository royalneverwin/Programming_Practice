#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
#define DEBUGx

char Chess[9][9]; //.是空白，#是棋盘上的空白区域，w是棋盘上的已有棋子区域
struct Point{
    int x;
    int y;
    Point(int xx, int yy):x(xx), y(yy){}
    bool operator < (const struct Point& p) const{
        return x != p.x? x < p.x: y < p.y;
    }
};


set<Point> points;


int sum = 0;
int n, k;


bool ifOK(int x, int y){
    for(int i = 1; i <= n; i++){
        if(i != x){
            if(Chess[i][y] == 'w')
                return false;
        }
    }
    for(int j = 1; j <= n; j++){
        if(j != y){
            if(Chess[x][j] == 'w')
                return false;
        }
    }
    return true;
}


void Dfs(int left){ //还剩n个棋子的深搜
#ifdef DEBUG
    cout << points.size() << ' ' << left << endl;
    for(int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << Chess[i][j];
        }
        cout << endl;
    }
#endif
    if(points.size() < left) //剪枝
        return;
    if(left == 0) { //成功分配
        sum += 1;
        return;
    }
    //第一种情况 这一个空格不放点
    struct Point p = *(points.begin());
    points.erase(points.begin());
    Dfs(left);
    points.insert(p); //回溯
    //第二种情况 这一个空格放点
    p = *(points.begin());
    if(ifOK(points.begin()->x, points.begin()->y)) {
        points.erase(points.begin());
        Chess[p.x][p.y] = 'w';
        Dfs(left-1);
        points.insert(p); //回溯
        Chess[p.x][p.y] = '#'; //回溯
    }
}


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin >> n >> k;
    while(n != -1 || k != -1){
        sum = 0;
        points.clear();
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                cin >> Chess[i][j];
                if(Chess[i][j] == '#')
                    points.insert(Point(i, j));
            }
        }
        Dfs(k);
        cout << sum << endl;
        cin >> n >> k;
    }
    return 0;
}