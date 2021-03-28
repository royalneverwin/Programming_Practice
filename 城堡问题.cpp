#include <iostream>
using namespace std;
//深搜


int R, C;//行列数
int rooms[60][60];
int color[60][60];//方块是否染过色的标记
int maxRoomArea = 0, roomNum = 0;
int roomArea;


void Dfs(int i, int k){//从第i行第k个开始深搜
    if(color[i][k])//已经被标记了
        return;
    ++roomArea;
    color[i][k] = roomNum;
    if((rooms[i][k]&1) == 0)
        Dfs(i, k-1);//向西走
    if((rooms[i][k]&2) == 0)
        Dfs(i-1, k);//向北走
    if((rooms[i][k]&4) == 0)
        Dfs(i, k+1);//向东走
    if((rooms[i][k]&8) == 0)
        Dfs(i+1, k);//向南走
}


int main(){
    cin >> R >> C;
    for(int i = 0; i < R; i++){
        for(int k = 0; k < C; k++){
            cin >> rooms[i][k];
        }
    }
    for(int i = 0; i < R; i++){
        for(int k = 0; k < C; k++){
            if(!color[i][k]){
                ++roomNum;//重新涂色
                roomArea = 0;//room面积重置为0
                Dfs(i, k);
                maxRoomArea = max(maxRoomArea, roomArea);
            }
        }
    }
    cout << roomNum << endl;
    cout << maxRoomArea << endl;
}