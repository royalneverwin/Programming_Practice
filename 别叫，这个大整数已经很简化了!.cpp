#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int MAX = 110;



class CHugeInt {
public:
    char HT[210];

    CHugeInt(const int n){//用数字初始化
        sprintf(HT, "%d", n);
    }

    CHugeInt(const char *s){//用字符串初始化
        strcpy(HT, s);
    }

    CHugeInt(){
        strcpy(HT, "0");
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




int  main()
{
    char s[210];
    int n;

    while (cin >> s >> n) {
        CHugeInt a(s);
        CHugeInt b(n);

        cout << a + b << endl;
        cout << n + a << endl;
        cout << a + n << endl;
        b += n;
        cout  << ++b << endl;
        cout << b++ << endl;
        cout << b << endl;
    }
    return 0;
}