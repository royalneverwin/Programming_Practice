#include <iostream>
#include <set>
#include <string>
using namespace std;


multiset<int> Zset;


int ifAdd[100010] = {0};

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int n;
    cin >> n;
    string s;
    int num;
    for(int i = 0; i < n; i++){
        cin >> s >> num;
        if(s == "add"){
            Zset.insert(num);
            ifAdd[num] = 1;
            cout << Zset.count(num) << endl;
        } else if(s == "ask"){
            cout << ifAdd[num] << ' ' << Zset.count(num) << endl;
        } else if(s == "del"){
            cout << Zset.count(num) << endl;
            while(Zset.find(num) != Zset.end()){
                Zset.erase(Zset.find(num));
            }
        } else{
            cout << "Wrong String." << endl;
        }
    }
    return 0;
}