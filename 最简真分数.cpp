#include <iostream>
#include <set>
using namespace std;


struct Point{
    int x;
    int y;
    Point(int xx, int yy):x(xx), y(yy){}
    bool operator < (const Point& other) const{
        return x * other.y < other.x * y;
    }
};


int gcd(int x, int y){
    if(x % y == 0)
        return y;
    return gcd(y, x % y);
}


set<Point> allPoint;
int main(){
    int n;
    int num[610];
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> num[i];
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (num[i] >= num[j])
                continue;
            int g = gcd(num[i], num[j]);
            if(g == 1)
                allPoint.insert(Point(num[i] / g, num[j] / g));
        }
    }
    cout << allPoint.size();
    return 0;
}
