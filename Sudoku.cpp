#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define xDEBUG1
#define xDEBUG2

//使用dfs算法，找到一个解决方法就结束


char sudoku[10][10];


struct point{//表示待填的空格位置
    int row;
    int col;
    point(){
        row = 0;
        col = 0;
    }
    point(int r, int c):row(r), col(c){}
};

bool operator == (const struct point &p1, const struct point &p2){
    return p1.col == p2.col && p1.row == p2.row;
}

vector<struct point> points;//待填的空格集合
vector<char> rowLeft[10];//表示每行还剩什么数字可以选
vector<char> colLeft[10];//表示每列还剩什么数字可以选
vector<char> matrixLeft[10];//表示每个对角线还剩什么数字可以选


bool is_checked(){
    int row, col;
    int matrixIndex;
    int flag;
    if(!points.empty()) {
        for (auto &i : points) {
            flag = 0;
            row = i.row;
            col = i.col;
            matrixIndex = 3 * ((row - 1) / 3) + (col - 1) / 3 + 1;
            if (rowLeft[row].empty())//该行有空格，却没有能写的数字了
                return false;
            if (colLeft[col].empty())//该列有空格，却没有能写的数字了
                return false;
            if (matrixLeft[matrixIndex].empty())//该九宫格有空格，却没有能写的数字了
                return false;
            for (auto &j: rowLeft[row]) {
                /*如果存在一个数字，在行、列、九宫格都满足，则说明正确*/
                if (find(colLeft[col].begin(), colLeft[col].end(), j) != colLeft[col].end() &&
                    find(matrixLeft[matrixIndex].begin(), matrixLeft[matrixIndex].end(), j) !=
                    matrixLeft[matrixIndex].end()) {
                    flag = 1;
                    break;
                }
            }
            if (!flag) {
                return false;
            }
        }
    }
    return true;
}


bool bfs() {
    if (!points.empty()) {
        char ele;
        struct point cur = points.front();//找到其中一个空格，填写
        points.erase(points.begin());
        int row, col, matrixIndex;
        row = cur.row;
        col = cur.col;
        matrixIndex = 3 * ((row - 1) / 3) + (col - 1) / 3 + 1;
        /*寻找该空格能填写的元素*/
#ifdef DEBUG2
        cout << "row:" << endl;
        for(auto &j: rowLeft[row]){
            cout << j << ' ';
        }
        cout << endl;
        cout << "col: " << endl;
        for(auto &j: colLeft[col]){
            cout << j << ' ';
        }
        cout << endl;
        cout << "matrix: " << endl;
        for(auto &j: matrixLeft[matrixIndex]){
            cout << j << ' ';
        }
        cout << endl;
#endif
        for (auto &j: rowLeft[row]) {//注意这里不要直接用j，如果在row中删掉值j会导致这里的j发生变化！
#ifdef DEBUG2
            cout << "row:" << row << ' ' << "col:" << col << ' ' << "matrix:" << matrixIndex << endl;
#endif
            ele = j;
            /*这里记录元素位置，为了在之后还原时将元素放回到正确位置，避免for循环时循环到之前循环到的元素*/
            auto prow = find(rowLeft[row].begin(), rowLeft[row].end(), ele);
            auto pcol = find(colLeft[col].begin(), colLeft[col].end(), ele);
            auto pmatrix = find(matrixLeft[matrixIndex].begin(), matrixLeft[matrixIndex].end(), ele);
            if (pcol != colLeft[col].end() && pmatrix != matrixLeft[matrixIndex].end()) {
                sudoku[row][col] = ele;
                /*删去填写的元素*/
                rowLeft[row].erase(prow);
                colLeft[col].erase(pcol);
                matrixLeft[matrixIndex].erase(pmatrix);
                if (is_checked()) {
#ifdef DEBUG2
                    for(int m = 1; m <= 9; m++){
                        for(int n = 1; n <= 9; n++){
                            cout << sudoku[m][n] << ' ';
                        }
                        cout << endl;
                    }
#endif
                    if(bfs()){//如果这样数独合法而且有解
                        return true;
                    }
                }
                /*如果该种不成立，要还原之前的状态*/
                rowLeft[row].insert(prow, sudoku[row][col]);
                colLeft[col].insert(pcol, sudoku[row][col]);
                matrixLeft[matrixIndex].insert(pmatrix, sudoku[row][col]);
                sudoku[row][col] = '0';
            }
        }
        /*如果该点所有可能值都不成立, 回到上一步，注意该点要还原*/
        points.insert(points.begin(), cur);
        return false;
    }
    /*如果没有空格*/
    return true;
}



int main(){
    int n;
    cin >> n;
    for(int temp = 0; temp < n; temp++) {
        /*清空*/
        for(int i = 1; i <= 9; i++){
            rowLeft[i].clear();
            colLeft[i].clear();
            matrixLeft[i].clear();
            points.clear();
        }
        /*初始化rowLeft, colLeft, matrixLeft*/
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= 9; j++) {
                rowLeft[i].push_back(j + '0');
                colLeft[i].push_back(j + '0');
                matrixLeft[i].push_back(j + '0');
            }
        }
        int k;
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= 9; j++) {
                cin >> sudoku[i][j];
                if (sudoku[i][j] == '0') {//遇到空格，加入vector
                    struct point tmp(i, j);
                    points.push_back(tmp);
                }
                /*删除行、列、九宫格中出现的数字*/
                if(sudoku[i][j] != '0') {
                    k = 3 * ((i - 1) / 3) + (j - 1) / 3 + 1;
                    rowLeft[i].erase(find(rowLeft[i].begin(), rowLeft[i].end(), sudoku[i][j]));
                    colLeft[j].erase(find(colLeft[j].begin(), colLeft[j].end(), sudoku[i][j]));
                    matrixLeft[k].erase(find(matrixLeft[k].begin(), matrixLeft[k].end(), sudoku[i][j]));
                }
            }
        }
#ifdef DEBUG1
        for(int i = 1; i <= 9; i++){
            for(int j = 1; j <= 9; j++){
                cout << sudoku[i][j] << ' ';
            }
            cout << endl;
        }
        cout << "points:" << endl;
        cout << points.size() << endl;
        for(auto &i: points){
            cout << i.row << ' ' << i.col << endl;
        }
        for(int i = 1; i <= 9; i++){
            cout << "row: " << endl;
            for(auto &j: rowLeft[i]){
                cout << j << ' ';
            }
            cout << endl;
            cout << "col: " << endl;
            for(auto &j: colLeft[i]){
                cout << j << ' ';
            }
            cout << endl;
            cout << "matrix: " << endl;
            for(auto &j: matrixLeft[i]){
                cout << j << ' ';
            }
            cout << endl;
        }
#endif
        if(!is_checked()){//如果数独不符合要求
            cout << -1 << endl;
            continue;
        }
        if (bfs()) {
            for (int i = 1; i <= 9; i++) {
                for (int j = 1; j <= 9; j++) {
                    cout << sudoku[i][j];
                }
                cout << endl;
            }
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}