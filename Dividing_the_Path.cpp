//从线段的起点向终点安装喷水头，令f(X)表示：所安装喷水头的喷洒范围恰好覆盖直线上的区间[0 X]时，最少需要多少个喷水头
// 显然，X应满足下列条件
// X为偶数
// X所在位置不会出现奶牛，即X不属于任何一个(S,E)
// X>=2A
// 当X>2B时，存在Y属于[X-2B X-2A]且Y满足上述三个条件，使得f(X)=f(Y)+1
//递推计算f(X)
// f(X) = ∝ ： X 是奇数
// f(X) = ∝ ： X < 2A
// f(X) = ∝ ：X处可能有奶牛出没
// f(X)=1： 2A<=X<=2B 、且X位于任何奶牛的活动范围之外
// f(X)=1+min{f(Y): Y属于[X-2B X-2A]、Y位于任何奶牛的活动范围之外}： X>2B
//快速找到[X-2B X-2A]中使得f(Y)最小的元素是问题求解速度的关键 。
//可以使用优先队列priority_queue! (multiset也可以，比priority_queue慢一点）!
// 求F(X)时，若坐标属于[X-2B, X-2A]的二元组(i,F(i))都保存在一个priority_queue中,并根据F(i)值排序，则队头的元素就能确保是F(i)值最小的。

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int INFINITE = 1 << 30;
const int MAXL = 1000010;


int F[MAXL]; //F[L]就是答案
int cowThere[MAXL]; //cowTHere[i]为1表示点i有奶牛
int N, L, A, B;
struct Fx{
    int x;
    int f;
    bool operator < (const Fx& a)const{
        return f > a.f;
    }
    Fx(int xx = 0, int ff = 0):x(xx), f(ff){}
};
priority_queue<Fx> qFx;


int main(){
    cin >> N >> L;
    cin >> A >> B;
    /*把A，B定义成覆盖的直径*/
    A <<= 1;
    B <<= 1;
    memset(cowThere, 0, sizeof(cowThere));
    for(int i = 0; i < N; i++){
        int s, e;
        cin >> s >> e;
        ++cowThere[s+1]; //代表从s+1起进入一个奶牛区
        --cowThere[e]; //代表从e起退出一个奶牛区
    }
    int inCows = 0; //表示当前点位于多少头奶牛的活动范围之内
    for(int i = 0; i <= L; i++){
        F[i] = INFINITE; //初始化F[i]
        inCows += cowThere[i];
        cowThere[i] = inCows > 0;
    }
    for(int i = A; i <= B; i+= 2){ //初始化队列
        if(! cowThere[i]){ //点i不是奶牛
            F[i] = 1;
            if(i <= B + 2 - A)
                //在求F[i]的时候，要确保队列里的点x满足x <= i - A
                qFx.push((Fx(i, 1)));
        }
    }
    for(int i = B + 2; i <= L; i += 2){
        if(! cowThere[i]){
            Fx fx;
            while(! qFx.empty()){
                fx = qFx.top(); //f最小的
                if(fx.x < i - B) //我只需要x >= i-B的，x < i-B的永远也用不到了，可以直接删除
                    qFx.pop();
                else
                    break;
            }
            if(! qFx.empty()) //存在fx
                F[i] = fx.f + 1;
        }
        if(F[i-A+2] != INFINITE){ //每次求完F[i]之后把F[i-A+2]入队列
            qFx.push(Fx(i-A+2, F[i-A+2]));
        }
    }
    if(F[L] == INFINITE)
        cout << -1 << endl;
    else
        cout << F[L] << endl;
    return 0;
}



