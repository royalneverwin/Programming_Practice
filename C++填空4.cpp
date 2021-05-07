#include <iostream>
#include <queue>
#include <stack>

const int TYPE_STACK = 0;
const int TYPE_QUEUE = 1;
const int TYPE_PRIOR = 2;

class Container {
public:
    int type;
    std::stack<int> a1;
    std::queue<int> a2;
    std::priority_queue<int> a3;
    Container(const int &_type):type(_type){}
    int pull(){
        if(type == 0){
            int tmp = a1.top();
            a1.pop();
            return tmp;
        } else if(type == 1){
            int tmp = a2.front();
            a2.pop();
            return tmp;
        } else if(type == 2){
            int tmp = a3.top();
            a3.pop();
            return tmp;
        }
    }

    void push(int x){
        if(type == 0){
            a1.push(x);
        } else if(type == 1){
            a2.push(x);
        } else if(type == 2){
            a3.push(x);
        }
    }
};

int main() {
    int n;
    Container s(TYPE_STACK), q(TYPE_QUEUE), p(TYPE_PRIOR);
    std::cin >> n;
    while (n--) {
        int t, x;
        std::cin >> t;
        if (t) {
            std::cout << s.pull() << ' ' << q.pull() << ' ' << p.pull() << std::endl;
        } else {
            std::cin >> x;
            s.push(x);
            q.push(x);
            p.push(x);
        }
    }
    return 0;
}