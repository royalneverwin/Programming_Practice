#include <iostream>
using namespace std;


int n, m;
int ans = 0;
struct myChar{
    char c;
    int cnt;
};
myChar Map[101][101];

void dfs(int x, int y, int cnt){
    Map[x][y].cnt = cnt;
    if(x > 1 && y > 1 && Map[x-1][y-1].c == '@' && Map[x-1][y-1].cnt == 0)
        dfs(x-1, y-1, cnt);
    if(x > 1 && Map[x-1][y].c == '@' && Map[x-1][y].cnt == 0)
        dfs(x-1, y, cnt);
    if(x > 1 && y < m && Map[x-1][y+1].c == '@' && Map[x-1][y+1].cnt == 0)
        dfs(x-1, y+1, cnt);
    if(y > 1 && Map[x][y-1].c == '@' && Map[x][y-1].cnt == 0)
        dfs(x, y-1, cnt);
    if(y < m && Map[x][y+1].c == '@' && Map[x][y+1].cnt == 0)
        dfs(x, y+1, cnt);
    if(x < n && y > 1 && Map[x+1][y-1].c == '@' && Map[x+1][y-1].cnt == 0)
        dfs(x+1, y-1, cnt);
    if(x < n && Map[x+1][y].c == '@' && Map[x+1][y].cnt == 0)
        dfs(x+1, y, cnt);
    if(x < n && y < m && Map[x+1][y+1].c == '@' && Map[x+1][y+1].cnt == 0)
        dfs(x+1, y+1, cnt);
}

int main(){
    cin >> n >> m;
    while(n != 0 || m != 0){
        ans = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                cin >> Map[i][j].c;
                Map[i][j].cnt = 0;
            }
        }
        for(int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if(Map[i][j].c == '@' && Map[i][j].cnt == 0) {
                    ans++;
                    dfs(i, j, ans);
                }
            }
        }
        cout << ans << endl;
        cin >> n >> m;
    }
}