#include <iostream>
#include <cstring>
#include <queue>
using namespace std;


struct Point{
    int B;
    struct Point *father;
    int x;
    int y;
    struct Point *next;//用于正向输出路径
};
struct Point maze[6][6];
int visited[6][6];
queue<struct Point> q;


void bfs(){
    q.push(maze[0][0]);
    visited[0][0] = 1;
    while(!q.empty()){
        struct Point tmp = q.front();
        q.pop();
        if(tmp.x == 4 && tmp.y == 4){
            return;
        }
        if(tmp.x != 0){//点不在第1行
            if(maze[tmp.x-1][tmp.y].B == 0 && !visited[tmp.x-1][tmp.y]){
                maze[tmp.x-1][tmp.y].father = &(maze[tmp.x][tmp.y]);
                q.push(maze[tmp.x-1][tmp.y]);
                visited[tmp.x-1][tmp.y] = 1;
            }
        }
        if(tmp.x != 4){//点不在第5行
            if(maze[tmp.x+1][tmp.y].B == 0 && !visited[tmp.x+1][tmp.y]){
                maze[tmp.x+1][tmp.y].father = &(maze[tmp.x][tmp.y]);
                q.push(maze[tmp.x+1][tmp.y]);
                visited[tmp.x+1][tmp.y] = 1;
            }
        }
        if(tmp.y != 0){//点不在第1列
            if(maze[tmp.x][tmp.y-1].B == 0 && !visited[tmp.x][tmp.y-1]){
                maze[tmp.x][tmp.y-1].father = &(maze[tmp.x][tmp.y]);
                q.push(maze[tmp.x][tmp.y-1]);
                visited[tmp.x][tmp.y-1] = 1;
            }
        }
        if(tmp.y != 4){//点不在第5列
            if(maze[tmp.x][tmp.y+1].B == 0 && !visited[tmp.x][tmp.y+1]){
                maze[tmp.x][tmp.y+1].father = &(maze[tmp.x][tmp.y]);
                q.push(maze[tmp.x][tmp.y+1]);
                visited[tmp.x][tmp.y+1] = 1;
            }
        }
    }
}


void ShowWay(){
    struct Point *p = &(maze[4][4]);
    struct Point *tmp = NULL;
    while(p->father != NULL){//将路径倒过来
        tmp = p;
        p = tmp->father;
        p->next = tmp;
    }
    p = &(maze[0][0]);
    while(p->x != 4 || p->y != 4){//顺序输出
        cout << '(' << p->x <<", " << p->y << ')' << endl;
        p = p->next;
    }
    cout << "(4, 4)";
}


int main(){
    memset(visited, 0, sizeof(visited));
    for(int i  = 0; i < 5; i++){//赋值+初始化
        for(int j = 0; j < 5; j++){
            cin >> maze[i][j].B;
            maze[i][j].x = i;
            maze[i][j].y = j;
            maze[i][j].father = NULL;
            maze[i][j].next = NULL;//用于输出路径
        }
    }
    bfs();
    ShowWay();
    return 0;
}
