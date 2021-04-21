#include <iostream>
#include <cmath>
#include <array>
#include <random>
#include <cstdlib>
#include <iomanip>
using namespace std;

//模拟退火算法，每次计算结果，如果更好就保留，如果不好则计算概率，在一定概率内保留，防止出现部分最优解
//这道题可以通过数学证明，不存在部分最优解，所以可以忽略一定概率的部分，如果不好就直接丢弃
const int maxP = 110;
int N;
const double EPS = 1e-6;
const double maxT = 100;
const double DELTA_T = 0.99;

struct Point{
    double x, y;
    Point(){
        x = y = 0;
    }
    Point(double tmpX, double tmpY){
        x = tmpX;
        y = tmpY;
    }
    double GetDis(const Point &p) const{
        return sqrt((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));
    }
};
struct Point computer[maxP];


//获取距离和
double getSum(const Point &ans){
    double sum = 0;
    for(int i = 0; i < N; i++){
        sum += ans.GetDis(computer[i]);
    }
    return sum;
}


//下一个点的移动方式
const array<pair<double, double>, 8> change {{
        {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}
}};


//产生随机数
static default_random_engine seed;
static uniform_int_distribution<int> randomInt(0, 7);
//用于模拟退火
// static uniform_real_distribution<double> randomDouble(0, 1);


//模拟退火
double func() {
    //初始点设为中点
    double midX = 0, midY = 0;
    for(int i = 0; i < N; i++){
        midX += computer[i].x;
        midY += computer[i].y;
    }
    midX /= N;
    midY /= N;
    Point pre(midX, midY);
    Point next;
    double T = maxT;
    double ans = getSum(pre);
    while(T - 0 > EPS){
        int direction = randomInt(seed);
        next.x = pre.x + change[direction].first;
        next.y = pre.y + change[direction].second;
        double disSum = getSum(next);
        if(ans - disSum > EPS){
            ans = disSum;
            pre = next;
        }
//        模拟退火
//        else{
//            double p = randomDouble(seed);
//            if(p < exp(ans - disSum) / T){
//                ans = disSum;
//                pre = next;
//            }
//        }
        T = T*DELTA_T;//退火
    }
    return ans;
}

int main(){
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> computer[i].x >> computer[i].y;
    }
    double ans = func();
    cout << setiosflags(ios::fixed) << setprecision(0) << ans << endl;
    return 0;
}