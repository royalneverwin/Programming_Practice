#include <iostream>
#include <vector>
using namespace std;


int m, n, k;
int Map[21][21]; //Map[i][j]表示0代表地砖已经塌陷
int ans = 0;
struct Point{
    int x; int y;
    Point(int xx, int yy):x(xx), y(yy){}
};


void dfs(int x, int y, int cur){ //cur代表目前获得的宝藏数
//    for(int i = 1; i <= m; i++){
//        for(int j = 1; j <= n; j++){
//            cout << Map[i][j] << ' ';
//        }
//        cout << endl;
//    }
    int flag = 0;
    if(x != 1 && Map[x-1][y] != 0){
        flag = 1;
        int award = Map[x-1][y];
        vector<Point> tmp;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(Map[i][j] == award){
                    Map[i][j] = 0;
                    tmp.push_back(Point(i, j));
                }
            }
        }
        dfs(x-1, y, cur+1);
        //回溯
        for(auto &p: tmp){
            Map[p.x][p.y] = award;
        }
    }
    if(x != m && Map[x+1][y] != 0){
        flag = 1;
        int award = Map[x+1][y];
        vector<Point> tmp;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(Map[i][j] == award) {
                    Map[i][j] = 0;
                    tmp.push_back(Point(i, j));
                }
            }
        }
        dfs(x+1, y, cur+1);
        //回溯
        for(auto &p: tmp){
            Map[p.x][p.y] = award;
        }
    }
    if(y != 1 && Map[x][y-1] != 0){
        flag = 1;
        int award = Map[x][y-1];
        vector<Point> tmp;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(Map[i][j] == award) {
                    Map[i][j] = 0;
                    tmp.push_back(Point(i, j));
                }
            }
        }
        dfs(x, y-1, cur+1);
        //回溯
        for(auto &p: tmp){
            Map[p.x][p.y] = award;
        }
    }
    if(y != n && Map[x][y+1] != 0){
        flag = 1;
        int award = Map[x][y+1];
        vector<Point> tmp;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(Map[i][j] == award) {
                    Map[i][j] = 0;
                    tmp.push_back(Point(i, j));
                }
            }
        }
        dfs(x, y+1, cur+1);
        //回溯
        for(auto &p: tmp){
            Map[p.x][p.y] = award;
        }
    }
    if(!flag) //如果无路可走，结束
        ans = max(ans, cur);
}


int main(){
    cin >> m >> n >> k;
     for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            cin >> Map[i][j];
            if(i != 1 || j != 1){
                if(Map[i][j] == Map[1][1])
                    Map[i][j] = 0;
            }
        }
    }
     Map[1][1] = 0;
    dfs(1, 1, 1);
    cout << ans << endl;
    return 0;
}