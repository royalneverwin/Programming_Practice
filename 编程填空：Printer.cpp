#include<iostream>
#include<algorithm>
#include<vector>
#include<bitset>

using namespace std;


class Printer {
public:
    int x;
    Printer(int n):x(n){}
    void operator () (int pi){
        if(pi > x){
            cout << pi << ',';
        }
    }
    void operator()(string pi){
        if((pi).length() > x){
            cout << pi << ',';
        }
    }
};
    int main(){

        int t;
        cin >> t;
        while(t--) {
            int n,x;
            cin>>x>>n;

            vector<int> intVec;
            for(int i = 0;i < n; ++i) {
                int y;
                cin >> y;
                intVec.push_back(y);
            }
            for_each(intVec.begin(), intVec.end(), Printer(x));
            cout<<endl;

            vector<string> strVec;
            for(int i = 0;i < n; ++i) {
                string str;
                cin >> str;
                strVec.push_back(str);
            }
            for_each(strVec.begin(), strVec.end(), Printer(x));
            cout<<endl;
        }
        return 0;
    }