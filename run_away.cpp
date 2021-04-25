#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <limits>
#include <algorithm>
#include <iomanip>
using namespace std;
const double MAXDOUBLE = numeric_limits<double>::max();
const double DELTA = 0.9;
const double EPS = 1e-6;

//模拟退火算法
class Point;

vector<Point> pointArray;

class Point{
public:
    double x, y;
    Point(){
        x = -1;
        y = -1;
    }
    Point(double a, double b):x(a), y(b){}
    double dis(const Point &p) const{
        return sqrt(pow(x - p.x, 2) + pow(y - p.y,2));
    }

    double NearestDis() const{
        double minDis = MAXDOUBLE;
        for(auto &p: pointArray){
            minDis = min(minDis, dis(p));
        }
        return minDis;
    }

    friend ostream & operator << (ostream &os, const Point &p){
        os << fixed << setprecision(1);
        os << '(' << p.x << ", " << p.y << ')';
        return os;
    }
};


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    /*随机数生成器*/
    random_device rd;
    static default_random_engine randomEngine(rd());
    static uniform_real_distribution<double> randomDouble(0,1);//随机生成0-1中double, 用于判断移动的方向
    int n;
    int x, y, m;
    int tmpx, tmpy;
    cin >> n;
    for(int i = 0; i < n; i++){//n个case
        pointArray.clear();
        cin >> x >> y >> m;
        for(int j = 0; j < m; j++){
            cin >> tmpx >> tmpy;
            pointArray.push_back(Point(tmpx, tmpy));
        }
        double ans, totalAns = 0;//ans代表每个点的结果, totalAns代表最终结果
        Point ansPoint, totalAnsPoint;
        for(int k = 0; k < 10; k++) {//随机从10个点开始向答案点逼近
            Point prev;//代表之前的最优点
            prev.x = randomDouble(randomEngine) * x;
            prev.y = randomDouble(randomEngine) * y;
            ans = prev.NearestDis();//初始化
            ansPoint = prev;//初始化
            double T = sqrt(x*x + y*y);//初始步长设置为最长
            while (T > EPS){
                Point next;//代表每个next
                Point finalNext = prev;//代表每次找到的最优next
                double nextAns;//代表每个next的结果
                double finalNextAns = 0;//代表每次找到的next的最优结果
                for(int l = 0; l < 30; l++){//每一次随机选取30个方向走, 选最好的结果
                    double direction = randomDouble(randomEngine) * 2 * M_PI;
                    next.x = prev.x + T * cos(direction);
                    next.y = prev.y + T * sin(direction);
                    if(next.x > x || next.x < 0 || next.y > y || next.y < 0){//如果走出了边界, 就跳过这个点的判断
                        continue;
                    }
                    nextAns = next.NearestDis();
                    if(nextAns > finalNextAns){
                        finalNextAns = nextAns;
                        finalNext = next;
                    }
                }
                if(finalNextAns > ans){//如果更优, 更新ans
                    ans = finalNextAns;
                    ansPoint = finalNext;
                } else{//否则, 概率更新ans
//                    if(randomDouble(randomEngine) < exp((finalNextAns - ans) / T)){
//                        ans = finalNextAns;
//                        ansPoint = finalNext;
//                    }
                }
                prev = ansPoint;
                T *= DELTA;
            }
            if(ans > totalAns){
                totalAnsPoint = ansPoint;
                totalAns = ans;
            }
        }
        cout << "The safest point is " << totalAnsPoint << '.' << endl;
    }
}




