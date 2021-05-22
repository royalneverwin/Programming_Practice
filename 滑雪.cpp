#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;


struct Point{
    int h;
    int x;
    int y;
    Point(int _h, int _x, int _y):h(_h), x(_x), y(_y){}
    bool operator < (const Point& p) const{
        return h < p.h;
    }
};


int myMap[101][101];
int Distance[101][101]; //代表从(x1, y1)开始滑雪最长的步数。从小到大计算Distance，可以利用之前计算的结果快速得到答案
vector<Point> allPoint;


int main(){
    int r, c;
    cin >> r >> c;
    for(int i = 1; i <= r; i++){
        for(int j = 1; j <= c; j++){
            cin >> myMap[i][j];
            allPoint.push_back(Point(myMap[i][j], i, j));
        }
    }
    sort(allPoint.begin(), allPoint.end());
    int tmpMax;
    int totalMax = 0;
    memset(Distance, 1, sizeof(Distance));
    for(auto& p: allPoint){
        int x = p.x;
        int y = p.y;
        tmpMax = 1;
        if(x != 1){
            if(myMap[x][y] > myMap[x-1][y] && Distance[x-1][y] + 1 > tmpMax){
                tmpMax = Distance[x-1][y] + 1;
            }
        }
        if(x != r){
            if(myMap[x][y] > myMap[x+1][y] && Distance[x+1][y] + 1 > tmpMax){
                tmpMax = Distance[x+1][y] + 1;
            }
        }
        if(y != 1){
            if(myMap[x][y] > myMap[x][y-1] && Distance[x][y-1] + 1 > tmpMax){
                tmpMax = Distance[x][y-1] + 1;
            }
        }
        if(y != c){
            if(myMap[x][y] > myMap[x][y+1] && Distance[x][y+1] + 1 > tmpMax){
                tmpMax = Distance[x][y+1] + 1;
            }
        }
        Distance[x][y] = tmpMax;
        totalMax = max(totalMax, tmpMax);
    }
    cout << totalMax << endl;
    return 0;
}