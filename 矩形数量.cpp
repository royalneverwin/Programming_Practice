#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int t;
int n;
struct Point{
    int x;
    int y;
    Point(int xx, int yy): x(xx), y(yy){}
    bool operator < (const Point& p) const{
        return x == p.x ? y < p.y: x < p.x;
    }
};
vector<Point> pArray;
vector<Point> newArray;
bool isRec(int x1, int x2, int x3, int x4){
    Point p1 = newArray[x1];
    Point p2 = newArray[x2];
    Point p3 = newArray[x3];
    Point p4 = newArray[x4];
    if(p1.x == p2.x && p1.y == p3.y && p3.x == p4.x && p4.y == p2.y){
        return true;
    }
    else{
        return false;
    }
}
int main(){
    int a, b;
    cin >> t;
    while(t--) {
        pArray.clear();
        newArray.clear();
        int cnt = 0;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a >> b;
            pArray.push_back(Point(a, b));
        }
        sort(pArray.begin(), pArray.end());
        Point prev(-1, -1);
        for(auto&p: pArray){
            if(p.x != prev.x || p.y != prev.y){
                prev = p;
                newArray.push_back(p);
            }
        }
        if(newArray.size() < 4){
            cout << 0 << endl;
            continue;
        }
        for(int i = 0; i < newArray.size()-3; i++){
            for(int j = i+1; j < newArray.size()-2; j++){
                for(int k = j+1; k < newArray.size()-1; k++){
                    for(int l = k+1; l < newArray.size(); l++){
                        if(isRec(i, j, k, l)){
                            cnt++;
                        }
                    }
                }
            }
        }
        cout << cnt << endl;
    }
    return 0;
}