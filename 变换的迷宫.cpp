#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;


int t;
int r,c,k;
struct Point{
    int x;int y;int cnt;
    Point(int xx, int yy, int _cnt=0):x(xx), y(yy), cnt(_cnt){
    }
    Point(){
        x = y = cnt = 0;
    }
};
Point s;
Point e;
char Map[110][110];
vector<Point> rock;
int ans[110][110][11]; //cnt记录到该状态的最少时间，第三个记录t % k，这样剪枝就会防止无限循环
int flag;
queue<Point> qq;


void bfs(){
    while(!qq.empty()){
        Point tmp = qq.front();
        qq.pop();
        int x = tmp.x;
        int y = tmp.y;
        int cnt = tmp.cnt + 1;
        if(x != 1){
            if(Map[x-1][y] != '#'){
                if(Map[x-1][y] == 'E'){ //到终点了
                    flag = 1;
                    cout << cnt << endl;
                    return;
                }
                if(cnt < ans[x-1][y][cnt % k]){ //比之前更早，再入队列
                    ans[x-1][y][cnt % k] = cnt;
                    qq.push(Point(x-1, y, cnt));
                }
            }
            else if(cnt % k == 0){
                if(cnt < ans[x-1][y][0]){ //比之前更早，再入队列
                    ans[x-1][y][0] = cnt;
                    qq.push(Point(x-1, y, cnt));
                }
            }
        }
        if(x != r){
            if(Map[x+1][y] != '#'){
                if(Map[x+1][y] == 'E'){ //到终点了
                    flag = 1;
                    cout << cnt << endl;
                    return;
                }
                if(cnt < ans[x+1][y][cnt % k]){ //比之前更早，再入队列
                    ans[x+1][y][cnt % k] = cnt;
                    qq.push(Point(x+1, y, cnt));
                }
            }
            else if(cnt % k == 0){
                if(cnt < ans[x+1][y][0]){ //比之前更早，再入队列
                    ans[x+1][y][0] = cnt;
                    qq.push(Point(x+1, y, cnt));
                }
            }
        }
        if(y != 1){
            if(Map[x][y-1] != '#'){
                if(Map[x][y-1] == 'E'){ //到终点了
                    flag = 1;
                    cout << cnt << endl;
                    return;
                }
                if(cnt < ans[x][y-1][cnt % k]){ //比之前更早，再入队列
                    ans[x][y-1][cnt % k] = cnt;
                    qq.push(Point(x, y-1, cnt));
                }
            }
            else if(cnt % k == 0){
                if(cnt < ans[x][y-1][0]){ //比之前更早，再入队列
                    ans[x][y-1][0] = cnt;
                    qq.push(Point(x, y-1, cnt));
                }
            }
        }
        if(y != c){
            if(Map[x][y+1] != '#'){
                if(Map[x][y+1] == 'E'){ //到终点了
                    flag = 1;
                    cout << cnt << endl;
                    return;
                }
                if(cnt < ans[x][y+1][cnt % k]){ //比之前更早，再入队列
                    ans[x][y+1][cnt % k] = cnt;
                    qq.push(Point(x, y+1, cnt));
                }
            }
            else if(cnt % k == 0){
                if(cnt < ans[x][y+1][0]){ //比之前更早，再入队列
                    ans[x][y+1][0] = cnt;
                    qq.push(Point(x, y+1, cnt));
                }
            }
        }
    }
}


void Prepare(){
    flag = 0;
    rock.clear();
    while(!qq.empty())
        qq.pop();
    cin >> r >> c >> k;
    for(int i = 1; i <= r; i++){
        for(int j = 1; j <= c; j++){
            for(int kk = 0; kk < k; kk++)
                ans[i][j][kk] = numeric_limits<int>::max();
            cin >> Map[i][j];
            if(Map[i][j] == 'S'){
                s.x = i;
                s.y = j;
            }
            else if(Map[i][j] == 'E'){
                e.x = i;
                e.y = j;
            }
            else if(Map[i][j] == '#')
                rock.push_back(Point(i, j));
        }
    }
}


int main(){
    cin >> t;
    while(t--){
        Prepare();
        ans[s.x][s.y][0] = 0;
        qq.push(s);
        bfs();
        if(!flag)
            cout << "Oop!" << endl;
    }
    return 0;
}