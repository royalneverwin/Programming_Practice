#include <iostream>
#include <cstring>
using namespace std;


//枚举所有可能有2^30种，太多了。只需要枚举其一部分的所有情况便可以唯一确定剩下部分的情况
//这一部分就是第一行。第一行灯的灭亮决定第二行的开关，第二行的灭亮又决定第三行的开关，以此类推


char orLights[5];//存放灯的初始状态
char lights[5];//存放变化中的灯的状态
char result[5];//存放最终结果


int GetBit(char c, int i){//得到c的第i位
    return (c >> i) & 1;
}


void SetBit(char & c, int i, int v){//使c的第i位设成v
    if(v){
        c |= (1 << i);
    }
    else{
        c &= ~(1 << i);
    }
}


void FlipBit(char & c, int i){//使c的第i位翻转
    c ^= (1 << i);
}


void OutputResult(int t, char result[]){
    cout << "PUZZLE #" << t << endl;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 6; j++){
            cout << GetBit(result[i], j);
            if(j < 5){
                cout << ' ';
            }
        }
        cout << endl;
    }
}


int main(){
    int n;
    int s;
    int switchs;
    cin >> n;
    for(int i = 0; i < n ;i++){
        //存数据小技巧：因为数据只有0和1，可以用位存，一个char一维数组即可存下所有数据
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 6; k++){
                cin >> s;
                SetBit(orLights[j], k, s);
            }
        }
        //枚举小技巧：如果要枚举k种如题所示情况，只需要用一个int类型的整数，让它从0到k-1，这样每一位就代表该条件下灯是否按下
        for(int j = 0; j < 64; j++){
            switchs = j;
            memcpy(lights, orLights, sizeof(orLights));//每次验证一个可能时将lights状态初始化
            for(int k = 0; k < 5; k++){
                result[k] = switchs;
                for(int l = 0; l < 6; l++){//处理该行lights变化
                    if(GetBit(switchs, l)){
                        if(l > 0)
                            FlipBit(lights[k], l-1);
                        FlipBit(lights[k], l);
                        if(l < 5)
                            FlipBit(lights[k], l+1);
                    }
                }
                if(k < 4)//处理下一行lights变化
                    lights[k+1] ^= switchs;//如果switchs对应的位是0，就不变；如果是1，就变
                switchs = lights[k];//更新switchs
            }
            if(lights[4] == 0){
                OutputResult(i+1, result);
                break;
            }
        }
    }


}