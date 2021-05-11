#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

struct petWithCnt{
    string name;
    int cnt;//用来判断在背包中存放时间长短
    petWithCnt(const string& n, int _cnt):name(n), cnt(_cnt){}
};

bool operator < (const petWithCnt& p1, const petWithCnt& p2){
    return p1.cnt > p2.cnt;
}

int main(){
    int T;
    cin >> T;
    for(int i = 0; i < T; i++){
        int n;
        cin >> n;
        string op, people, pet;
        map<string, priority_queue<petWithCnt>> allBag;
        map<string, vector<string>> allCom;
        for(int j = 1; j <= n; j++){
            cin >> op >> people >> pet;
            if(allBag.count(people) == 0){
                priority_queue<petWithCnt> newBag;
                allBag.insert(pair<string, priority_queue<petWithCnt>> (people, newBag));
            }
            if(allCom.count(people) == 0){
                vector<string> newCom;
                allCom.insert(pair<string, vector<string>> (people, newCom));
            }
            if(op == "C"){//抓精灵
                if(allBag[people].size() < 6){
                    allBag[people].push(petWithCnt(pet, j));//cnt = j
                } else{
                    string pet2com = (allBag[people].top()).name;
                    allBag[people].pop();
                    allCom[people].push_back(pet2com);
                    allBag[people].push(petWithCnt(pet, j));
                }
            } else{//取精灵
                auto p = find(allCom[people].begin(), allCom[people].end(), pet);
                if(p == allCom[people].end()){
                    cout << "Failed" << endl;
                } else{
                    string pet2com = (allBag[people].top()).name;
                    allBag[people].pop();
                    allBag[people].push(petWithCnt(pet, j));
                    allCom[people].erase(p);
                    allCom[people].push_back(pet2com);
                    cout << "Success" << endl;
                }

            }
        }
    }
    return 0;
}