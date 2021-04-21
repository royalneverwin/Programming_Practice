#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;


multiset <int> spend;//用来找最大值和最小值
vector<int> continuingSpend;

int N, M;



int FindMax(){
    auto i = spend.end();
    int sum = 0;
    for(int j = 0; j < N - M + 1; j++){
        i--;
    }
    while(i != spend.end()){
        sum += *i;
        i++;
    }
    return sum;
}


int FindMin(){
    auto i =spend.end();
    i--;
    return *i;
}


bool IfDisRight(double dis){
    int sum = 1;
    int periodSum = 0;
    for(int i : continuingSpend) {//判断按照dis来分的话可不可以分成>=F份即可
        periodSum += i;
        if(periodSum > dis){
            periodSum = 0;
            sum++;
            periodSum += i;
        }
    }
    if(sum <= M)
        return true;
    else
        return false;
}



int main(){
    scanf("%d%d", &N, &M);
    int oneMonth;
    for(int i = 0; i < N; i++){
        scanf("%d", &oneMonth);
        spend.insert(oneMonth);
        continuingSpend.push_back(oneMonth);
    }
    int maxDis = FindMax();
    int minDis = FindMin();
    int middle = (maxDis + minDis)/2;//二分查找
    while(maxDis > minDis + 1){
        if(IfDisRight(middle)){
            maxDis = middle;
        } else{
            minDis = middle + 1;
        }
        middle = (maxDis + minDis) / 2;
    }
    if(maxDis == minDis){
        cout << minDis << endl;
    } else{
        if(IfDisRight(minDis)){
            cout << minDis << endl;
        } else{
            cout << maxDis << endl;
        }
    }
    return 0;
}