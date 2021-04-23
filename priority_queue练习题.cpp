#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

const int MAX = 10000000;
const int SQRTMAX = int(sqrt(MAX));


map<int, int> primeCount;

/*对一个正整数n来说，如果它存在[2,n]范围内的质因子，要么这些质因子全部 小于等于 sqrt(n)，要么只存在 一个大于 sqrt(n)的质因子，而其余质因子全部 小于等于 sqrt(n)!!!!*/
vector<int> prime;
class Cmp1{//用于输出优先级最高
public:
    bool operator()(int a, int b){
        if(primeCount[a] == primeCount[b]){
            return a < b;
        } else{
            return primeCount[a] < primeCount[b];
        }
    }
};


priority_queue<int, vector<int>, Cmp1> pqMax1;
priority_queue<int, vector<int>, Cmp1> pqMax2;


bool Prime(int index){
    if(index == 1){
        return false;
    } else{
        for(int i = 2; i*i <= index; i++){
            if(index % i == 0){
                return false;
            }
        }
        return true;
    }
}


void calculatePrime(){
    for(int i = 1; i <= SQRTMAX; i++){
        if(Prime(i)){
            prime.push_back(i);
        }
    }
}


int Calculate(int index){
    int prevIndex = index;
    if(index == 1 || index == 2){
        return 0;
    } else{
        int sum = 0;
        for(auto &i: prime){
            if(i >= index){
                break;
            }
            if(index % i == 0){
                sum++;
                while(index % i == 0){//将index中的质因子全部去掉
                    index /= i;
                }
            }
        }
        if(index != 1 && index != prevIndex){//有一个大于sqrtMAX的质因子, 且index有质因子
            sum++;
        }
        return sum;
    }
}


int main(){
    calculatePrime();
    int num;
    int ele;
    int flag = 1;//flag = 1, 代表元素在pqMax1中, 求最小将元素从Max1移动到Max2; flag = 0则反过来
    cin >> num;
    for(int i = 0; i < num; i++){
        for(int j = 0; j < 10; j++){
            cin >> ele;
            primeCount[ele] = Calculate(ele);
            if(flag) {
                pqMax1.push(ele);
            } else{
                pqMax2.push(ele);
            }
        }
        /*输出最小的, 通过将元素在Max1和Max2之间平移得到*/
        if(flag){
            cout << pqMax1.top() << ' ';//输出最大
            pqMax1.pop();//丢弃
            while(pqMax1.size() != 1){
                pqMax2.push(pqMax1.top());
                pqMax1.pop();
            }
            cout << pqMax1.top() << endl;//输出最小
            pqMax1.pop();//丢弃
            flag = 0;
        } else{
            cout << pqMax2.top() << ' ';//输出最大
            pqMax2.pop();//丢弃
            while(pqMax2.size() != 1){
                pqMax1.push(pqMax2.top());
                pqMax2.pop();
            }
            cout << pqMax2.top() << endl;//输出最小
            pqMax2.pop();//丢弃
            flag = 1;
        }
    }
    return 0;
}