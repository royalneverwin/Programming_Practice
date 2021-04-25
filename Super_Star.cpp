#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <limits>
#include <algorithm>
#include <iomanip>
using namespace std;
const double MAXDOUBLE = numeric_limits<double>::max();
const double DELTA = 0.99;
const double EPS = 1e-8;

//不如说是梯度下降算法, 题目要求寻找最短半径, 可以转化成寻找距离最远的点最近的一个点（以离最远的点为半径的球肯定可以覆盖所有点）
class Point;

vector<Point> pointArray;

class Point{
public:
    double x, y, z;
    Point(){
        x = -1;
        y = -1;
        z = -1;
    }
    Point(double a, double b, double c):x(a), y(b), z(c){}
    double dis(const Point &p) const{
        return sqrt(pow(x - p.x, 2) + pow(y - p.y,2) + pow(z - p.z, 2));
    }

    double FarthestDis() const{
        double maxDis = MAXDOUBLE;
        for(auto &p: pointArray){
            maxDis = min(maxDis, dis(p));
        }
        return maxDis;
    }
};


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    /*随机数生成器*/
    random_device rd;
    int n;
    double tmpx, tmpy, tmpz;
    cin >> n;
    while(n != 0) {
        pointArray.clear();
        for (int i = 0; i < n; i++) {//n个case
            cin >> tmpx >> tmpy >> tmpz;
            pointArray.push_back(Point(tmpx, tmpy, tmpz));
        }
        double ans = numeric_limits<double>::max();
        Point ansPoint(0, 0, 0);
        double T = 200;//初始步长设置为最长
        while (T > EPS) {
            Point farthestPoint;
            double farthestDis = 0;
            double curDis;
            for(auto &p: pointArray) {//寻找离当前中心最远的点
                curDis = sqrt(pow(ansPoint.x - p.x, 2) + pow(ansPoint.y - p.y, 2) + pow(ansPoint.z - p.z, 2));
                if(curDis > farthestDis) {
                    farthestDis = curDis;
                    farthestPoint = p;
                }
            }
            /*尝试向最远的点逼近*/
            ans = min(ans, farthestDis);
            ansPoint.x += (farthestPoint.x - ansPoint.x) / farthestDis * T;
            ansPoint.y += (farthestPoint.y - ansPoint.y) / farthestDis * T;
            ansPoint.z += (farthestPoint.z - ansPoint.z) / farthestDis * T;
            T *= DELTA;
        }
        cout << fixed << setprecision(5);
        cout << ans << endl;
        cin >> n;
    }
}




