//剪枝1：搭建过程中发现已建好的面积已经不小于目前求得的最优表面积，或者预见到搭完后面积一定会不小于目前最优表面积,则停止搭建（最优性剪枝）
//剪枝2：搭建过程中预见到再往上搭，高度已经无法安排，或者半径已经无法安排，则停止搭建(可行性剪枝）
//剪枝3：搭建过程中发现还没搭的那些层的体积，一定会超过还缺的体积，则停止搭建(可行性剪枝）
//剪枝4：搭建过程中发现还没搭的那些层的体积，最大也到不了还缺的体积，则停止搭建(可行性剪枝）
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;
int N, M;
int minArea = 1 << 30; //最优表面积
int area = 0; //正在搭建中的蛋糕的表面积
int minV[30]; //minV[n]表示n层蛋糕的最少体积
int minA[30]; //minA[n]表示n层蛋糕的最少侧表面积


int MaxVForNRH(int n, int r, int h){ //求在n层蛋糕，底层最大半径r，最高高度h的情况下，能凑出来的最大体积
    int v = 0;
    for(int i = 0; i < n; i++)
        v += (r-i) * (r-i) * (h-i);
    return v;
}


void Dfs(int v, int n, int r, int h){//n层凑体积v，最底层半径不超过r，高度不超过h
    if(n == 0){
        if(v) //体积不够
            return;
        else{
            minArea = min(minArea, area);
            return;
        }
    }
    if(v <= 0) //体积多了
        return;
    if(minV[n] > v) //剪枝3
        return;
    if(area + minA[n] >= minArea) //剪枝1
        return;
    if(h < n || r < n) //剪枝2
        return;
    if(MaxVForNRH(n, r, h) < v) //剪枝4
        return;
    for(int rr = r; rr >= n; rr--){ //从大到小找会比从小到大快5倍速度（经过实践得知）
        if(n == M) //底面积，给个初始值（也就是蛋糕搭完之后上表面的面积之和）
            area = rr * rr;
        for(int hh = h; hh >= n; hh--){
            area += 2 * rr * hh;
            Dfs(v - rr*rr*hh, n-1, rr-1, hh-1);
            /*记得有回溯*/
            area -= 2 * rr * hh;
        }
    }
}


int main(){
    cin >> N >> M; //M层蛋糕，体积N
    minV[0] = 0;
    minA[0] = 0;
    for(int i = 1; i <= M; i++){ //第i层半径至少i，高度至少i
        minV[i] = minV[i-1] + i*i*i;
        minA[i] = minA[i-1] + 2*i*i;
    }
    if(minV[M] > N)
        cout << 0 << endl;
    else{
        int maxH = (N - minV[M-1]) / (M * M) + 1; //底层最大高度
        int maxR = sqrt(double(N - minV[M-1] / M)) + 1; //底层最大半径
        area = 0;
        minArea = 1 << 30;
        Dfs(N, M, maxR, maxH);
        if(minArea == 1 << 30)
            cout << 0 << endl;
        else
            cout << minArea << endl;
    }
    return 0;

}

