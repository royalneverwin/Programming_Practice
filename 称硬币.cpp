#include <iostream>
#include <cstring>
using namespace std;


char Left[3][7];//三次称量，每边最多6个硬币
char Right[3][7];
char result[3][5];

bool IsFake(char c, bool light) {//light表示假设假币是否为轻，返回值表示是否是假币
    char *pLeft, *pRight;
    for(int i = 0; i < 3; i++){
        if(light){//如果为轻，假币在的up
            pLeft = Left[i];
            pRight = Right[i];
        }
        else{//如果为重，假币在的down，把称量结果对换，转化成up的情况
            pLeft = Right[i];
            pRight = Left[i];
        }
        //法2：
//        switch(result[i][0]){
//            case 'u':
//                if(strchr(pRight, c) == NULL){
//                    return false;
//                }
//                break;
//            case 'e':
//                if(strchr(pLeft, c) || strchr(pRight, c)){
//                    return false;
//                }
//                break;
//            case 'd':
//                if(strchr(pLeft, c) == NULL){
//                    return false;
//                }
//                break;
//        }
        if(strchr(pLeft, c)){
            if(strcmp(result[i], "down") != 0){
                return false;
            }
        }
        else if(strchr(pRight, c)){
            if(strcmp(result[i], "up") != 0){
                return false;
            }
        }
        else if(strcmp(result[i], "even") != 0){
            return false;
        }
    }
    return true;
}


int main(){
    int Case;
    char c;
    cin >> Case;
    for(int i = 0; i < Case; i++){
        for(int j = 0; j < 3; j++) {
            cin >> Left[j] >> Right[j] >> result[j];
        }
        for(c = 'A'; c <= 'L'; c++){
            if(IsFake(c, true)){
                cout << c << " is the counterfeit coin and it is light.\n";
                break;
            }
            else if(IsFake(c, false)){
                cout << c << " is the counterfeit coin and it is heavy.\n";
                break;
            }
        }
    }
    return 0;
}
