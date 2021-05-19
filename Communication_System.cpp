#include <iostream>
#include <set>
#include <map>
#include <iomanip>
using namespace std;


//我们只需要遍历所有总体带宽，计算B/P最大值即可


struct Facility{
    int kind;
    int seller;
    int B;
    int P;
    Facility(int k, int s, int b, int p):kind(k),seller(s), B(b), P(p){}
    bool operator < (const Facility& f) const{
        return P < f.P;
    }
};



set<int> B;


map<int, set<Facility>> total;


int main(){
    int t;
    cin >> t;
    int n;
    int cnt;
    int b, p;
    double result;
    int sumP;
    while(t--){
        B.clear();
        total.clear();
        result = 0;
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> cnt;
            set<Facility> f;
            total[i] = f;
            for(int j = 1; j <= cnt; j++){
                cin >> b >> p;
                total[i].insert(Facility(i, j, b, p));
                B.insert(b);
            }
        }
        for(auto tmpB: B){
            sumP = 0;
            int flag = 1;
            for(int i = 1; i <= n; i++){
                int flag1 = 0;
                for(auto& tmpF: total[i]){
                    if(tmpF.B >= tmpB){
                        flag1 = 1;
                        sumP += tmpF.P;
                        break;
                    }
                }
                if(flag1 == 0){
                    flag = 0;
                    break;
                }
            }
            if(flag){//存在
                if(result < float(tmpB) / sumP){
                    result = float(tmpB) / sumP;
                }
            }
        }
        cout << setiosflags(ios::fixed) << setprecision(3) << result << endl;
    }
    return 0;
}