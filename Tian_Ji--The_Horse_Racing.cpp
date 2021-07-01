#include <iostream>
#include <set>
#include <algorithm>
using namespace std;


// 贪心方法：从大到小排序，如果tian最好的马比king的好，就直接比。
// 如果tian最好的马比king的差，就用tian最差的马比king最好的。
// 如果tian最好的马跟king的一样，就要先比较king和tian最差的马，找到第一个tian最差的马比king最差的马差的，和king最好的马比。
int tian[1010];
int tianBegin;
int tianEnd;
int king[1010];
int kingBegin;
int kingEnd;
int winCnt;

int n;
int main(){
    cin >> n;
    while(n){
        winCnt = 0;
        tianBegin = kingBegin = 0;
        tianEnd = kingEnd = n-1;
        for(int i = 0; i < n; i++){
            cin >> tian[i];
        }
        for(int i = 0; i < n; i++){
            cin >> king[i];
        }
        sort(tian, tian + n, greater<int>());
        sort(king, king + n, greater<int>());
        for(int i = 0; i < n; i++){
            if(tianBegin == tianEnd){
                if(tian[tianBegin] > king[kingBegin]) {
                    winCnt++;
                }
                else if(tian[tianBegin] < king[kingBegin]) {
                    winCnt--;
                }
            }
            else {
                if (tian[tianBegin] > king[kingBegin]) {
                    winCnt++;
                    tianBegin++;
                    kingBegin++;
                } else if(tian[tianBegin] > king[kingBegin]) {
                    winCnt--;
                    tianEnd--;
                    kingBegin++;
                }
                else{
                    if(tian[tianEnd] > king[kingEnd]){
                        winCnt++;
                        tianEnd--;
                        kingEnd--;
                    }
                    else{
                        if(tian[tianEnd] < king[kingBegin])
                            winCnt--;
                        tianEnd--;
                        kingBegin++;
                    }
                }
            }
        }
        cout << winCnt * 200 << endl;
        cin >> n;
    }
    return 0;
}