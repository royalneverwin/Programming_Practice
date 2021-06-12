#include <iostream>
using namespace std;


int m;
int s;
int people[65536];
const double eps = 1e-6;


bool dfs(int cur, int left, int index, double sum){ //从小到大分配时间，cur代表目前可分配的最小时间，left代表还剩多长时间，index代表分配到了第几个人, sum代表目前总共学了多少
    if(sum + 1.0 / left  > 1 - eps && sum  + 1.0 / left < 1 + eps){ //注意这里只是给一个范围，不要求完全等于1
        people[index] = left;
        index++;
        cout << index;
        for(int i = 0; i < index; i++)
            cout << ' ' << people[i];
        cout << endl;
        return true;
    }
    if(index * index >= s) //最多只可能有sqrt(s)个人
        return false;
    if(sum + 1.0 / cur > 1 + eps) //肯定会大于1
        return false;
    for(int i = cur; i <= left; i++){
        people[index] = i;
        if(dfs(i, left - i, index + 1, sum + 1.0 / i)){
            return true;
        }
    }
    return false;
}


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin >> m;
    while(m--){
        cin >> s;
        if(s == 1)
            cout << "1 1" << endl;
        else{
            if(!dfs(2, s, 0, 0)){//一个人至少分配2时间
                cout << -1 << endl;
            }
        }
    }
}