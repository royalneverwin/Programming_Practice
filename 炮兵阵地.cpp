#include <iostream>
#include <cstring>
using namespace std;


int state[70]; //每行放大炮的种类
int N, M;
int myIndex = 0;
int Map[110];
int dp[110][70][70]; //第i行布局为j，第i-1行布局为k的大炮最多数目（这样会形成递推关系）


inline void GetState(){
    for(int i = 0; i < (1 << M); i++){
        if((i & (i >> 1)) == 0 && (i & (i >> 2)) == 0 && (i & (i << 1)) == 0 && (i & (i << 2)) == 0){
            state[myIndex] = i;
            myIndex++;
        }
    }
}


inline int Num(int curState){
    int sum = 0;
    while(curState != 0){
        sum++;
        curState &= (curState - 1); //注意这种写法
    }
    return sum;
}


inline bool ifOK(int row1, int state1, int row2, int state2){ //不仅要判断是否相邻，还要判断是不是在山地建炮车
    if((Map[row1]& state1) != 0){
        return false;
    }
    if(row2 >= 0 && (Map[row2]& state2) != 0){
        return false;
    }
    if(row2 >=0 && (state1 & state2) != 0)
        return false;
    return true;
}


int F(int row, int state1, int state2){
    if(dp[row][state1][state2] != -1) {
        return dp[row][state1][state2];
    }
    if(!ifOK(row, state[state1], row-1, state[state2])) { //如果这种情况不成立
        return (dp[row][state1][state2] = 0);
    }
    if(row == 0) { //边界1
        return (dp[row][state1][state2] = Num(state[state1]));
    }
    if(row == 1){ //边界2
        return (dp[row][state1][state2] = Num(state[state1]) + Num(state[state2]));
    }
    int ret = 0;
    for(int i = 0; i < myIndex; i++){
        if(ifOK(row, state[state1], row -2, state[i]) && ifOK(row-1, state[state2], row-2, state[i])){ //如果成立
            ret = max(ret, F(row-1, state2, i) + Num(state[state1]));
        }
    }
    return (dp[row][state1][state2] = ret);
}


int main(){
    cin >> N >> M;
    char c;
    for(int i = 0; i < N; i++){
        Map[i] = 0;
        for(int j = 0; j < M; j++){
            cin >> c;
            if(c == 'H')
                Map[i] = Map[i] | (1 << j);
        }
    }
    GetState();
    memset(dp, 0xFF, sizeof(dp));
    int ans = 0;
//    for(int l = 0; l < 2; l++){
//        for(int i = 0; i < myIndex; i++){
//            if(l == 0)
//                dp[0][i][0] = Num(state[i]);
//            else {
//                for (int j = 0; j < myIndex; j++) {
//                    dp[1][i][j] = Num(state[i]) + Num(state[j]);
//                }
//            }
//        }
//    }
//    for(int l = 2; l < m; l++) {
//        for (int i = 0; i < N; i++) {
//            for (int j = 0; j < myIndex; j++) {
//                for (int k = 0; k < myIndex; k++) {
//                    ans = max(ans, F(i, state[j], state[k]));
//                }
//            }
//        }
//    }
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < myIndex; j++) {
            for (int k = 0; k < myIndex; k++) {
                ans = max(ans, F(i, j, k));
            }
        }
    }
    cout << ans << endl;
    return 0;
}