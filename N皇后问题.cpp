#include <iostream>
#include <cmath>
using namespace std;

//用递归替代多重循环

int N;
int queenPos[100];//用来存放算好的皇后位置，最左上角是（0， 0）


void NQueen(int k){//假定0到k-1行的皇后都已经被摆好，下面摆第k行
  if(k == N){
      for(int i = 0; i < N; i++){
          cout << queenPos[i] + 1 << ' ';
      }
      cout << endl;
      return;
  }
  for(int i = 0; i < N; i++){
      int j;
      for(j = 0; j < k; j++){
          if(queenPos[j] == i || abs(queenPos[j] - i) == abs(k-j)){
              break;
          }
      }
      if(j == k){
          queenPos[k] = i;
          NQueen(k+1);
      }
  }
}


int main(){
    cin >> N;
    NQueen(0);//从第0行开始摆皇后
    return 0;
}