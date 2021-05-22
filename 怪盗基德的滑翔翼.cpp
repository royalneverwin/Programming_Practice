#include <iostream>
#include <map>
#include <algorithm>
using namespace std;


int height[101];
multimap<int, int> mmap;


int leftMax[101];//从i点向左边飞最多的房子
int rightMax[101];//从i点向右边飞最多的房子


int num;


void GetLeftMax(int index){
    for(int i = 0; i < index; i++){
        if(height[i] < height[index]){
            leftMax[index] = max(leftMax[index], leftMax[i] + 1);
        }
    }
}


void GetRightMax(int index){
    for(int i = index+1; i < num; i++){
        if(height[i] < height[index]){
            rightMax[index] = max(rightMax[index], rightMax[i] + 1);
        }
    }
}

int main(){
    int k;
    int maxCnt;
    cin >> k;
    while(k--){
        cin >> num;
        for(int i = 0; i < num; i++){
            cin >> height[i];
            mmap.insert(make_pair(height[i], i));
            leftMax[i] = 1;
            rightMax[i] = 1;
        }
        /*从Height小到大计算leftMax和rightMax*/
        for(auto &m: mmap){
            int index=  m.second;
            GetLeftMax(index);
            GetRightMax(index);
        }
        maxCnt = 0;
        for(int i = 0; i < num; i++){
            maxCnt = max(maxCnt, leftMax[i]);
            maxCnt = max(maxCnt, rightMax[i]);
        }
        cout << maxCnt << endl;
    }
    return 0;
}