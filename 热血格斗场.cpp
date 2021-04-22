#include <iostream>
#include <set>
#include <cmath>
using namespace std;
#define DEBUGx
/*构建一课二叉搜索树, 在插入的时候寻找实力最相近的人*/


class Cmp{
public:
    bool operator()(pair<int, int>p1, pair<int, int>p2){
        return p1.second < p2.second;
    }
};


multiset<pair<int, int>, Cmp> member;


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    pair<int, int>facer(1, 1000000000);
    member.insert(facer);
    int n;
    int id, power;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> id >> power;
        pair<int, int>tmp(id, power);
        auto cur = member.insert(tmp);
#ifdef DEBUG
        for(auto &tmpMember: member){
            cout << tmpMember.first << ' ' << tmpMember.second << endl;
        }
#endif
        if(cur == member.begin()){//如果插入的位置是第一个
            auto next = ++cur;
            cur--;
#ifdef DEBUG
            cout << "cur:" << cur->first << ' ' << cur->second << endl;
            cout << "next:" << next->first << ' ' << next->second << endl;
#endif
            cout << cur->first << ' ' << next->first << endl;
        } else {
            auto prev = --cur;
            cur++;
            auto next = ++cur;
            cur--;
            if (next == member.end()) {//如果插入位置是最后一个
                cout << cur->first << ' ' << prev->first << endl;
#ifdef DEBUG
                cout << "cur:" << cur->first << ' ' << cur->second << endl;
                cout << "prev:" << prev->first << ' ' << prev->second << endl;
#endif
            } else {//如果插入位置在中间
#ifdef DEBUG
                cout << "cur:" << cur->first << ' ' << cur->second << endl;
                cout << "next:" << next->first << ' ' << next->second << endl;
                cout << "prev:" << prev->first << ' ' << prev->second << endl;
#endif
                if (abs(cur->second - prev->second) > abs(cur->second - next->second)) {//cur和next实力差更小
                    cout << cur->first << ' ' << next->first << endl;
                } else if (abs(cur->second - prev->second) < abs(cur->second - next->second)) {//cur和prev实力差更小
                    cout << cur->first << ' ' << prev->first << endl;
                } else {//实力差相同, 和弱的打
                    if (prev->second < next->second) {
                        cout << cur->first << ' ' << prev->first << endl;
                    } else if (prev->second > next->second) {
                        cout << cur->first << ' ' << next->first << endl;
                    } else {
                        cout << "存在实力相同的选手！" << endl;
                    }
                }
            }
        }
    }
    return 0;
}