#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//贪心算法，每次观看能观看的电影中结束时间最早的一场电影，这样就能观看到最多部电影
struct movie{
    int start;
    int end;
    bool operator <  (const struct movie &m) const{
        return end < m.end;
    }
};


vector<movie> Movie;


int main(){
    int n;
    int totalMovie;
    int movieEnd;
    cin >> n;
    while(n != 0) {
        totalMovie = 0;
        movieEnd = 0;
        Movie.clear();
        for (int i = 0; i < n; i++) {//输入数据
            struct movie tmp;
            cin >> tmp.start >> tmp.end;
            Movie.push_back(tmp);
        }
        sort(Movie.begin(), Movie.end());//按照电影结束时间排序
        for(auto &i: Movie){
            if(i.start >= movieEnd){//如果开始时间>=结束时间，就可以看电影
                totalMovie += 1;
                movieEnd = i.end;
            }
        }
        cout << totalMovie << endl;
        cin >> n;
    }
    return 0;
}