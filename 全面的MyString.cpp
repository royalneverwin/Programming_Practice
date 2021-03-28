#include <cstdlib>
#include <iostream>
using namespace std;
//int strlen(const char * s)
//{	int i = 0;
//    for(; s[i]; ++i);
//    return i;
//}
//void strcpy(char * d,const char * s)
//{
//    int i = 0;
//    for( i = 0; s[i]; ++i)
//        d[i] = s[i];
//    d[i] = 0;
//}
int strcmp(const char * s1,const char * s2)
{
    for(int i = 0; s1[i] && s2[i] ; ++i) {
        if( s1[i] < s2[i] )
            return -1;
        else if( s1[i] > s2[i])
            return 1;
    }
    return 0;
}

//void strcat(char * d,const char * s)
//{
//    int len = strlen(d);
//    strcpy(d+len,s);
//}

class MyString
{
    char * p;
public:
    MyString(const char * s) {//用字符串初始化
        if( s) {
            p = new char[strlen(s) + 1];
            strcpy(p,s);
        }
        else
            p = NULL;

    }

    MyString(const MyString &s){//用MyString初始化
        if( s.p){
            p = new char[strlen(s.p)+1];
            strcpy(p, s.p);
        }
        else{
            p = NULL;
        }
    }

    MyString(){//空字符串初始化
        p = new char;
        p[0] = '\0';
    }

    ~MyString() { if(p) delete [] p; }//析构

    void Copy(const char *s){//成员函数Copy
        delete []p;
        if(s){
            p = new char[strlen(s)+1];
            strcpy(p, s);
        }
        else{
            p = NULL;
        }
    }

    MyString & operator = (const MyString &s){//重载=，=MyString
        if(&s == this){
            return *this;
        }
        Copy(s.p);
        return *this;
    }

    MyString & operator = (const char *s){//重载=，=字符串
        Copy(s);
        return *this;
    }

    MyString operator + (MyString &s){//重载+运算符，+MyString
        MyString tmp = *this;
        strcat(tmp.p, s.p);
        return tmp;
    }

    MyString operator + (const char *s){//重载+运算符，+char *
        MyString tmp = *this;
        strcat(tmp.p, s);
        return tmp;
    }

    char & operator [](int n){//重载[]运算符
        return p[n];
    }

    MyString operator +=(const char *s){//重载+=运算符
        strcat(p, s);
        return *this;
    }

    MyString operator () (int start, int end){
        MyString tmp = p + start;
        tmp.p[end] = '\0';
        return tmp;

    }

    bool operator < (const MyString &s){//重载 < 运算符
        int l1 = strlen(p);
        int l2 = strlen(s.p);
        for(int i = 0; i <= min(l1, l2); i++){
            if(p[i] < s.p[i]){
                return true;
            }
            else if(p[i] > s.p[i]){
                return false;
            }
        }
        return false;
    }

    bool operator == (const MyString &s){ //重载==运算符
        int l1 = strlen(p);
        int l2 = strlen(s.p);
        for(int i = 0; i <= min(l1, l2); i++){
            if(p[i] < s.p[i]){
                return false;
            }
            else if(p[i] > s.p[i]){
                return false;
            }
        }
        return true;
    }

    bool operator > (const MyString &s){//重载 > 运算符
        int l1 = strlen(p);
        int l2 = strlen(s.p);
        for(int i = 0; i <= min(l1, l2); i++){
            if(p[i] < s.p[i]){
                return false;
            }
            else if(p[i] > s.p[i]){
                return true;
            }
        }
        return false;
    }

    friend MyString operator + (const char *s, MyString &w){//重载+运算符为友元函数
        MyString tmp(s);
        strcat(tmp.p, w.p);
        return tmp;
    }

    friend ostream & operator <<(ostream & os, const MyString &s){//重载输出运算符
        os << s.p;
        return os;
    }

};


int CompareString( const void * e1, const void * e2)
{
    MyString * s1 = (MyString * ) e1;
    MyString * s2 = (MyString * ) e2;
    if( * s1 < *s2 )
        return -1;
    else if( *s1 == *s2)
        return 0;
    else if( *s1 > *s2 )
        return 1;
}
int main()
{
    MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
    MyString SArray[4] = {"big","me","about","take"};
    cout << "1. " << s1 << s2 << s3<< s4<< endl;
    s4 = s3;
    s3 = s1 + s3;
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    cout << "6. " << s1[2] << endl;
    s2 = s1;
    s1 = "ijkl-";
    s1[2] = 'A' ;
    cout << "7. " << s2 << endl;
    cout << "8. " << s1 << endl;
    s1 += "mnop";
    cout << "9. " << s1 << endl;
    s4 = "qrst-" + s2;
    cout << "10. " << s4 << endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    cout << "11. " << s1 << endl;
    qsort(SArray,4,sizeof(MyString),CompareString);
    for( int i = 0;i < 4;i ++ )
        cout << SArray[i] << endl;
    //s1的从下标0开始长度为4的子串
    cout << s1(0,4) << endl;
    //s1的从下标5开始长度为10的子串
    cout << s1(5,10) << endl;
    return 0;
}