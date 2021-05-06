#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
class CMean {
public:
    int& n;
    int sum;
    int t;
    CMean(int &myAver): n(myAver)  {
        sum = 0;
        t = 0;
    }
    void operator ()(int num){
        t++;
        sum += num;
        n = sum / t;
    }
};


int main(int argc, char* argv[]) {
    int  v;
    int t;
    cin >> t;
    while ( t -- ) {
        cin >> v;
        vector<int> vec;
        while (v) {
            vec.push_back(v);
            cin >> v;
        }
        int myAver = 0;
        for_each(vec.begin(), vec.end(), CMean(myAver));
        cout << myAver << endl;
    }
    return 0;
}