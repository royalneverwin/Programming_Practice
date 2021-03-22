#include <iostream>
using namespace std;


int BinarySearch(int a[], int size, int p){
    int L = 0;//左端点
    int R = size - 1;//右端点
    while(L <= R){
        int mid = L + (R-L)/2;//为了防止L+R过大溢出
        if(p == a[mid])
            return mid;
        else if(p > a[mid])
            L = mid + 1;
        else
            R = mid - 1;
    }
    return -1;
}


//LowerBound, 在包含size个元素的、从小到大排序的int数组a里查找比
//给定整数p小的、下标最大的元素。
int LowerBound(int a[], int size, int p){
    int L = 0;
    int R = size - 1;
    int lastPos = -1;
    while(L <= R){
        int mid = L + (R - L)/2;
        if(a[mid] >= p){
            R = mid + 1;
        }
        else{
            lastPos = mid;
            L = mid+1;
        }
    }
    return lastPos;
}