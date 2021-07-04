#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int n, m;
int weight[1010];
int maxWeight = 0;
int findMin(){
    return ceil(float(maxWeight) / m);
}
int findMax(){
    return maxWeight;
}
bool judge(int middle){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += ceil(float(weight[i]) / middle);
        if(sum > m)
            return false;
    }
    return true;
}
void binarySearch(){
    int minAns = findMin();
    int maxAns = findMax();
    int ans = 0;
    while(minAns <= maxAns){
        int middle = (minAns + maxAns) / 2;
        for(int i = 0; i < m; i++){
            if(judge(middle)){
                ans = middle;
                maxAns = middle - 1;
            }
            else{
                minAns = middle + 1;
            }
        }
    }
    cout << ans << endl;
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> weight[i];
        maxWeight = max(maxWeight, weight[i]);
    }
    binarySearch();
    return 0;
}