#include <iostream>
using namespace std;


//John有一座很长的畜栏，包括N个隔间，这些小隔间的位置为x0到xN-1，均为整数
//John的C头牛每头牛分到一个隔间，牛都希望互相离得远一点，怎样才能使任意两头牛之间的最小距离尽可能的大？


int a[10] = {13, 27, 19, 2, 8, 12, 2, 8, 30, 89};
int b[10];


void Merge(int a[], int s, int m, int e, int tmp[]){
    int pb = 0;
    int p1 = s, p2 = m+1;
    while(p1 <= m && p2 <= e){
        if(a[p1] < a[p2])
            tmp[pb++] = a[p1++];
        else
            tmp[pb++] = a[p2++];
    }
    while(p1 <= m)
        tmp[pb++] = a[p1++];
    while(p2 <= e)
        tmp[pb++] = a[p2++];
    for(int i = 0; i < e-s+1; i++){
        a[s+i] = tmp[i];
    }
}


void MergeSort(int a[], int s, int e, int tmp[]){
    if(s < e){
        int m = s + (e - s)/2;
        MergeSort(a, s, m, tmp);
        MergeSort(a, m+1, e, tmp);
        Merge(a, s, m, e, tmp);
    }
}


int main(){
    int size = sizeof(a)/sizeof(int);
    MergeSort(a, 0, size-1, b);
    for(int i = 0; i < size; i++){
        cout << a[i] << ',';
    }
    cout << endl;
    return 0;
}
