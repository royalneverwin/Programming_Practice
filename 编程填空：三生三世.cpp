#include<iostream>
#include<cstring>
#include<list>
#include<algorithm>
using namespace std;

class TV_Drama {
public:
    char name[100];
    int actor;
    int story;
    int acting_skill;
    TV_Drama(char *n, int a, int s, int as):actor(a), story(s), acting_skill(as){
        strcpy(name, n);
    }
    bool operator < (const TV_Drama &t) const{
        return actor > t.actor;
    }
};

bool comparator_1(const TV_Drama &t1, const TV_Drama &t2){
    return t1.story > t2.story;
}

class comparator_2{
public:
    bool operator ()(const TV_Drama &t1, const TV_Drama &t2){
        return t1.acting_skill > t2.acting_skill;
    }
};
void Printer(const TV_Drama &t){
    cout << t.name << ';';
}
    int main(){
        list<TV_Drama> lst;
        int n;

        cin>>n;
        char  _name[100];
        int _actor, _story, _acting_skill;
        for (int i=0; i<n; i++){
            cin.ignore();
            cin.getline(_name,100);
            cin>>_actor>>_story>>_acting_skill;
            lst.push_back(TV_Drama(_name, _actor, _story, _acting_skill));
        }

        lst.sort();
        for_each(lst.begin(), lst.end(), Printer);
        cout<<endl;

        lst.sort(comparator_1);
        for_each(lst.begin(), lst.end(), Printer);
        cout<<endl;

        lst.sort(comparator_2());
        for_each(lst.begin(), lst.end(), Printer);
        cout<<endl;

        return 0;
    }