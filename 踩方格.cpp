#include <iostream>
#include <cstring>
using namespace std;


int visited[30][50];


int ways(int i, int j, int n){//从i,j出发走n步一共有多少种方案
    if(n == 0)
        return 1;
    visited[i][j] = 1;//被访问
    int num = 0;
    if(!visited[i][j-1])//向西走
        num += ways(i, j-1, n-1);
    if(!visited[i][j+1])//向东走
        num += ways(i, j+1, n-1);
    if(!visited[i+1][j])//向北走
        num += ways(i+1, j, n-1);
    visited[i][j] = 0;//！！！！！更新，让它再次未被访问
    return num;
}


int main(){
    int n;
    cin >> n;
    memset(visited, 0, sizeof(visited));
    cout << ways(0, 25, n);
}