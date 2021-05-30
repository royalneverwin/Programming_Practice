#include <iostream>
#include <cstring>
using namespace std;


int maxD[12881]; //maxD[i]代表最多装j重量所能得到的desirability的最大值
int weight[3403];
int desire[3403];


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> weight[i] >> desire[i];
    }
    /*不能直接存从1到n的sumD，那么就一次一次存，第二次的覆盖第一次*/
    for(int j = 1; j <= m; j++){
        if(j < weight[1])
            maxD[j] = 0;
        else
            maxD[j] = desire[1];
    }
    for(int i = 2; i <= n; i++){
        for(int j = m; j >= weight[i]; j--)
                maxD[j] = max(maxD[j], maxD[j-weight[i]] + desire[i]);
    }
    cout << maxD[m] << endl;
    return 0;
}