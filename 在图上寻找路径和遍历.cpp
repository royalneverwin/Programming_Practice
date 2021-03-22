#include <iostream>
using namespace std;


const int MAX_LEN = 10;
int depth;
int path[MAX_LEN];
bool isOld(int v);//判断v是否被标记
void setOld(int v);//将v标记
int getNext(int v);//得到与v相邻的点
int s, e;//start，end
bool Dfs(int v){
    if(v == e){
        path[depth] = v;
        return true;
    }
    if(isOld(v)){
        return false;
    }
    setOld(v);
    path[depth] = v;
    depth++;
    int next = getNext(v);
    while(next != -1){
        if(Dfs(next) == true){
            return true;
        }
    }
    --depth;
    return false;
}

