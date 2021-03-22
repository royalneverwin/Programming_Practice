#include <iostream>
#include <algorithm>
using namespace std;


//方法1：将数组排序，对数组每个元素用二分查找看能否找到对应的数
//方法2：将数组排序，设置两个变量i = 0，j = n-1，看a[i] + a[j]，如果大于m就让j-1，如果小于m就让i+1，直至a[i] + a[j] = m或i = j
int main(){
    int Array[10000];
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> Array[i];
    }
    sort(Array, Array + n);
    int x = 0, y = n - 1;
    while(Array[x] + Array[y] != m && x < y){
        if(Array[x] + Array[y] > m){
            y -= 1;
        }
        else if(Array[x] + Array[y] < m){
            x += 1;
        }
    }
    if(Array[x] + Array[y] == m)
        cout << Array[x] << ' ' << Array[y] << endl;
    else
        cout << "No match." << endl;
    return 0;
}