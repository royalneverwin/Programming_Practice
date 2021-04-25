#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cmath>
#include <map>
#include <set>

using namespace std;
class MyFunc
{
public:
    int n;
    MyFunc(int a):n(a){}
    int operator()(int num) const{
        int sum = 1;
        for(int i = 0; i < n; i++){
            sum *= num;
        }
        return sum;
    }
};
int main()
{
    int n;
    cin >> n;
    while(n--) {
        vector<MyFunc> v;
        for (int i = 0; i < 5; ++i)
            v.push_back(MyFunc(i+1));
        int ans = 1;
        for (int i = 0; i < 5; ++i)
        {
            int m;
            cin >> m;
            ans += v[i](m);
        }
        cout << ans <<endl;
    }
}