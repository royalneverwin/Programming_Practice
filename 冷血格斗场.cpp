#include <iostream>
#include <set>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define DEBUGx
/*构建一课二叉搜索树, 在插入的时候寻找实力最相近的人*/



typedef map<int, vector<int>> mmid;
mmid member;//first代表实力, vector代表有相同实力的id集合


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int n;
    int id, power;
    cin >> n;
    member[1000000000].push_back(1);
    for(int i = 0; i < n; i++) {
        cin >> id >> power;
        member[power].push_back(id);//如果存在vector, push_back, 如果不存在vector, 创建一个vector再push_back
#ifdef DEBUG
        for(auto &pmember:member){
            for(auto &pointid: pmember.second){
                cout << pointid << ' ';
            }
            cout << endl;
        }
#endif
        if (member[power].size() > 1) {//如果存在实力相同选手, 一定和实力相同选手打
            sort(member[power].begin(), member[power].end());
            auto pID = member[power].begin();
            if (*pID == id) {//防止id最小的是新成员
                pID++;
            }
            cout << id << ' ' << *pID << endl;
        }
#ifdef DEBUG
#endif
        else {//不存在实力相同选手
            auto prev = member.find(power);
            auto next = prev;
            if(prev == member.begin()) {//cur是实力最小的
                next++;
                sort((next->second).begin(), (next->second).end());
                cout << id << ' ' << *((next->second).begin()) << endl;
            } else {
                prev--;
                next++;
                if(next == member.end()){//cur是实力最大的
                    sort((prev->second).begin(), (prev->second).end());
                    cout << id << ' ' << *((prev->second).begin()) << endl;
                } else{
                    if(abs(prev->first - power) > abs(next->first - power)){//next差距小
                        sort((next->second).begin(), (next->second).end());
                        cout << id << ' ' << *((next->second).begin()) << endl;
                    } else if(abs(prev->first - power) < abs(next->first - power)){//prev差距小
                        sort((prev->second).begin(), (prev->second).end());
                        cout << id << ' ' << *((prev->second).begin()) << endl;
                    } else {
                        sort((next->second).begin(), (next->second).end());
                        sort((prev->second).begin(), (prev->second).end());
                        if(*((next->second).begin()) > *((prev->second).begin())){
                            cout << id << ' ' << *((prev->second).begin()) << endl;
                        } else{
                            cout << id << ' ' << *((next->second).begin()) << endl;
                        }
                    }
                }
            }
        }
#ifdef DEBUG
#endif
    }
    return 0;
}