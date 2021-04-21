#include <iostream>
#include <cstring>
using namespace std;


/* 因为一个操作操作4次后，就会回到原来的状态, 所以一个操作最多有四种可能：操作0, 1, 2, 3次, 一共9种操作, 所以最多有4^9种可能
 * 暴力枚举即可
 */


const char changeClock[9][6] = {"ABDE", "ABC", "BCEF", "ADG", "BDEFH", "CFI", "DEGH", "GHI", "EFHI"};


int minChanges = (1 << 31) - 1;
int ansChange[9];
int clockStatus[9];
int tmpClockStatus[9];
int op[9];


void Check(){//对每种情况进行检查
    int sum = 0;
    for(int i = 0; i < 9; i++){
        sum += op[i];
        if(sum >= minChanges){//如果此时操作数大于目前最小值，直接跳过
            return;
        }
    }
    for(int i = 0; i < 9; i++){//初始化tmpClockStatus
        tmpClockStatus[i] = clockStatus[i];
    }
    for(int i = 0; i < 9; i++){//对tmpClockStatus进行处理
        for(int j = 0; j < strlen(changeClock[i]); j++){
            tmpClockStatus[changeClock[i][j] - 'A'] = (tmpClockStatus[changeClock[i][j] - 'A'] + op[i]) % 4;
        }
    }
    int flag = 1;
    for(int i = 0; i < 9; i++){
        if(tmpClockStatus[i] != 0){
            flag = 0;
            break;
        }
    }
    if(flag){
        minChanges = sum;
        for(int i = 0; i < 9; i++){
            ansChange[i] = op[i];
        }
    }
}
int main(){
    for(int i = 0; i < 9; i++){
        cin >> clockStatus[i];
        op[i] = 0;
    }
    while(op[8] != 4){
        Check();
        op[0]++;
        for(int i = 0; i < 8; i++){
            op[i+1] += op[i] / 4;
            op[i] %= 4;
        }
    }
    for(int i = 0; i < 9; i++){
        if(ansChange[i] != 0){
            for(int j = 0; j < ansChange[i]; j++){
                cout << i + 1 << ' ';
            }
        }
    }
    return 0;
}