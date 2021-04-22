#include <iostream>
#include <list>
#include <string>
#include <map>
using namespace std;


map<int, list<int>> totalList;


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int n;
    string s;
    int listIndex1, listIndex2, listIndexNum;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> s;
        if(s == "new"){
            cin >> listIndex1;
            list<int> tmp;
            totalList[listIndex1] = tmp;
        } else if(s == "add"){
            cin >> listIndex1 >> listIndexNum;
            totalList[listIndex1].push_back(listIndexNum);
        } else if(s == "merge"){
            cin >> listIndex1 >> listIndex2;
            totalList[listIndex1].merge(totalList[listIndex2]);//merge函数做到merge
        } else if(s == "unique"){
            cin >> listIndex1;
            totalList[listIndex1].sort();
            totalList[listIndex1].unique();//unique删除和前一个元素相同的元素, 所以unique之前要sort
        } else if(s == "out"){
            cin >> listIndex1;
            totalList[listIndex1].sort();
            for(auto &tmpNum: totalList[listIndex1]){
                cout << tmpNum << ' ';
            }
            cout << endl;
        } else{
            cout << "Wrong Management!" << endl;
        }
    }
    return 0;
}


//int main(){
//    ios::sync_with_stdio(false);cin.tie(0);
//    int n;
//    string s;
//    int listIndex1, listIndex2, listIndexNum;
//    cin >> n;
//    for(int i = 0; i < n; i++){
//        cin >> s;
//        if(s == "new"){
//            cin >> listIndex1;
//            list<int> tmp;
//            tmp.push_back(listIndex1);
//            totalList.push_back(tmp);
//        } else if(s == "add"){
//            cin >> listIndex1 >> listIndexNum;
//            for(auto &l: totalList){
//                if(*(l.begin()) == listIndex1){
//                    l.push_back(listIndexNum);
//                    break;
//                }
//            }
//        } else if(s == "merge"){
//            cin >> listIndex1 >> listIndex2;
//            list<list<int>>::iterator l1, l2;
//            int flag1 = 0, flag2 = 0;
//            for(auto tmpList = totalList.begin(); tmpList != totalList.end(); tmpList++){
//                if(*(tmpList->begin()) == listIndex1){
//                    l1 = tmpList;
//                    flag1 = 1;
//                }
//                if(*(tmpList->begin()) == listIndex2){
//                    l2 = tmpList;
//                    flag2 = 1;
//                }
//                if(flag1 && flag2){
//                    break;
//                }
//            }
//            l2->pop_front();
//            for(auto tmpNum: (*l2)){//merge之前先把l2的index去掉
//                l1->push_back(tmpNum);
//            }
//            l2->clear();
//            l2->push_back(listIndex2);
//        } else if(s == "unique"){
//            cin >> listIndex1;
//            for(auto &l: totalList){
//                if(*(l.begin()) == listIndex1){
//                    l.pop_front();
//                    l.unique();//注意unique之前先把index去掉
//                    l.push_front(listIndex1);
//                    break;
//                }
//            }
//        } else if(s == "out"){
//            cin >> listIndex1;
//            for(auto &l: totalList){
//                if(*(l.begin()) == listIndex1){
//                    l.pop_front();
//                    l.sort();
//                    for(auto tmpNum: l){
//                        cout << tmpNum << ' ';
//                    }
//                    cout << endl;
//                    l.push_front(listIndex1);
//                    break;
//                }
//            }
//        } else{
//            cout << "Wrong Management!" << endl;
//        }
//    }
//    return 0;
//}
//
