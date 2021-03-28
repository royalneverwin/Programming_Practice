#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


const double eps = 1e-6;

struct candy {
    int value;
    int weight;
};

vector<struct candy> Candy;


bool operator < (const struct candy c1, const struct candy c2){//注意这里要比较每单位重量candy的价值大小
    return double(c1.value)/c1.weight - double(c2.value)/c2.weight > eps;
}


int main(){
    int n, w;
    cin >> n >> w;
    for(int i = 0; i < n; i++){
        struct candy tmp;
        cin >> tmp.value >> tmp.weight;
        Candy.push_back(tmp);
    }
    sort(Candy.begin(), Candy.end());//按照从大到小排序

    double totalValue = 0;
    int totalW = 0;
    for(auto &i: Candy){//遍历vector
        if(totalW + i.weight <= w){
            totalValue += i.value;
            totalW += i.weight;
        }
        else{
            totalValue += ((i.value)  * double(w - totalW) / i.weight);
            break;
        }
    }

    printf("%.1f\n", totalValue);
    return 0;
}