#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;


bool myPrev[210][10010]; //prev[i][j] = 1代表用前i个硬币能凑出价格j
bool myNext[210][10010]; //next[i][j] = 1代表用从i开始的所有硬币能凑出价格j
int coin[210];


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int n, x;
    cin >> n >> x;
    for(int i = 1; i <= n; i++){
        cin >> coin[i];
    }
    memset(myPrev, 0, sizeof(myPrev));
    memset(myNext, 0, sizeof(myNext));
    //构造prev
    if(n == 1){ //对n=1特例进行处理！因为下面的操作默认n大于1: !myNext[2][x]和!myPrev[n-1][x]
        cout << 1 << endl;
        cout << coin[1] << endl;
        return 0;
    }
    for(int j = 1; j <= x; j++){//设初值
        if(j == coin[1])
            myPrev[1][j] = true;
        else
            myPrev[1][j] = false;
    }
    for(int i = 1; i <= n; i++)
        myPrev[i][0] = true;
    int minCoin = coin[1];
    for(int i = 2; i <= n; i++){
        minCoin = min(minCoin, coin[i]);
        for(int j = 1; j < minCoin; j++)
            myPrev[i][j] = false;
        for(int j = minCoin; j <= x; j++){
            if(j < coin[i]) //凑出j不需要用到i
                myPrev[i][j] = myPrev[i-1][j];
            else
                myPrev[i][j] = myPrev[i-1][j] || myPrev[i-1][j-coin[i]];
        }
    }
    //构造next
    for(int j = 1; j <= x; j++){//设初值
        if(j == coin[n])
            myNext[n][j] = true;
        else
            myNext[n][j] = false;
    }
    for(int i = n; i >= 1; i--)
        myNext[i][0] = true;
    minCoin = coin[n];
    for(int i = n-1; i >= 1; i--){
        minCoin = min(minCoin, coin[i]);
        for(int j = 1; j < minCoin; j++)
            myNext[i][j] = false;
        for(int j = minCoin; j <= x; j++){
            if(j < coin[i]) //凑出j不需要用到i
                myNext[i][j] = myNext[i+1][j];
            else
                myNext[i][j] = myNext[i+1][j] || myNext[i+1][j-coin[i]];
        }
    }
    vector<int> Need;
    if(!myNext[2][x])
        Need.push_back(coin[1]);
    for(int i = 2; i <= n-1; i++){
        int flag = 0;
        for(int j = 0; j <= x; j++) {
            if(myPrev[i-1][j] && myNext[i+1][x-j]) {
                flag = 1;
                break;
            }
        }
        if(!flag)
            Need.push_back(coin[i]);
    }
    if(!myPrev[n-1][x])
        Need.push_back(coin[n]);
    cout << Need.size() << endl;
    sort(Need.begin(), Need.end());
    for(auto p: Need)
        cout << p << ' ';
    cout << endl;
    return 0;
}
