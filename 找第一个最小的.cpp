#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class T1, class T2, class T3>
T1 FindFirstLess(T1 begin, T1 end, T2 m, T3 op){
    for(T1 i = begin; i != end; i++){
        if(op(*i, m)){
            return i;
        }
    }
    return end;
}


int main()
{
    int t;
    cin >> t;
    while(t--) {
        int n ;
        string type;
        cin >> n >> type;
        vector<int> vi;
        vector<string> vs;
        if( type == "N") {
            int a,m;
            for(int i = 0;i < n  - 1; ++i) {

                cin >> a;
                vi.push_back(a);
            }
            cin >> m;
            vector<int>::iterator p = FindFirstLess(vi.begin(),vi.end(),m,less<int>());
            if( p!= vi.end())
                cout << * p << endl;
            else
                cout << "Not Found" << endl;

        }
        else {
            string a,m;
            for(int i = 0;i < n - 1; ++i) {
                cin >> a;
                vs.push_back(a);
            }
            cin >> m;
            vector<string>::iterator p = FindFirstLess(vs.begin(),vs.end(),m,less<string>());
            if( p!= vs.end())
                cout << * p << endl;
            else
                cout << "Not Found" << endl;

        }
    }
    return 0;
}