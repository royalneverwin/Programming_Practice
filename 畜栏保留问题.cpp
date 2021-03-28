#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

/*
1) 把所有奶牛按开始时间从小到大排序。
2) 为第一头奶牛分配一个畜栏。
3) 依次处理后面每头奶牛i。处理 i 时，考虑已分配畜栏中，结束时间最
早的畜栏x。若 E(x) < S(i), 则不用分配新畜栏，i可进入x,并修改E(x)为E(i) 若 E(x) >= S(i)，则分配新畜栏y,记 E(y) = E(i)
直到所有奶牛处理结束
需要用优先队列存放已经分配的畜栏，并使得结束时间最早的畜栏始终
位于队列头部。
 */

struct Cow {
    int a, b;//挤奶开始时间和结束时间
    int No;//该奶牛的编号，这里用编号记录是因为sort时会打乱奶牛位置
    bool operator < (const Cow & c) const{
        return a < c.a;
    }
} cows[50100];

int pos[50100];//pos[i]表示编号为i的奶牛去的畜栏编号

struct Stall{
    int end;//结束时间
    int No;//编号
    bool operator < (const Stall & s) const{//注意优先队列默认是从大到小，所以这里重载要使优先队列输出从小到大
        return end > s.end;
    }
    Stall(int e, int n):end(e), No(n){}
};


int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){//读取输入数据
        cin >> cows[i].a >> cows[i].b;
        cows[i].No = i;
    }
    sort(cows, cows + n);//奶牛按照开始时间排序
    int total = 0;
    priority_queue<Stall> pq;//建立畜栏的优先队列
    for(int i = 0; i < n; i++){
        if(pq.empty()){//如果优先队列为空，则无畜栏，因此增加畜栏
            ++total;
            pq.push(Stall(cows[i].b, total));
            pos[cows[i].No] = total;
        }
        else{
            Stall st = pq.top();//st是结束时间最早的畜栏
            if(st.end < cows[i].a){//注意端点也不能重合
                pq.pop();
                pos[cows[i].No] = st.No;
                pq.push(Stall(cows[i].b, st.No));//将更新的畜栏再放回优先队列
            }
            else{
                ++total;
                pq.push(Stall(cows[i].b, total));
                pos[cows[i].No] = total;
            }
        }
    }
    cout << total << endl;
    for(int i = 0; i < n; i++){
        cout << pos[i] << endl;
    }
    return 0;
}


