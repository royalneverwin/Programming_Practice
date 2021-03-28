#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>
using namespace std;


string weapon[3];


class Creature{//基类，有两个成员变量HP和ATK
protected:
    int HP;
    int ATK;
public:
    Creature(int hp, int atk): HP(hp),ATK(atk){}
    Creature(){
        HP = 0;
        ATK = 0;
    }
    virtual void State(){}
    virtual ~Creature(){}
};

class Dragon:public Creature{//派生类，表示Dragon，count表示存在个数
public:
    int count;
    int weaponList;
    double morale;
    Dragon(int hp, int atk):Creature(hp, atk){
        count = 0;
        weaponList = -1;
        morale=  -1.0;
    };
    Dragon():Creature(0, 0){
        count = 0;
        weaponList = -1;
        morale = -1.0;
    }
    virtual void State(){
        cout << " born with strength " << HP << ',' << count << " dragon in ";
    }
    void SpecialState(){
        cout << "It has a " << weapon[weaponList] << ",and it's morale is ";
        printf("%.2f\n", morale);
    }
    ~Dragon(){}
};


class Ninja:public Creature{//派生类，表示Ninja，count表示存在个数
public:
    int count;
    int weaponList[2];
    Ninja(int hp, int atk):Creature(hp, atk){
        count = 0;
        weaponList[0] = -1;
        weaponList[1] = -1;
    };
    Ninja():Creature(0, 0){
        count = 0;
        weaponList[0] = -1;
        weaponList[1] = -1;
    }
    virtual void State(){
        cout << " born with strength " << HP << ',' << count << " ninja in ";
    }
    void SpecialState() {
        cout << "It has a " << weapon[weaponList[0]] << " and a " << weapon[weaponList[1]] << endl;
    }
    ~Ninja(){}
};


class Iceman:public Creature{//派生类，表示Iceman，count表示存在个数
public:
    int count;
    int weaponList;
    Iceman(int hp, int atk):Creature(hp, atk){
        count = 0;
        weaponList = -1;
    };
    Iceman():Creature(0, 0){
        count = 0;
        weaponList = -1;
    }
    virtual void State(){
        cout << " born with strength " << HP << ',' << count << " iceman in ";
    }
    void SpecialState() {
        cout << "It has a " << weapon[weaponList] << endl;
    }
    ~Iceman(){}
};


class Lion:public Creature{//派生类，表示Lion，count表示存在个数
public:
    int count;
    int loyalty;
    Lion(int hp, int atk):Creature(hp, atk){
        count = 0;
        loyalty = -1;
    };
    Lion():Creature(0, 0){
        count = 0;
        loyalty = -1;
    }
    virtual void State(){
        cout << " born with strength " << HP << ',' << count << " lion in ";
    }
    void SpecialState() {
        cout << "It's loyalty is " << loyalty << endl;
    }
    ~Lion(){}
};


class Wolf:public Creature{//派生类，表示Wolf，count表示存在个数
public:
    int count;
    Wolf(int hp, int atk):Creature(hp, atk){
        count = 0;
    };
    Wolf():Creature(0, 0){
        count = 0;
    }
    virtual void State(){
        cout << " born with strength " << HP << ',' << count << " wolf in ";
    }
    ~Wolf(){}
};


class RedDevil{//红魔军，成员对象有五个warrior，还有总血量totalLife、warrior编号number，warrior产生顺序list，判断每次产生何种warrior whichOne，判断是否结束ifEnd，时间time
public:
    Dragon dra;
    Ninja nin;
    Iceman ice;
    Lion lio;
    Wolf wol;
    int totalLife;
    int number;
    unordered_map<string, int> creature;
    string list[5];
    int whichOne;
    int ifEnd;
    int time;
    RedDevil(int dragonHP, int ninjaHP, int icemanHP, int lionHP, int wolfHP, int life):dra(dragonHP, 0), nin(ninjaHP, 0), ice(icemanHP, 0), lio(lionHP, 0), wol(wolfHP, 0){
        totalLife = life;
        number = 0;
        whichOne = 0;
        list[0] = "iceman";
        list[1] = "lion";
        list[2] = "wolf";
        list[3] = "ninja";
        list[4] = "dragon";
        creature["dragon"] = dragonHP;
        creature["ninja"] = ninjaHP;
        creature["iceman"] = icemanHP;
        creature["lion"] = lionHP;
        creature["wolf"] = wolfHP;
        ifEnd = 0;
        time = 0;
    }
    void Create(){
        int tryTime = 0;//用来判断军营是否还能创造warrior
        string tmp = list[whichOne];
        whichOne = (whichOne+1) % 5;
        printf("%03d ", time);
        while(tryTime < 5) {
            if (totalLife >= creature[tmp]) {//可以创造
                number++;
                totalLife -= creature[tmp];
                if(tmp == "dragon"){
                    dra.weaponList = number % 3;
                    dra.morale = double(totalLife) / creature[tmp];
                    cout << "red dragon " << number;
                    dra.count++;
                    dra.State();
                    cout << "red headquarter" << endl;
                    dra.SpecialState();
                }
                else if(tmp == "ninja"){
                    cout << "red ninja " << number;
                    nin.weaponList[0] = number % 3;
                    nin.weaponList[1] = (number + 1) % 3;
                    nin.count++;
                    nin.State();
                    cout << "red headquarter" << endl;
                    nin.SpecialState();
                }
                else if(tmp == "iceman"){
                    cout << "red iceman " << number;
                    ice.weaponList = number % 3;
                    ice.count++;
                    ice.State();
                    cout << "red headquarter" << endl;
                    ice.SpecialState();
                }
                else if(tmp == "lion"){
                    cout << "red lion " << number;
                    lio.count++;
                    lio.loyalty = totalLife;
                    lio.State();
                    cout << "red headquarter" << endl;
                    lio.SpecialState();
                }
                else if(tmp == "wolf"){
                    cout << "red wolf " << number;
                    wol.count++;
                    wol.State();
                    cout << "red headquarter" << endl;
                }
                break;
            }
            else{//不可以创造
                tmp = list[whichOne];
                whichOne = (whichOne+1) % 5;
                tryTime++;
            }
        }
        if(tryTime == 5){//如果军营无法再创造
            cout << "red headquarter stops making warriors" << endl;
            ifEnd = 1;
        }
        time++;
    };
};


class BlueDevil{//蓝魔军，成员对象有五个warrior，还有总血量totalLife、warrior编号number，warrior产生顺序list，判断每次产生何种warrior whichOne，判断是否结束ifEnd，时间time
public:
    Dragon dra;
    Ninja nin;
    Iceman ice;
    Lion lio;
    Wolf wol;
    int totalLife;
    int number;
    unordered_map<string, int> creature;
    string list[5];
    int whichOne;
    int ifEnd;
    int time;
    BlueDevil(int dragonHP, int ninjaHP, int icemanHP, int lionHP, int wolfHP, int life): dra(dragonHP, 0), nin(ninjaHP, 0), ice(icemanHP, 0), lio(lionHP, 0), wol(wolfHP, 0){
        totalLife = life;
        number = 0;
        whichOne = 0;
        list[0] = "lion";
        list[1] = "dragon";
        list[2] = "ninja";
        list[3] = "iceman";
        list[4] = "wolf";
        creature["dragon"] = dragonHP;
        creature["ninja"] = ninjaHP;
        creature["iceman"] = icemanHP;
        creature["lion"] = lionHP;
        creature["wolf"] = wolfHP;
        ifEnd = 0;
        time = 0;
    }
    void Create(){
        int tryTime = 0;//用来判断军营是否还能创造warrior
        string tmp = list[whichOne];
        whichOne = (whichOne+1) % 5;
        printf("%03d ", time);
        while(tryTime < 5) {
            if (totalLife >= creature[tmp]) {//可以创造
                number++;
                totalLife -= creature[tmp];
                if(tmp == "dragon"){
                    cout << "blue dragon " << number;
                    dra.weaponList = number % 3;
                    dra.morale = double(totalLife) / creature[tmp];
                    dra.count++;
                    dra.State();
                    cout << "blue headquarter" << endl;
                    dra.SpecialState();
                }
                else if(tmp == "ninja"){
                    cout << "blue ninja " << number;
                    nin.weaponList[0] = number % 3;
                    nin.weaponList[1] = (number + 1) % 3;
                    nin.count++;
                    nin.State();
                    cout << "blue headquarter" << endl;
                    nin.SpecialState();
                }
                else if(tmp == "iceman"){
                    cout << "blue iceman " << number;
                    ice.weaponList = number % 3;
                    ice.count++;
                    ice.State();
                    cout << "blue headquarter" << endl;
                    ice.SpecialState();
                }
                else if(tmp == "lion"){
                    cout << "blue lion " << number;
                    lio.loyalty = totalLife;
                    lio.count++;
                    lio.State();
                    cout << "blue headquarter" << endl;
                    lio.SpecialState();
                }
                else if(tmp == "wolf"){
                    cout << "blue wolf " << number;
                    wol.count++;
                    wol.State();
                    cout << "blue headquarter" << endl;
                }
                break;
            }
            else{//不可以创造
                tmp = list[whichOne];
                whichOne = (whichOne+1) % 5;
                tryTime++;
            }
        }
        if(tryTime == 5){//如果军营无法再创造
            cout << "blue headquarter stops making warriors" << endl;
            ifEnd = 1;
        }
        time++;
    };
};


int main(){
    int n, M, dragon, ninja, iceman, lion, wolf;
    cin >> n;
    /*初始化武器*/
    weapon[0] = "sword";
    weapon[1] = "bomb";
    weapon[2] = "arrow";
    for(int i = 0; i < n; i++){
        cin >> M >> dragon >> ninja >> iceman >> lion >> wolf;
        RedDevil rd(dragon, ninja, iceman, lion, wolf, M);
        BlueDevil bd(dragon, ninja, iceman, lion, wolf, M);
        cout << "Case:" << i+1 << endl;
        while(!rd.ifEnd || !bd.ifEnd){
            if(!rd.ifEnd){
                rd.Create();
            }
            if(!bd.ifEnd){
                bd.Create();
            }
        }
    }
    return 0;
}