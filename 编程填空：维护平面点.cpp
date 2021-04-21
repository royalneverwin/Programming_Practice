#include <set>
#include <iostream>
#include <string>
using namespace std;

struct myComp{
    bool operator ()(pair<int, int> p1, pair<int, int>p2){
        if(p1.second < 0 || p2.second < 0) {
            return p1.first < p2.first;
        } else if(p1.first < 0 || p2.first < 0){
            return p1.second > p2.second;//注意x1 > x2一定有y1 < y2, 所以这里找的话应该是反过来比
        } else{
            return p1.first < p2.first;
        }
    }
};


int main() {
    string cmd;
    set<pair<int, int>, myComp> S;
    while (cin >> cmd) {
        if (cmd == "A") {
            int x, y;
            cin >> x >> y;
            S.insert(make_pair(x, y));
        } else if (cmd == "Qx") {
            int x;
            cin >> x;
            cout << S.lower_bound(make_pair(x, -1))->second << endl;
        } else if (cmd == "Qy") {
            int y;
            cin >> y;
            cout << S.lower_bound(make_pair(-1, y))->first << endl;
        } else {
            int x, y;
            cin >> x >> y;
            S.erase(make_pair(x, y));
        }
    }
    return 0;
}