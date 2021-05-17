#include <iostream>
#include <map>
#include <queue>
using namespace std;


struct Patient{
    int priority;
    int time;
    Patient(int p, int t): priority(p), time(t){}
    bool operator < (const Patient& other) const{
        return (priority != other.priority) ? priority < other.priority: time > other.time;
    }
};


priority_queue<struct Patient> pq1;
priority_queue<struct Patient> pq2;
priority_queue<struct Patient> pq3;


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        while(!pq1.empty())
            pq1.pop();
        while(!pq2.empty())
            pq2.pop();
        while(!pq3.empty())
            pq3.pop();
        int n;
        int num = 0;
        string s1;
        int a, b;
        cin >> n;
        for(int j = 0; j < n; j++){
            cin >> s1;
            if(s1 == "IN"){
                num++;
                cin >> a >> b;
                if(a == 1){
                    pq1.push(Patient(b, num));
                } else if(a == 2){
                    pq2.push(Patient(b, num));
                } else if(a == 3){
                    pq3.push(Patient(b, num));
                }
            } else if(s1 == "OUT"){
                cin >> a;
                if(a == 1){
                    if(!pq1.empty()){
                        cout << pq1.top().time << endl;
                        pq1.pop();
                    } else{
                        cout << "EMPTY" << endl;
                    }
                } else if(a == 2){
                    if(!pq2.empty()){
                        cout << pq2.top().time << endl;
                        pq2.pop();
                    } else{
                        cout << "EMPTY" << endl;
                    }
                } else if(a == 3){
                    if(!pq3.empty()){
                        cout << pq3.top().time << endl;
                        pq3.pop();
                    } else{
                        cout << "EMPTY" << endl;
                    }
                }
            }
        }
    }
    return 0;
}