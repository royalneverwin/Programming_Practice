#include <iostream>
#include <string>
using namespace std;
string curLock;
string ansLock;
string tmpLock;


void ChangeLock(int pos){
    tmpLock[pos] = (tmpLock[pos] - '0') ^ 1 + '0';
}

/*从左到右看，每一个锁的左边是否按下和解锁密码决定了该锁是否按下*/
int main(){
    cin >> curLock >> ansLock;
    int ifRight1 = 0;
    int ifRight2 = 0;
    int minTry1 = 0;
    int minTry2 = 0;
    /*第一种情况 锁按下*/
    tmpLock = curLock;
    ChangeLock(0);
    ChangeLock(1);
    minTry1 ++;
    for(int i = 1; i < tmpLock.length(); i++){//从左到右进行处理
        if(tmpLock[i-1] != ansLock[i-1]){//i锁要按下
            minTry1++;
            ChangeLock(i-1);
            ChangeLock(i);
            if(i != tmpLock.length() - 1)
                ChangeLock(i+1);
        }
    }
    if(tmpLock == ansLock){
        ifRight1 = 1;
    }
    /*第二种情况，锁不按下*/
    tmpLock = curLock;
    for(int i = 1; i < tmpLock.length(); i++){//从左到右进行处理
        if(tmpLock[i-1] != ansLock[i-1]){//i锁要按下
            minTry2++;
            ChangeLock(i-1);
            ChangeLock(i);
            if(i != tmpLock.length() - 1)
                ChangeLock(i+1);
        }
    }
    if(tmpLock == ansLock){
        ifRight2 = 1;
    }
    if(ifRight1 == 1 && ifRight2 == 1){
        cout << min(minTry1, minTry2) << endl;
    } else if(ifRight1 == 1){
        cout << minTry1 << endl;
    } else if(ifRight2 == 1){
        cout << minTry2 << endl;
    } else{
        cout << "impossible" << endl;
    }
    return 0;
}