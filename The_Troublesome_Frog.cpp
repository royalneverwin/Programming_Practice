#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <bitset>
using namespace std;


/*枚举 + 剪枝*/
int row, col;//稻田的行数和列数
int n;//被压扁的水稻数


struct Plant{//为了枚举的时候优先枚举步长短的, 要求Plant先按照x从小到大排序, 若x相同则按照y从小到大排序
    int r, c;
    bool operator < (const Plant& p) const{
        return (r == p.r) ? (c < p.c) : (r < p.r);
    }
};


struct Plant p[5010];
bitset<5010> plantExists[5010];//也可以用char plantExists[5010][5010], 用bitset更节省空间


int maxStep(Plant secPlant, int dx, int dy){
    int steps = 2;
    secPlant.r = secPlant.r + dx;
    secPlant.c = secPlant.c + dy;
    while(secPlant.r <= row && secPlant.r >= 1 && secPlant.c <= col && secPlant.c >= 1){
        if(!plantExists[secPlant.r][secPlant.c])//必须保证在跳出稻田之前每一步的水稻都是被压垮的, 否则点的选取不成立
            return 0;
        secPlant.r += dx;
        secPlant.c += dy;
        ++steps;
    }
    return steps;
}


int main(){
    int dx, dy, px, py, steps, max = 2;//因为2个植物被踩我们不感兴趣, 因此max至少为2
    ios::sync_with_stdio(false);cin.tie(0);
    cin >> row >> col;
    cin >> n;
    memset(plantExists, 0, sizeof(plantExists));//初始化
    for(int i = 0; i  < n; i++){
        cin >> p[i].r >> p[i].c;
        plantExists[p[i].r].set(p[i].c);
    }
    sort(p, p+n);
    for(int i = 0; i < n - 1; i++){//plant[i]是第1个点
        for(int j = i + 1; j < n; j++){//plant[j]是第2个点
            dx = p[j].r - p[i].r;
            dy = p[j].c - p[i].c;
            px = p[i].r - dx;
            py = p[i].c - dy;
            //第一次剪枝： (px, py)表示plant[i]之前的节点, 因为plant[i]已经是第一个节点了, 因此(px, py)一定在稻田外, 否则这两个点选取错误, 不用再遍历了
            if(px >= 1 && px <= row && py >= 1 && py <= col)
                continue;
            px = p[i].r + max * dx;
            //第二次剪枝：目前已经发现的踩最多水稻的青蛙踩了max个, 如果该青蛙跳max次时已经跳出稻田, 说明该青蛙必定最多踩水稻小于等于max次, 不会影响结果, 不用再遍历了
            if(px > row)//这里不用判断px < 1的原因是水稻排序是x从小到大的, 因此dx必大于等于0
                break;//这里break的原因是之前已经对水稻排序, 所以排在j后面对水稻x都不会比它小, 对j的x已经越界, 对后面所有水稻水稻一样会越界, 不用再换j了, 直接换i
            py = p[i].c + max * dy;
            if(py > col || py < 1){
                continue;
            }
            steps = maxStep(p[j], dx, dy);
            if(steps > max)
                max = steps;
        }
    }
    if(max == 2)
        max = 0;
    cout << max << endl;
    return 0;
}