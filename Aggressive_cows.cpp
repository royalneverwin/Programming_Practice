#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 1000000000;


vector <int> stall;


int N, C;


bool IfDisRight(int dis){
    int length = stall.size();
    int pre = 0;
    int sum = 1;
    while(sum < C){
        int flag = 0;
        for(int i = pre + 1; i < length; i++){
            if(stall[i] - stall[pre] >= dis){
                pre = i;
                sum++;
                flag = 1;
                break;
            }
        }
        if(!flag){
            return false;
        }
    }
    return true;
}


int main(){
    scanf("%d%d", &N, &C);
    int oneStall;
    for(int i = 0; i < N; i++){
        scanf("%d", &oneStall);
        stall.push_back(oneStall);
    }
    sort(stall.begin(), stall.end());
    int maxDis = MAX / C;
    int minDis = 1;
    int middle = (maxDis + minDis)/2;//二分查找
    while(maxDis > minDis + 1){
        if(IfDisRight(middle)){
            minDis = middle;
        } else{
            maxDis = middle - 1;
        }
        middle = (maxDis + minDis) / 2;
    }
    if(maxDis == minDis){
        cout << minDis << endl;
    } else{//maxDIs == minDis + 1
        if(IfDisRight(maxDis)){
            cout << maxDis << endl;
        } else{
            cout << minDis << endl;
        }
    }
    return 0;
}