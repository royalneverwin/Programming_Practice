#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
using namespace std;

//MaxMin算法+alpha-beta剪枝
//alpha最小值，beta最大值

int chessCount = 0;
int ansX = -1, ansY = -1;

char Chess[4][4];


bool ifWin(char c){
    int flag = 0;
    for(int i = 0; i < 4; i++){
        if(Chess[i][0] == c && Chess[i][1] == c && Chess[i][2] == c && Chess[i][3] == c){//一行4个
            flag = 1;
        }
    }
    for(int i = 0; i < 4; i++){
        if(Chess[0][i] == c && Chess[1][i] == c && Chess[2][i] == c && Chess[3][i] == c){//一列4个
            flag = 1;
        }
    }
    if(Chess[0][0] == c && Chess[1][1] == c && Chess[2][2] == c && Chess[3][3] == c){//对角线4个
        flag = 1;
    }
    if(Chess[3][0] == c && Chess[2][1] == c && Chess[1][2] == c && Chess[0][3] == c){//对角线4个
        flag = 1;
    }
    return flag;
}


int MaxSearch();
int MinSearch(){
//    cout << "MinSearch: " << endl;
//    for(int i = 0; i < 4; i++){
//        for(int j = 0; j < 4; j++){
//            cout << Chess[i][j];
//        }
//        cout << endl;
//    }
//    cout << "ifWin(x): " << ifWin('x') << endl;
    if(ifWin('x')){//到对手的时候我已经赢了
        return 1;
    }
    if(chessCount == 16){//平局
        return 0;
    }
    int ans;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(Chess[i][j] == '.'){
                Chess[i][j] = 'o';
                chessCount++;
                ans = MaxSearch();
                Chess[i][j] = '.';
                chessCount--;
                if(ans == 0){//存在赢不了的局, 平或者输
                    return 0;
                }
            }
        }
    }
    return 1;//都是必赢局
}




int MaxSearch(){
//    cout << "MaxSearch: " << endl;
//    for(int i = 0; i < 4; i++){
//        for(int j = 0; j < 4; j++){
//            cout << Chess[i][j];
//        }
//        cout << endl;
//    }
//    cout << "ifWin(o): " << ifWin('o') << endl;
    if(ifWin('o')){//到我的时候，对方已经赢了
        return 0;
    }
    if(chessCount == 16){//平局
        return 0;
    }
    int ans;
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if(Chess[i][j] == '.'){
                Chess[i][j] = 'x';
                chessCount++;
                ans = MinSearch();
                Chess[i][j] = '.';
                chessCount--;
                if(ans == 1){//如果有必赢局
                    return 1;
                }
            }
        }
    }
    return 0;
}


int Predict(){
    if(ifWin('o')){
        return 0;
    }
    if(chessCount == 16) {//平局
        return 0;
    }
    int ans;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(Chess[i][j] == '.'){
                Chess[i][j] = 'x';
                chessCount++;
                ans = MinSearch();
                Chess[i][j] = '.';
                chessCount--;
                if(ans == 1){//有必赢局
                    ansX = i;
                    ansY = j;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main(){
    char c;
    cin >> c;
    while(c != '$'){
        chessCount = 0;
        for(int i = 0; i < 4; i++){
            cin >> Chess[i];
            for(int j = 0; j < 4; j++){
                if(Chess[i][j] != '.'){
                    chessCount++;
                }
            }
        }
//        for(int i = 0; i < 4; i++){
//            for(int j = 0; j < 4; j++){
//                cout << Chess[i][j];
//            }
//            cout << endl;
//        }
        if(Predict()){
            printf("(%d,%d)\n", ansX, ansY);
        }
        else{
            cout << "#####" << endl;
        }
        cin >> c;
    }
    return 0;
}