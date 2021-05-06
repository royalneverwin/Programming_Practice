#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
using namespace std;

struct petInBag{
    string name;
    int cnt;
    petInBag(const string& n):name(n){
        cnt = 0;
    }
};

bool operator < (const petInBag& p1, const petInBag& p2){
    return p1.cnt > p2.cnt;
}

int main(){
    int T;
    cin >> T;
    for(int i = 0; i < T; i++){
        int n;
        cin >> n;
        string op, people, pet;
        vector<petInBag> bag;
        unordered_map<string, int> com;
        for(int j = 0; j < n; j++){
            cin >> op >> people >> pet;
            if(op == "C"){//抓精灵
                if(bag.size() < 6){
                    for(auto & tmp : bag){//用来判断抓住时间
                        tmp.cnt++;
                    }
                    bag.push_back(petInBag(pet));
                } else{
                    sort(bag.begin(), bag.end());
                    string tmpPet = (bag.begin())->name;
                    bag.erase(bag.begin());
                    com.insert(pair<string, int>(tmpPet, 1));
                    bag.push_back(petInBag(pet));
                }
            } else{//取精灵
                if(people != "satoshi"){//识别假的
                    cout << "Failed" << endl;
                } else{
                    if(com.count(pet) == 0){
                        cout << "Failed" << endl;
                    } else{
                        sort(bag.begin(), bag.end());
                        string tmpPet = (bag.begin())->name;
                        bag.erase(bag.begin());
                        com.insert(pair<string, int>(tmpPet, 1));
                        com.erase(pet);
                        bag.push_back(petInBag(pet));
                        cout << "Success" << endl;
                    }
                }
            }
        }
        for(auto &tmp: bag){
            cout << tmp.name << endl;
        }
        cout << endl;
        for(auto &tmp:com){
            cout << tmp.first << endl;
        }
        cout << endl;
    }
    return 0;
}