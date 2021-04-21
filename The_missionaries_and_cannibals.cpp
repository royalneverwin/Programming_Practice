#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define xDEBUG

//算法：bfs, 加上一些优化方法


int m, n;//m代表传教士和野蛮人人数；n代表船限载


//用来表示每一次过河后的状态, 不妨设要求从左到右过河
struct state{
    int misR;//右岸传教士数量
    int canR;//右岸野人数量
    /*注意还需要船上mis >= can, 这部分我们在选人上船时进行操作*/
    int boat;//0表示船在左岸, 1表示船在右岸
    int step;//表示这是第几步
    state(){
        misR = 0;
        canR = 0;
        boat = 0;
        step = 0;
    }
    state(int mr, int cr, int bo, int st):misR(mr), canR(cr), boat(bo), step(st){}
};


vector<struct state> states;//所有遍历过的状态组成的集合


queue<struct state> qstate;


//判断状态是否符合题意
bool is_correct(struct state &s){
    if(s.misR == 0){
        return true;
    }
    if(s.misR == m){
        return true;
    }
    if(s.misR == s.canR){
        return true;
    }
    return false;
}


//判断是否实现目标
inline bool is_success(struct state &s){
    if(s.misR == m && s.canR == m){
        return true;
    }
    return false;
}


//判断该状态是否已经遍历过（是否有回溯）
bool is_checked(struct state &s){
    for(auto i = states.begin(); i != states.end(); i++){
        if(s.canR == i->canR && s.misR == i->misR && s.boat == i->boat){
            return true;
        }
    }
    return false;
}


int main(){
    cin >> m >> n;
    int dMis, dCan;
    struct state init(0, 0, 0, 0);
    qstate.push(init);
    states.push_back(init);
    while(!qstate.empty()) {
        struct state cur = qstate.front();
        struct state tmp;
        qstate.pop();
        for (int i = 1; i <= n; i++) {//i表示每次过河的总人数
            for (dCan = 0; dCan <= i; dCan++) {
                dMis = i - dCan;
                if (dMis != 0 && dMis < dCan) {//不符合要求，直接跳过
                    continue;
                }
                tmp.boat = cur.boat ^ 1;
                if(cur.boat == 1) {
                    tmp.canR = cur.canR - dCan;
                    tmp.misR = cur.misR - dMis;
                    if(tmp.canR < 0 || tmp.misR < 0)//如果坐船人数过多，直接跳过
                        continue;
                }
                else{
                    tmp.canR = cur.canR + dCan;
                    tmp.misR = cur.misR + dMis;
                    if(tmp.canR > m || tmp.misR > m)//如果坐船人数过多，直接跳过
                        continue;
                }
                tmp.step = cur.step + 1;
                if(is_success(tmp)){
                    cout << tmp.step << endl;
                    return 0;
                }
                if(is_correct(tmp) && !is_checked(tmp)) {
                    states.push_back(tmp);
                    qstate.push(tmp);
                }
#ifdef DEBUG
                printf("misR: %d, canR: %d, boat: %d, step: %d\n", tmp.misR, tmp.canR, tmp.boat, tmp.step);
#endif
            }
        }
    }
    cout << -1;
    return 0;
}
