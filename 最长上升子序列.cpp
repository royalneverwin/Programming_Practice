#include <iostream>
#include <algorithm>
using namespace std;


const int MAX = 21;
int n;


double a[MAX];


int maxLen[MAX];


int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        maxLen[i] = 1;
    }
    for(int i = 2; i <= n; i++){
        for(int j = 1; j < i; j++){
            if(a[i] <= a[j]){
                maxLen[i] = max(maxLen[i], maxLen[j]+1);
            }
        }
    }
    cout << * max_element(maxLen+1, maxLen+n+1);
    return 0;
}