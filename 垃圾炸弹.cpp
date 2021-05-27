#include <iostream>
#include <vector>
using namespace std;


struct point{
    int x;
    int y;
    int cnt;
    point(int _x, int _y, int _cnt):x(_x), y(_y), cnt(_cnt){}
};


vector<point> p;

int main(){
    int d;
    int n;
    cin >> d >> n;
    int x, y, cnt;
    for(int i = 0; i < n; i++){
        cin >> x >> y >> cnt;
        p.push_back(point(x, y, cnt));
    }
    int sum = 0;
    int sumP = 0;
    int tmpSum;
    for(int i = 0; i <= 1024; i++){
        for(int j = 0; j <= 1024; j++){//注意这里i和j都是从0到1024枚举，因为虽然从d到1024-d枚举清理垃圾最大数目结果一样，但在求清理垃圾最多的投放点数目时会出错
            tmpSum = 0;
            for(auto& tmp: p){
                if(tmp.x <= i + d && tmp.x >= i - d && tmp.y <= j + d && tmp.y >= j - d){
                    tmpSum += tmp.cnt;
                }
            }
            if(sum == tmpSum){
                sumP++;
            }else if(sum < tmpSum){
                sumP = 1;
            }
            sum = max(tmpSum, sum);
        }
    }
    cout << sumP << ' ' << sum << endl;
    return 0;
}