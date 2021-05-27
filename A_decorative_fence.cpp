//排列：
//共N根长度不一的木棒。本题待求方案的序号为C
//先假设第1短的木棒作为第一根，看此时的方案数P(N,1)是否>=C
//如果否，则应该用第二短的作为第一根，C 减去P(N,1) ，再看此时方案数P(N, 2)和C比如何。
//如果还 < C ，则应以第三短的作为第一根,C再减去P(N, 2) ….
//P(i,j)表示： 有i根木棒，以其中第j短的作为第一根，在此情形下能构成的美妙栅栏数目。
//若发现第 i短的作为第一根时，方案数已经不小于C，(即P(N,i) >= C ,C是不断减小的) 则确定应该以第i短的作为第一根，
//C减去第 i短的作为第一根的所有方案数，然后再去确定第二根….即接下来试P(N-1,1), P(N-1,2)……
//动归：
//令 S(i)表示由i根木棒构成的合法方案集合
//令 B[i][k] 表示： S(i)中以这i根木棒里第k短的木棒打头的方案数
//在选定了某根木棒x作为i根木棒中的第一根木棒的情况下, 假定剩下i-1根木棒的合法方案数是A[i-1]。
//但是，这A[i-1]种方案，并不是每种都能和x形成新的合法方案。将第一根比第二根长的方案称为DOWN方案，
//第一根比第二根短的称为UP方案，则，S(i-1)中，第一根木棒比x长的DOWN方案，以及第一根木棒比x短的UP方案，才能和x构成S(i)中的方案。
//B[i][k] = ∑ B[i-1][M](DOWN) + ∑ B[i-1][N](UP), M = k ... i-1 , N = 1… k-1
//没法直接推。于是把B分类细化，即加一维: B[i][k] = C[i][k][DOWN] + C[i][k][UP]
//C[i][k][DOWN] 是S(i)中以第k短的木棒打头的DOWN方案数。然后试图对C进行动规:
//C[i][k][UP] = ∑ C[i-1][M][DOWN], M = k ... i -1
//C[i][k][DOWN] = ∑ C[i-1][N][UP], N = 1… k-1
//初始条件：C[1][1][UP]=C[1][1][DOWN] = 1
//经验：当选取的状态，难以进行递推时（分解出的子问题和原问题形式不一样，或不具有无后效性），考虑将状态增加限制条件后分类细化，即增加维度，然后在新的状态上尝试递推
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;


const int UP = 0;
const int DOWN = 1;
const int MAXN = 25;
long long C[MAXN][MAXN][2];//C[i][k][DOWN] 是S(i)中以第k短的木棒打头的DOWN方案数,C[i][k][UP] 是S(i)中以第k短的木棒打头的UP方案数,第k短指i根中第k短
void Init(int n){
    memset(C, 0, sizeof(C));
    C[1][1][UP] = C[1][1][DOWN] = 1;
    for(int i = 2; i <= n; i++){
        for(int k = 1; k <= i; k++){// 枚举第一根木棒的长度
            for(int M = k; M < i; M++){ //枚举第二根木棒的长度，注意C的第二个参数代表"第k小"
                C[i][k][UP] += C[i-1][M][DOWN];
            }
            for(int N = 1; N <= k-1; N++){ //枚举第二根木棒长度
                C[i][k][DOWN] += C[i-1][N][UP];
            }
        }
    }
    //总方案数是Sum{C[n][k][DOWN] + C[n][k][UP]}, k = 1, 2, ... ,n
}
void Print(int n, long long cc){
    int used[MAXN]; //木棒是否用过
    int seq[MAXN]; //最终要输出的答案
    memset(used, 0, sizeof(used));
    for(int i = 1; i <= n; i++){ //依次确定每一个位置i的木棒序号
        int No = 0; //位置i的木棒k是剩下的木棒里第No短的，No从1开始算
        long long skipped = 0; //已经跳过的方案数
        int k;
        for(k = 1; k <= n; k++){
            if(!used[k]){ //长度为k的木棒没有用过
                ++No; //k是剩下的木棒里第No短的
                if(i == 1) //确定的是位置1的木棒序号
                    skipped = C[n][No][UP] + C[n][No][DOWN];
                else{
                    if(k > seq[i-1] && (i <= 2 || seq[i-2] > seq[i-1])) //该放置合法
                        skipped = C[n-i+1][No][DOWN];
                    else if(k < seq[i-1] && (i <= 2 || seq[i-2] < seq[i-1]))
                        skipped = C[n-i+1][No][UP];
                }
                if(skipped >= cc)
                    break;
                else
                    cc -= skipped;
            }
        }
        used[k] = 1;
        seq[i] = k;
    }
    for(int i = 1; i <= n; i++)
        cout << seq[i] << ' ';
    cout << endl;
}


int main(){
    int t, n;
    long long c;
    Init(20);
    scanf("%d", &t);
    while(t--){
        scanf("%d %lld", &n, &c);
        Print(n, c);
    }
    return 0;
}