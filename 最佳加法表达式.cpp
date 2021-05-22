#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;


int m;

char maxInt[51];


/*之前写的CHugeInt，直接拿来用了*/
class CHugeInt {
public:
    char HT[51];

    CHugeInt(const int n){//用数字初始化
        sprintf(HT, "%d", n);
    }

    CHugeInt(const char *s){//用字符串初始化
        strcpy(HT, s);
    }

    CHugeInt(){
        strcpy(HT, "0");
    }

    CHugeInt substr(int end, int start){ //取HugeInt第start位到end的位组成数
        char tmp[51];
        for(int i = start; i <= end; i++){
            tmp[i - start] = HT[i];
        }
        tmp[end - start + 1] = '\0';
        return CHugeInt(tmp);
    }

    CHugeInt & operator = (const CHugeInt & a){//重载=
        strcpy(HT, a.HT);
        return *this;
    }

    CHugeInt operator + (const CHugeInt & b){//重载+，做到两个HugInt相加
        return Add(*this, b);
    }

    friend CHugeInt operator + (int b, const CHugeInt &a){//重载+，做到HugeInt和int相加
        CHugeInt tmp(b);
        return Add(a, tmp);
    }

    friend ostream & operator << (ostream &os, const CHugeInt &a){//重载流输出运算符
        os << a.HT;
        return os;
    }



    CHugeInt operator += (int a){//重载+=运算符
        CHugeInt tmp(a);
        *this = Add(*this, tmp);
        return *this;
    }

    CHugeInt operator ++(){//重载前置++运算符
        CHugeInt tmp(1);
        *this = Add(*this, tmp);
        return *this;
    }

    CHugeInt operator ++ (int){//重载后置++运算符
        CHugeInt tmp(1);
        CHugeInt tmp2 = *this;
        *this = Add(*this, tmp);
        return tmp2;
    }

    bool operator < (const CHugeInt &other) const{
        int ia = strlen(HT) + 1;
        int ib = strlen(other.HT) + 1;
        if(ia != ib){
            return ia < ib;
        }
        for(int i = 0; i < ia; i++){
            if(HT[i] != other.HT[i]){
                return HT[i] < other.HT[i];
            }
        }
        return false; //相等
    }


    friend CHugeInt Add(const CHugeInt &a, const CHugeInt &b){//进行两个HugeInt的加法
        CHugeInt tmp;
        int addOne = 0;
        int ia = strlen(a.HT) - 1;
        int ib = strlen(b.HT) - 1;
        int it = max(ia, ib);
        int lt = it + 1;
        tmp.HT[lt] = '\0';
        char addResult;
        char tmpa;
        char tmpb;
        while(ia >= 0 || ib >= 0){
            if(ia >= 0)
                tmpa = a.HT[ia];
            else
                tmpa = '0';

            if(ib >= 0)
                tmpb = b.HT[ib];
            else
                tmpb = '0';
            addResult = tmpa + (tmpb - '0') + addOne;
            addOne = 0;
            if(addResult > '9'){//如果需要进位
                addResult = addResult - 9 - 1;
                addOne = 1;
            }
            ia--;
            ib--;
            tmp.HT[it] = addResult;
            it--;
        }
        if(addOne){//最高项需要进位，特殊处理
            for(int i = lt; i >= 0; i--){
                tmp.HT[i+1] = tmp.HT[i];
            }
            tmp.HT[0] = '1';
        }
        return tmp;
    }
};


CHugeInt sumInt[51][51]; //x位的大整数被y个加号分所得到的最小值


CHugeInt GetSum(CHugeInt num, int x, int y) {//求得CHugeInt前x位// 被y个加号分所得到的最大值
    CHugeInt max(maxInt);
    if(y == 0){
        char tmp[51];
        strcpy(tmp, num.HT);
        tmp[x] = '\0';
        return CHugeInt(tmp);
    }
    for (int i = 1; i <= x - y; i++) { //假设最后一个数位数为i，前面所有的数位数为x-i
        if( sumInt[x-i][y-1] + num.substr(x-1, x-i) < max){
            max = sumInt[x-i][y-1] + num.substr(x-1, x-i);
        }
    }
//    cout << x << ' ' << y << ' ' << ' ' << max << endl;
    return max;
}


int main(){
    char s[51];
    for(int i = 0; i < 50; i++){
        maxInt[i] = '9';
    }
    maxInt[50] = '\0';
    while(cin >> m){
        cin >> s;
        CHugeInt num(s);
        for(int i = 1; i <= strlen(num.HT); i++){
            for(int j = 0; j <= i - 1 && j <= m; j++){
                sumInt[i][j] = GetSum(num, i , j);
            }
        }
        cout << sumInt[strlen(num.HT)][m] << endl;
    }
    return 0;
}