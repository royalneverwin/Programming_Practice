#include<iostream>
using namespace std;
template<class T>
// 在此处补充你的代码
void f(T* array, int cnt){
    T tmp[cnt];
    for(int i = 0; i < cnt; i++){
        tmp[cnt - i - 1] = array[i];
    }
    for(int i = 0; i < cnt; i++){
        array[i] = tmp[i];
    }
}
int main()
{
    int a[5] = { 10, 21, 34, 4, 50 };
    double d[6] = { 4.1, 11.1, 10.1, 9.1, 8.1, 7.1 };
    f(a, 5);
    f(d, 6);
    for (int i = 0; i < 5; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    for (int j = 0; j < 6; j++)
    {
        cout << d[j] << " ";
    }
    cout << endl;
    return 0;
}