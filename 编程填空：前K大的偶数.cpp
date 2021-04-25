#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>
#include <set>

using namespace std;
class MyQueue
{
public:
    int k;
    priority_queue<int> pq;
    MyQueue(int n):k(n){}
    friend istream & operator >> (istream &is, MyQueue& q){
        int n;
        is >> n;
        if(n % 2 == 0){
            (q.pq).push(n);
        }
        return is;
    }
    friend ostream & operator << (ostream &os, MyQueue q){
        for(int i = 0; i < q.k; i++){
            os << (q.pq).top() << ' ';
            (q.pq).pop();
        }
        return os;
    }
};
int main()
{
    int t;
    cin >> t;
    while(t--) {
        int n, k;
        cin >> n >> k;
        MyQueue q(k);
        for (int i = 0; i < n; ++i)
            cin >> q;
        cout<<q;
        cout << endl;
    }
    return 0;
}