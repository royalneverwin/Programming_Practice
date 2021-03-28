#include <iostream>
#include <cstring>
#include <queue>
using namespace std;


int N, K;
class Point{
public:
    int locat;
    int step;
    Point(int l, int s):locat(l), step(s){}
    Point(){
        locat = 0;
        step = 0;
    }
    ~Point(){}
};//记录每个点所对应位置和到达该点的步数


queue<Point> q;


int visited[100010];//判重标记，visited[i]=true表示i已经扩展过


void bfs(){
    Point p(N, 0);
    q.push(p);//放入首元素
    while(!q.empty()){
        Point tmp = q.front();//弹出queue首元素
        q.pop();
        visited[tmp.locat] = 1;//设定locat已遍历
        if(tmp.locat == K){//如果遍历到，输出，程序结束
            cout << tmp.step << endl;
            return;
        }
        //如果未遍历到，将与queue关联的元素压入queue中
        if((tmp.locat -1) >= 0 && (!visited[tmp.locat-1]))
            q.push(Point(tmp.locat-1,tmp.step+1));
        if(tmp.locat < K && tmp.locat+1 < 100010 && (!visited[tmp.locat+1]))
            q.push(Point(tmp.locat+1, tmp.step+1));
        if(tmp.locat < K && 2*tmp.locat < 100010 && (!visited[2*tmp.locat]))
            q.push(Point(2*tmp.locat, tmp.step+1));
    }
    cout << "no" << endl;
}


int main(){
    cin >> N >> K;
    memset(visited, 0, sizeof(visited));
    bfs();
    return 0;
}