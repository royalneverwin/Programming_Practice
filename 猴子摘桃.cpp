#include <iostream>
#include <vector>
using namespace std;


struct tree{
    int peach;
    int enemy;
    tree(int p, int e):peach(p), enemy(e){}
};
int carry;
vector<tree> Tree;


int main(){
    cin >> carry;
    while(carry != -1){
        int p, e;
        Tree.clear();
        cin >> p >> e;
        while(p != -1 || e != -1){
            Tree.push_back(tree(p, e));
            cin >> p >> e;
        }
        int ans = 0;
        for(int i = 0; i < Tree.size(); i++){
            int index = i;
            int pp = 0;
            int ee = Tree[index].enemy;
            while(ee <= carry){
                pp += Tree[index].peach;
                index++;
                if(index < Tree.size())
                    ee += Tree[index].enemy;
                else
                    break;
            }
            ans = max(ans, pp);
        }
        cout << ans << endl;
        cin >> carry;
    }
}

