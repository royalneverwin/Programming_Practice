//
//将连续的若干个方块作为一个“大块”(box_segment)
//考虑，假设开始一共有 n个“大块”，编号0到n-1 第i个大块的颜色是 color[i],包含的方块数目，即长度,是len[i]
//click_box(i,j,ex_len)表示:
//大块j的右边已经有一个长度为ex_len的大块(该大块可能是在合
//并过程中形成的，不妨就称其为ex_len)，且j的颜色和ex_len
//相同，在此情况下将 i 到j以及ex_len都消除所能得到的最高分
//。
//于是整个问题就是求：click_box(0,n-1,0)
//
//求click_box(i,j,ex_len)时，有两种处理方法，取最优者
//假设j和ex_len合并后的大块称作 Q
//1) 将Q直接消除，这种做法能得到的最高分就是：
//click_box(i,j-1,0) + (len[j]+ex_len)2
//2) 期待Q以后能和左边的某个同色大块合并。需要枚举可能和Q
//合并的大块。假设让大块k和Q合并，则此时能得到的最大
//分数是：
//click_box(i,k,len[j]+ex_len) + click_box(k+1,j-1,0)
//click_box(i,j,ex_len) 递归的终止条件：
//i == j
#include <iostream>
#include <cstring>
using namespace std;
const int M = 210;
struct Segment{
    int color;
    int len;
};
Segment segments[M];
int score[M][M][M];
int ClickBox(int i, int j, int len){
    if(score[i][j][len] != -1)
        return score[i][j][len];
    int result = (segments[j].len + len) * (segments[j].len + len);
    if(i == j)
        return result;
    result += ClickBox(i, j-1, 0); //第j块和后面的块一起消除
    /*可能存在更好的消除方法*/
    for(int k = i; k <= j-1; k++){
        if(segments[k].color != segments[j].color)
            continue;
        int r = ClickBox(k+1, j-1, 0); //中间块的消除
        r += ClickBox(i, k, segments[j].len + len); //第k块和后面的颜色相同
        result= max(result, r);
    }
    score[i][j][len] = result;
    return result;
}


int main(){
    int T;
    cin >> T;
    for(int i = 0; i < T; i++){
        int n;
        memset(score, 0xff, sizeof(score)); //置初值-1
        cin >> n;
        int lastC = 0; //上一个方块的颜色种类
        int segNum = -1; //先++后赋值，所以这里初值为-1
        for(int j = 0; j < n; j++){
            int c;
            cin >> c;
            if(c != lastC){ //c为不同的颜色，重制lastC
                segNum++;
                segments[segNum].len = 1;
                segments[segNum].color = c;
                lastC = c;
            } else
                segments[segNum].len++;
        }
        cout << "Case " << i+1 << ": " << ClickBox(0, segNum, 0) << endl;
    }
    return 0;
}