#include <iostream>
using namespace std;
const int MAX = 100010;


long long myArray[MAX];
long long myCopy[MAX];


long long cnt = 0;


void Merge(long long *array1, long long *array2, int begin, int middle, int end){
    int begin1 = begin, begin2 = middle+1;
    int index = begin;
    while(begin1 <= middle && begin2 <= end){
        if(array1[begin1] < array1[begin2]) {
            array2[index++] = array1[begin1++];
        } else{
            array2[index++] = array1[begin2++];
            cnt += middle - begin1 + 1;//注意这里是middle - begin1 + 1
        }
    }
    while(begin1 <= middle){
        array2[index++] = array1[begin1++];
    }
    while(begin2 <= end){
        array2[index++] = array1[begin2++];
    }
    for(int i = begin; i <= end; i++){//merge完再拷贝回去
        array1[i] = array2[i];
    }
}


void MergeSort(long long *array1, long long *array2, int begin, int end){
    if(begin < end){
        int middle = (begin + end) / 2;
        MergeSort(array1, array2, begin, middle);
        MergeSort(array1, array2, middle+1, end);
        Merge(array1, array2, begin, middle, end);
    }
}


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> myArray[i];
    }
    MergeSort(myArray, myCopy, 0, n-1);
    cout << cnt << endl;
    return 0;
}