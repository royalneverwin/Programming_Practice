#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

struct Point{
    int x; int y;
    Point(int xx, int yy):x(xx), y(yy){}
    bool operator < (const struct Point& p) const{
        return y == p.y? x < p.x: y > p.y;
    }
};


set<Point> allP;
char match[5][5];
vector<Point> Win;
int best = 4;

void dfs(){
    if(!allP.empty()) {
        int x = allP.begin()->x;
        int y = allP.begin()->y;
        allP.erase(allP.begin());
        auto p = allP.find(Point(y, x));
        allP.erase(p);
        match[x][y] = 'W';
        match[y][x] = 'L';
        dfs();
        match[x][y] = 'L';
        match[y][x] = 'W';
        dfs();
        allP.insert(Point(x, y));
        allP.insert(Point(y, x));
        match[x][y] = match[y][x] = '?';
    }else{
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 4; j++) {
                if (match[i][j] == 'W')
                    Win[i - 1].y++;
            }
        }
        sort(Win.begin(), Win.end());
        for (int i = 0; i <= 3; i++) {
            if (Win[i].x == 1) {
                best = min(i + 1, best);
                break;
            }
        }
        for (int i = 0; i <= 3; i++) { //回溯
            Win[i].x = i + 1;
            Win[i].y = 0;
        }
    }
}


int main(){
    int t;
    cin >> t;
    while(t--){
        best = 4;
        Win.clear();
        allP.clear();
        Win.push_back(Point(1, 0));
        Win.push_back(Point(2, 0));
        Win.push_back(Point(3, 0));
        Win.push_back(Point(4, 0));
        for(int i = 1; i <= 4; i++){
            for(int j = 1; j <= 4; j++){
                cin >> match[i][j];
                if(match[i][j] == '?' && i != 1 && j != 1)
                    allP.insert(Point(i, j));
            }
        }
        for(int j = 1; j <= 4; j++){ //矩阵是对称矩阵，只要改一半
            if(match[1][j] == '?'){
                match[1][j] = 'W';
                match[j][1] = 'L';
            }
        }
        dfs();
        cout << best << endl;
    }
}