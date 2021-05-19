#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>
using namespace std;
int sum[9][9];
int result[16][9][9][9][9];
int smallSum(int x1, int y1, int x2, int y2){
    return sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
}
int fun(int n, int x1, int y1, int x2, int y2){ //求将 (x1,y1)-(x2,y2)分割成 n块，所能得到的n个块的分数的平方之和的最小值
    int v = 1 << 30;
    if(n == 1){
        int t = smallSum(x1, y1, x2, y2);
        return t*t;
    }
    if(x2 - x1 + y2 - y1 < n-1)//不够切了
        return v;
    if(result[n][x1][y1][x2][y2] != -1)//已经算过这个result了
        return result[n][x1][y1][x2][y2];
    for(int x = x1; x < x2; x++){//上边切成1块或者下边切成1块
        int up = smallSum(x1, y1, x, y2);
        int down = smallSum(x+1, y1, x2, y2);
        int t = min(fun(n-1, x1, y1, x, y2) + down * down, fun(n-1, x+1, y1, x2, y2) + up * up);
        v = min(t, v);
    }
    for(int y = y1; y < y2; y++){//左边切成1块或者右边切成1块
        int left = smallSum(x1, y1, x2, y);
        int right = smallSum(x1, y+1, x2, y2);
        int t = min(fun(n-1, x1, y1, x2, y) + right * right, fun(n-1, x1, y+1, x2, y2) + left * left);
        v = min(t, v);
    }
    result[n][x1][y1][x2][y2] = v;
    return v;
}
int main(){
    int n;
    memset(sum, 0, sizeof(sum));
    memset(result, 0xff, sizeof(result));
    cin >> n;
    for(int i = 1; i <= 8; i++){
        int rowSum = 0;
        for(int j = 1; j <= 8; j++){
            int s;
            cin >> s;
            rowSum += s;
            sum[i][j] = sum[i-1][j] + rowSum; //注意这种求和方式
        }
    }
    int squareSum = fun(n, 1, 1, 8, 8);
    double Result = n * squareSum - sum[8][8] * sum[8][8];
    cout << setiosflags(ios::fixed) << setprecision(3) << sqrt(Result / (n * n)) << endl;
    return 0;
}