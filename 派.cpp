#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;
const double EPS = 1e-6;
const double pi=3.141592653589;//这里pi的精度给准确些


vector <double> stall;
multiset <double> pie;


int N, F;


double S(int r){
    return r * r * pi;
}


double FindMax(){
    multiset <double>::iterator i = pie.end();
    i--;
    return *i;
}


double FindMin(){
    multiset<double>::iterator i = pie.begin();
    return *i;
}


bool IfDisRight(double dis){
    int sum = 0;
    for(multiset<double>::iterator i = pie.begin(); i != pie.end(); i++) {//判断按照dis来分的话可不可以分成>=F份即可
        sum += int(*i / dis);
    }
    if(sum >= F)
        return true;
    else
        return false;
}



int main(){
    scanf("%d%d", &N, &F);
    int onePie;
    F++;//加上我自己
    for(int i = 0; i < N; i++){
        scanf("%d", &onePie);
        pie.insert(S(onePie));
    }
    double maxDis = FindMax();
    double minDis = FindMin() / F;
    double middle = (maxDis + minDis)/2;//二分查找
    while(fabs(maxDis - minDis) > EPS){
        if(IfDisRight(middle)){
            minDis = middle;
        } else{
            maxDis = middle;
        }
        middle = (maxDis + minDis) / 2;
    }
    cout << setiosflags(ios::fixed) << setprecision(3) << minDis << endl;
    return 0;
}