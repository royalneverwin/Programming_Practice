#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
#define xDEBUG


/*iceman行走消耗*/
const int lifeCost = 9;
const int attackAdd = 20;


unordered_map<string, int> weaponNumber;//武器编号


/*事件进行时间*/
int timeCountHour;
int timeCountMinute;


/*初始输入*/
int blueLife, redLife;
int cityCount;
int arrowATK;
int loyalDown;
int totalTime;
unordered_map<string, int> creatureHP;
unordered_map<string, int> creatureATK;


/*红魔军，蓝魔军*/
const string redList[5] = {"iceman", "lion", "wolf", "ninja", "dragon"};
const string blueList[5] = {"lion", "dragon", "ninja", "iceman", "wolf"};
int blueNumber, redNumber;//武士编号
int ifRedWin;//判断是否获胜
int ifBlueWin;
unordered_map<int, string> PrintCreature;


/*输出时间*/
void PrintTime(){
    cout << setw(3) << timeCountHour << ':';
    cout << setw(2) << timeCountMinute << ' ';
}


class Weapon{
public:
    int ATK;
    int kind;
    Weapon(){
        ATK = 0;
        kind = -1;
    }
    virtual int GetUseTime(){//只有arrow用得到
        return -1;
    }
    virtual void AddUseTime(){}//只有arrow用得到
    Weapon(int atk, int k):ATK(atk), kind(k){}
    virtual ~Weapon(){}
};


class Sword:public Weapon{
public:
    Sword(int atk):Weapon(atk, 0){}
    Sword():Weapon(){}
    ~Sword(){}
};


class Bomb:public Weapon{
public:
    Bomb():Weapon(0, 1){}
    ~Bomb(){}
};


class Arrow:public Weapon{
public:
    int useTime;
    Arrow():Weapon(arrowATK, 2){
        useTime = 0;
    }
    Arrow(int u):Weapon(arrowATK, 2){
        useTime = u;
    }

    virtual int GetUseTime(){
        return useTime;
    }

    virtual void AddUseTime(){
        useTime++;
    }

    ~Arrow(){}
};


class Creature{//基类，有两个成员变量HP和ATK
public:
    int HP;
    int ATK;
    int number;//编号
    /*种类，判断creature是哪一种，我们规定dragon、ninja、iceman、lion、wolf分别是1，2，3，4，5*/
    int kind;
    vector<Weapon *> weaponList;
    Creature(int hp, int atk, int num, int k): HP(hp),ATK(atk), number(num), kind(k){
    }
    Creature(){
        HP = 0;
        ATK = 0;
        number = 0;
        kind = -1;
    }

    virtual bool ifHaveArrow(){
        return false;
    }
    virtual bool ifHaveBomb(){
        return false;
    }
    virtual int GetLoyalty(){//对于除lion的warrior，用不到这个，这个函数是专门给lion编写的
        return 1;
    }
    virtual double GetMorale(){//专门个dragon写的, 得到它的morale
        return 1.0;
    };
    virtual void MoraleAdd(){//增加dragon的morale
    }
    virtual void MorialDown(){//减少dragon的morale
    }
    virtual void CntMove(){}//专门给iceman编写的
    virtual void DoMoveCost(){}//iceman会掉血加攻击力
    virtual void GrabWeapon(Creature *enemy){}//wolf会抢武器
    virtual void LoyaltyDown(){}//lion减loyalty
    bool ifDead() const{
        return HP <= 0;
    }
    void Attack(int side, Creature *enemy, int city){//side = 1 表示红魔军，side = -1 表示蓝魔军
        int SwordAttack = 0;
        if(!weaponList.empty()) {
            for (auto p = weaponList.begin();
                 p != weaponList.end(); p++) {
                if ((*p)->kind == 0) {
                    SwordAttack = (*p)->ATK;
                    (*p)->ATK = (*p)->ATK * 8 / 10;
                    if ((*p)->ATK == 0) {//sowrd攻击变为0时，视为失去sword
                        weaponList.erase(p);
                    }
                    break;//只会有一把剑
                }
            }
        }
        enemy->HP -= ATK + SwordAttack;
        /*输出信息*/
        PrintTime();
        if(side == 1){
            cout << "red " <<PrintCreature[kind] << ' ' << number << " attacked blue " << PrintCreature[enemy->kind] << ' ' << enemy->number;
            cout << " in city " << city << " with " << HP << " elements and force " << ATK << endl;
        } else{
            cout << "blue " <<PrintCreature[kind] << ' ' << number << " attacked red " << PrintCreature[enemy->kind] << ' ' << enemy->number;
            cout << " in city " << city << " with " << HP << " elements and force " << ATK << endl;
        }
    }
    void FightBack(int side, Creature *enemy, int city){//side = 1 表示红魔军，size = -1 表示蓝魔军
        int SwordAttack = 0;
        if(!weaponList.empty()) {
            for (auto p = weaponList.begin();
                 p != weaponList.end(); p++) {
                if ((*p)->kind == 0) {
                    SwordAttack = (*p)->ATK;
                    (*p)->ATK = (*p)->ATK * 8 / 10;
                    if ((*p)->ATK == 0) {//sowrd攻击变为0时，视为失去sword
                        weaponList.erase(p);
                    }
                    break;//只会有一把剑
                }
            }
        }
        enemy->HP -= ATK * 5 / 10 + SwordAttack;
        /*输出信息*/
        PrintTime();
        if(side == 1){
            cout << "red " <<PrintCreature[kind] << ' ' << number << " fought back against blue " << PrintCreature[enemy->kind] << ' ' << enemy->number;
            cout << " in city " << city << endl;
        } else{
            cout << "blue " <<PrintCreature[kind] << ' ' << number << " fought back against red " << PrintCreature[enemy->kind] << ' ' << enemy->number;
            cout << " in city " << city << endl;
        }
    }
    virtual ~Creature(){
        for(auto &p: weaponList){
            delete p;
        }
        weaponList.clear();
    }
};


class Dragon:public Creature{//派生类，表示Dragon，count表示存在个数, Dragon只能有一个武器, 拥有属性"士气"
public:
    double morale;
    Dragon(int hp, int atk, int num, double mor):Creature(hp, atk, num, 1), morale(mor){
        /*分配武器*/
        Weapon *tmp;
        if(num % 3 == 0) {
            if(atk * 2 / 10 > 0) {
                tmp = new Sword(atk * 2 / 10);
                weaponList.push_back(tmp);//不能放最后，否则可能会把一个位置指针push进去
            }
        }
        else if(num % 3 == 1) {
            tmp = new Bomb();
            weaponList.push_back(tmp);
        }
        else {
            tmp = new Arrow();
            weaponList.push_back(tmp);
        }
    };
    Dragon():Creature(), morale(0){}
    virtual bool ifHaveArrow(){
        if(weaponList.empty()){
            return false;
        }
        if(weaponList[0]->kind == 2){
            return true;
        }
        return false;
    }
    virtual bool ifHaveBomb(){
        if(weaponList.empty()){
            return false;
        }
        if(weaponList[0]->kind == 1){
            return true;
        }
        return false;
    }
    virtual double GetMorale(){
        return morale;
    }
    virtual void MoraleAdd(){
        morale += 0.2;
    }
    virtual void MoraleDown(){
        morale -= 0.2;
    }
    ~Dragon(){}
};


class Ninja:public Creature{//派生类，表示Ninja，count表示存在个数
public:
    Ninja(int hp, int atk, int num):Creature(hp, atk, num, 2){
        /*分配武器*/
        Weapon *tmp1;
        Weapon *tmp2;
        if(num % 3 == 0) {
            if(atk * 2 / 10 > 0) {
                tmp1 = new Sword(atk * 2 / 10);
                weaponList.push_back(tmp1);

            }
        }
        else if(num % 3 == 1) {
            tmp1 = new Bomb();
            weaponList.push_back(tmp1);
        }
        else {
            tmp1 = new Arrow();
            weaponList.push_back(tmp1);
        }
        if((num+1) % 3 == 0) {
            if(atk * 2 / 10 > 0) {
                tmp2 = new Sword(atk * 2 / 10);
                weaponList.push_back(tmp2);
            }
        }
        else if((num+1) % 3 == 1) {
            tmp2 = new Bomb();
            weaponList.push_back(tmp2);
        }
        else {
            tmp2 = new Arrow();
            weaponList.push_back(tmp2);
        }
    };
    Ninja():Creature(){}
    virtual bool ifHaveArrow() {
        if (weaponList.empty()) {
            return false;
        }
        for (auto &p: weaponList) {
            if (p->kind == 2) {
                return true;
            }
        }
        return false;
    }
    virtual bool ifHaveBomb(){
        if(weaponList.empty()){
            return false;
        }
        for(auto &p: weaponList) {
            if (p->kind == 1) {
                return true;
            }
        }
        return false;
    }
    ~Ninja(){}
};


class Iceman:public Creature{//派生类，表示Iceman，count表示存在个数
public:
    int walkCount;
    Iceman(int hp, int atk, int num):Creature(hp, atk, num, 3), walkCount(0){
        /*分配武器*/
        Weapon *tmp;
        if(num % 3 == 0) {
            if(atk * 2 / 10 > 0) {
                tmp = new Sword(atk * 2 / 10);
                weaponList.push_back(tmp);
            }
        }
        else if(num % 3 == 1) {
            tmp = new Bomb();
            weaponList.push_back(tmp);
        }
        else {
            tmp = new Arrow();
            weaponList.push_back(tmp);
        }
    };
    Iceman():Creature(), walkCount(0){}
    virtual void CntMove(){
        walkCount++;
        if(walkCount == 2){
            DoMoveCost();
            walkCount = 0;
        }
    }
    virtual bool ifHaveArrow(){
        if(weaponList.empty()){
            return false;
        }
        if(weaponList[0]->kind == 2){
            return true;
        }
        return false;
    }
    virtual bool ifHaveBomb(){
        if(weaponList.empty()){
            return false;
        }
        if(weaponList[0]->kind == 1){
            return true;
        }
        return false;
    }
    virtual void DoMoveCost(){
        HP =  max(HP - lifeCost, 1);
        ATK += attackAdd;
    }
    ~Iceman(){}
};


class Lion:public Creature{//派生类，表示Lion，count表示存在个数
public:
    int loyalty;
    Lion(int hp, int atk, int num, int loyal):Creature(hp, atk, num, 4), loyalty(loyal){//lion没有武器
    };
    Lion():Creature(){
        loyalty = -1;
    }
    virtual bool ifHaveArrow(){
        if(weaponList.empty()){
            return false;
        }
        if(weaponList[0]->kind == 2){
            return true;
        }
        return false;
    }
    virtual bool ifHaveBomb(){
        if(weaponList.empty()){
            return false;
        }
        if(weaponList[0]->kind == 1){
            return true;
        }
        return false;
    }
    virtual int GetLoyalty(){
        return loyalty;
    }
    virtual void LoyaltyDown(){
        loyalty -= loyalDown;
    }
    ~Lion(){}
};


class Wolf:public Creature{//派生类，表示Wolf，count表示存在个数
public:
    Wolf(int hp, int atk, int num):Creature(hp, atk, num, 5){};
    Wolf():Creature(){}
    virtual void GrabWeapon(Creature *enemy){//n = 0表示是红魔军，n = 1表示是蓝魔军
        /*抢夺武器*/
        int ifGrab[3] = {1, 1, 1};//0, 1, 2分别代表Sword、Bomb和Arrow能否抢夺
        if(!weaponList.empty()) {
            for (auto &p: weaponList) {
                if (p != nullptr) {
                    ifGrab[p->kind] = 0;
                }
            }
        }
        if(!enemy->weaponList.empty()) {
            for (auto &p: enemy->weaponList) {
                if (p != nullptr && ifGrab[p->kind]) {
                    Weapon *tmp;
                    if (p->kind == 0) {
                        int attack = p->ATK;
                        tmp = new Sword(attack);
                        weaponList.push_back(tmp);
                    } else if (p->kind == 1) {
                        tmp = new Bomb();
                        weaponList.push_back(tmp);
                    } else {
                        int used = p->GetUseTime();
                        tmp = new Arrow(used);
                        weaponList.push_back(tmp);
                    }
                }
            }
        }
        /*打印信息*/
    }
    virtual bool ifHaveArrow() {
        if (weaponList.empty()) {
            return false;
        }
        for (auto &p: weaponList) {
            if (p->kind == 2) {
                return true;
            }
        }
        return false;
    }
    virtual bool ifHaveBomb(){
        if(weaponList.empty()){
            return false;
        }
        for(auto &p: weaponList) {
            if (p->kind == 1) {
                return true;
            }
        }
        return false;
    }
    ~Wolf(){}
};


/*战场类*/
class BattleField{
public:
    /* 22个场地，包括20个城市（最大）和两个司令部，我们规定0是西司令部，N+1是东司令部
     * 因为同一时刻每个城市最多只可能一方一个武士，所以用指针数组记录不同场地的武士类型，
     * 两个指针数组分别代表两军
     */
    Creature* blueCreature[22];
    Creature* redCreature[22];
    int fieldFlag[22];//0代表没有旗帜, 1代表红魔军旗帜, -1代表蓝魔军旗帜
    int citylife[22];//代表城市中生命元数量
    int city;//城市个数
    int whichSideWin[22];//记录每个城市每次战斗哪一方赢了，1代表红魔军赢了，-1代表蓝魔军赢了
    /*记录输赢, 便于战斗结束后司令部分发奖励和获得生命元*/
    int ifCityBlueWin[22];
    int ifCityRedWin[22];
    BattleField(int c):city(c){
        for(int i = 0; i <= city+1; i++){
            blueCreature[i] = nullptr;
            redCreature[i] = nullptr;
            fieldFlag[i] = 0;
            citylife[i] = 0;
            whichSideWin[i] = 0;
            ifCityBlueWin[i] = 0;
            ifCityRedWin[i] = 0;
        }
    }
    BattleField(){
        city = 0;
        for(int i = 0; i < 22; i++){
            blueCreature[i] = nullptr;
            redCreature[i] = nullptr;
            fieldFlag[i] = 0;
            citylife[i] = 0;
            whichSideWin[i] = 0;
            ifCityBlueWin[i] = 0;
            ifCityRedWin[i] = 0;
        }
    }

};


/*司令部生成武士, 0表示红魔军（西）生成武士，1表示蓝魔君（东）生成武士，在每小时的第0分降生武士*/
void CreateWorrier(BattleField &bf, int n){
    int whichOne;//用来判断生成哪一种武士
    if(n == 0) {//红魔军
        whichOne = (redNumber - 1) % 5;
        string tmp = redList[whichOne];
        if (redLife >= creatureHP[tmp]) {//如果可以生成该武士
            PrintTime();
            cout << "red ";
            redLife -= creatureHP[tmp];
            if (tmp == "dragon") {
                cout << "dragon " << redNumber << " born" << endl;
                Dragon *dra = new Dragon(creatureHP["dragon"], creatureATK["dragon"], redNumber, double(redLife) / creatureHP["dragon"]);
                cout << "Its morale is ";
                cout << setiosflags(ios::fixed) << setprecision(2) << dra->morale << endl;
                redNumber++;
                bf.redCreature[0] = dra;
            } else if (tmp == "ninja") {
                cout << "ninja " << redNumber << " born" << endl;
                Ninja *nin = new Ninja(creatureHP["ninja"], creatureATK["ninja"], redNumber);
                redNumber++;
                bf.redCreature[0] = nin;
            } else if (tmp == "iceman") {
                cout << "iceman " << redNumber << " born" << endl;
                Iceman *ice = new Iceman(creatureHP["iceman"], creatureATK["iceman"], redNumber);
                redNumber++;
                bf.redCreature[0] = ice;
            } else if (tmp == "lion") {
                cout << "lion " << redNumber << " born" << endl;
                cout << "Its loyalty is " << redLife << endl;
                Lion *lio = new Lion(creatureHP["lion"], creatureATK["lion"], redNumber, redLife);
                redNumber++;
                bf.redCreature[0] = lio;
            } else if (tmp == "wolf") {
                cout << "wolf " << redNumber << " born" << endl;
                Wolf *wol = new Wolf(creatureHP["wolf"], creatureATK["wolf"], redNumber);
                redNumber++;
                bf.redCreature[0] = wol;
            }
        } else {//不可以创造
            bf.redCreature[0] = nullptr;
        }
    }
    else {//蓝魔军
        whichOne = (blueNumber - 1) % 5;
        string tmp = blueList[whichOne];
        if (blueLife >= creatureHP[tmp]) {//如果可以生成该武士
            PrintTime();
            cout << "blue ";
            blueLife -= creatureHP[tmp];
            if (tmp == "dragon") {
                cout << "dragon " << blueNumber << " born" << endl;
                Dragon *dra = new Dragon(creatureHP["dragon"], creatureATK["dragon"], blueNumber, double(blueLife) / creatureHP["dragon"]);
                cout << "Its morale is ";
                cout << setiosflags(ios::fixed) << setprecision(2) << dra->morale << endl;
                blueNumber++;
                bf.blueCreature[bf.city+1] = dra;
            } else if (tmp == "ninja") {
                cout << "ninja " << blueNumber << " born" << endl;
                Ninja *nin = new Ninja(creatureHP["ninja"], creatureATK["ninja"], blueNumber);
                blueNumber++;
                bf.blueCreature[bf.city+1] = nin;
            } else if (tmp == "iceman") {
                cout << "iceman " << blueNumber << " born" << endl;
                Iceman *ice = new Iceman(creatureHP["iceman"], creatureATK["iceman"], blueNumber);
                blueNumber++;
                bf.blueCreature[bf.city+1] = ice;
            } else if (tmp == "lion") {
                cout << "lion " << blueNumber << " born" << endl;
                cout << "Its loyalty is " << blueLife << endl;
                Lion *lio = new Lion(creatureHP["lion"], creatureATK["lion"], blueNumber, blueLife);
                blueNumber++;
                bf.blueCreature[bf.city+1] = lio;
            } else if (tmp == "wolf") {
                cout << "wolf " << blueNumber << " born" << endl;
                Wolf *wol = new Wolf(creatureHP["wolf"], creatureATK["wolf"], blueNumber);
                blueNumber++;
                bf.blueCreature[bf.city+1] = wol;
            }
        } else {//不可以创造
            bf.blueCreature[bf.city+1] = nullptr;
        }
    }
}


/*每小时的5分，判断lion是否应该逃跑*/
void IfLionRun(BattleField &bf){
    for(int i = 0; i <= bf.city + 1; i++){
        /*到达敌方司令部的lion不会逃跑*/
        if(bf.redCreature[i] != nullptr) {
            if (bf.redCreature[i]->kind == 4 && bf.redCreature[i]->GetLoyalty() <= 0 && i != bf.city + 1) {
                PrintTime();
                cout << "red lion " << bf.redCreature[i]->number << " ran away" << endl;
                delete bf.redCreature[i];
                bf.redCreature[i] = nullptr;//lion逃跑了
            }
        }
        if(bf.blueCreature[i] != nullptr) {
            if (bf.blueCreature[i]->kind == 4 && bf.blueCreature[i]->GetLoyalty() <= 0 && i != 0) {
                PrintTime();
                cout << "blue lion " << bf.blueCreature[i]->number << " ran away" << endl;
                delete bf.blueCreature[i];
                bf.blueCreature[i] = nullptr;//lion逃跑了
            }
        }
    }
}


/*每小时的10分，武士朝敌人司令部方向前进一步*/
void March(BattleField &bf){
    /*先判断是否获胜*/
    int redNoMarch = 0;
    int blueNoMarch = 0;
    if(bf.redCreature[bf.city+1] != nullptr && bf.redCreature[bf.city] != nullptr){//红魔军胜了
        ifRedWin = 1;
    }
    if(bf.blueCreature[0] != nullptr && bf.blueCreature[1] != nullptr){//蓝魔军胜了
        ifBlueWin = 1;
    }
    /*红魔军进军*/
    for(int i = bf.city + 1; i > 0; i--) {
        if(i == bf.city + 1 && bf.redCreature[bf.city+1] != nullptr && bf.redCreature[bf.city] == nullptr){
            redNoMarch = 1;
            continue;
        }
        bf.redCreature[i] = bf.redCreature[i-1];
        if(bf.redCreature[i] != nullptr) {
            bf.redCreature[i]->CntMove();
        }
    }
    /*把司令部的warrior清除*/
    bf.redCreature[0] = nullptr;
    /*蓝魔军进军*/
    for(int i = 0; i < bf.city + 1; i++){
        if(i == 0 && bf.blueCreature[0] != nullptr && bf.blueCreature[1] == nullptr){
            blueNoMarch = 1;
            continue;
        }
        bf.blueCreature[i] = bf.blueCreature[i+1];
        if(bf.blueCreature[i] != nullptr) {
            bf.blueCreature[i]->CntMove();
        }
    }
    /*把司令部的warrior清除*/
    bf.blueCreature[bf.city+1] = nullptr;
    /*输出结果*/
    if(bf.blueCreature[0] != nullptr && blueNoMarch == 0){//红魔军司令部被占领
        PrintTime();
        cout << "blue " << PrintCreature[bf.blueCreature[0]->kind] << ' ' << bf.blueCreature[0]->number
             << " reached red headquarter with " << bf.blueCreature[0]->HP << " elements and force " << bf.blueCreature[0]->ATK << endl;
        if(ifBlueWin) {
            PrintTime();
            cout << "red headquarter was taken" << endl;
        }
    }
    for(int i = 1; i <= bf.city; i++){
        if(bf.redCreature[i] != nullptr){
            PrintTime();
            cout << "red " << PrintCreature[bf.redCreature[i]->kind] << " " << bf.redCreature[i]->number
                 << " marched to city " << i << " with " << bf.redCreature[i]->HP << " elements and force "
                 << bf.redCreature[i]->ATK << endl;
        }
        if(bf.blueCreature[i] != nullptr){
            PrintTime();
            cout << "blue " << PrintCreature[bf.blueCreature[i]->kind] << " " << bf.blueCreature[i]->number
                 << " marched to city " << i << " with " << bf.blueCreature[i]->HP << " elements and force "
                 << bf.blueCreature[i]->ATK << endl;
        }
    }
    if(bf.redCreature[bf.city+1] != nullptr  && redNoMarch == 0){//蓝魔军司令部被占领
        PrintTime();
        cout << "red " << PrintCreature[bf.redCreature[bf.city+1]->kind] << ' ' << bf.redCreature[bf.city+1]->number
             << " reached blue headquarter with " << bf.redCreature[bf.city+1]->HP << " elements and force " << bf.redCreature[bf.city+1]->ATK << endl;
        if(ifRedWin) {
            PrintTime();
            cout << "blue headquarter was taken" << endl;
        }
    }
}


/*每小时的20分：每个城市产出10个生命元*/
void CityCreateLife(BattleField &bf){
    for(int i = 1; i <= bf.city; i++){
        bf.citylife[i] += 10;
    }
}


/*每小时的30分，武士取走该城市中的所有生命元*/
void WorrierGrabLife(BattleField &bf){
    for(int i = 1; i <= bf.city; i++){
        /*对红魔军判断*/
        if(bf.redCreature[i] != nullptr && bf.blueCreature[i] == nullptr) {
            /*输出信息*/
            PrintTime();
            cout << "red " << PrintCreature[bf.redCreature[i]->kind] << ' ' << bf.redCreature[i]->number
                 << " earned " << bf.citylife[i] << " elements for his headquarter" << endl;
            redLife += bf.citylife[i];
            bf.citylife[i] = 0;
        }
        /*对蓝魔军判断*/
        else if(bf.blueCreature[i] != nullptr && bf.redCreature[i] == nullptr) {
            /*输出信息*/
            PrintTime();
            cout << "blue " << PrintCreature[bf.blueCreature[i]->kind] << ' ' << bf.blueCreature[i]->number
                 << " earned " << bf.citylife[i] << " elements for his headquarter" << endl;
            blueLife += bf.citylife[i];
            bf.citylife[i] = 0;
        }
    }
}


/*每小时的35分, 拥有arrow的武士放箭*/
void ArrowAttack(BattleField &bf){
    for(int i = 1; i <= bf.city; i++){
        if(i >= 1 && i <= bf.city -1) {//红魔军射
            if (bf.redCreature[i] != nullptr && bf.redCreature[i]->ifHaveArrow() && bf.blueCreature[i + 1] != nullptr) {
                bf.blueCreature[i + 1]->HP -= arrowATK;
                for (auto p = (bf.redCreature[i]->weaponList).begin();
                     p != (bf.redCreature[i]->weaponList).end(); p++) {
                    if ((*p)->kind == 2) {
                        (*p)->AddUseTime();
                        if ((*p)->GetUseTime() == 3) {
                            (bf.redCreature[i]->weaponList).erase(p);
                        }
                        break;
                    }
                }
                /*输出信息*/
                PrintTime();
                cout << "red " << PrintCreature[bf.redCreature[i]->kind] << ' ' << bf.redCreature[i]->number << " shot";
                if (bf.blueCreature[i + 1]->ifDead()) {
                    cout << " and killed blue " << PrintCreature[bf.blueCreature[i + 1]->kind] << ' '
                         << bf.blueCreature[i + 1]->number;
                }
                cout << endl;
            }
        }
        if(i >= 2 && i <= bf.city){//蓝魔军射
            if(bf.blueCreature[i] != nullptr && bf.blueCreature[i]->ifHaveArrow() && bf.redCreature[i-1] != nullptr){
                bf.redCreature[i-1]->HP -= arrowATK;
                for(auto p = (bf.blueCreature[i]->weaponList).begin(); p != (bf.blueCreature[i]->weaponList).end(); p++){
                    if((*p)->kind == 2){
                        (*p)->AddUseTime();
                        if((*p)->GetUseTime() == 3){
                            (bf.blueCreature[i]->weaponList).erase(p);
                        }
                        break;
                    }
                }
                /*输出信息*/
                PrintTime();
                cout << "blue " << PrintCreature[bf.blueCreature[i]->kind] << ' ' << bf.blueCreature[i]->number << " shot";
                if(bf.redCreature[i-1]->ifDead()){
                    cout << " and killed red " << PrintCreature[bf.redCreature[i-1]->kind] << ' ' << bf.redCreature[i-1]->number;
                }
                cout << endl;
            }
        }
    }
    /*注意这里射死不要删除, 留到40分开战的时候判断是否胜利*/
}


/*判断p1是否一定可以被p2杀死*/
bool ifCanBeKilled(BattleField &bf, int side, Creature *p1, Creature *p2, int city){//side = 1代表p1是红魔军；= -1代表p1是蓝魔军
    int swordAttack1 = 0;
    int swordAttack2 = 0;
    if(!(p2->weaponList).empty()) {
        for (auto &p: p2->weaponList) {
            if (p->kind == 0) {
                swordAttack2 = p->ATK;
                break;//只会有一把剑
            }
        }
    }
    if(!(p1->weaponList).empty()) {
        for (auto &p: p1->weaponList) {
            if (p->kind == 0) {
                swordAttack1 = p->ATK;
                break;//只会有一把剑
            }
        }
    }
    if(side == 1) {//p1是红魔军
        if(bf.fieldFlag[city] == 1 || (bf.fieldFlag[city] == 0 && city % 2 == 1)){//自己先攻击
            if(p2->HP > swordAttack1 + p1->ATK && p2->kind != 2 && p1->HP <= swordAttack2 + p2->ATK * 5 / 10){//会被非ninja反击死
                return true;
            } else {
                return false;
            }
        } else{//自己被攻击
            if(p1->HP <= swordAttack2 + p2->ATK){
                return true;
            } else{
                return false;
            }
        }
    } else if(side == -1){//p1是蓝魔军
        if(bf.fieldFlag[city] == -1 || (bf.fieldFlag[city] == 0 && city % 2 == 0)){//自己先攻击
            if(p2->HP > swordAttack1 + p1->ATK && p2->kind != 2 && p1->HP <= swordAttack2 + p2->ATK * 5 / 10){//会被非ninja反击死
                return true;
            } else {
                return false;
            }
        } else{//自己被攻击
            if(p1->HP <= swordAttack2 + p2->ATK){
                return true;
            } else{
                return false;
            }
        }
    }
}


/*每小时的38分, 拥有bomb的武士判断是否应该同归于尽*/
void BombAttack(BattleField &bf){
    for(int i = 1; i <= bf.city; i++){
        /*先判断红魔军*/
        if(bf.redCreature[i] != nullptr && bf.redCreature[i]->HP > 0 && bf.redCreature[i]->ifHaveBomb() && bf.blueCreature[i] != nullptr && bf.blueCreature[i]->HP > 0){//加一条判断防止对面被射死依然会导致同归于尽
            if(ifCanBeKilled(bf, 1, bf.redCreature[i], bf.blueCreature[i], i)){//同归于尽
                /*输出信息*/
                PrintTime();
                cout << "red " << PrintCreature[bf.redCreature[i]->kind] << ' ' << bf.redCreature[i]->number << " used a bomb and killed blue ";
                cout << PrintCreature[bf.blueCreature[i]->kind] << ' ' << bf.blueCreature[i]->number << endl;
                /*处理worrier*/
                delete bf.redCreature[i];
                delete bf.blueCreature[i];
                bf.redCreature[i] = nullptr;
                bf.blueCreature[i] = nullptr;
            }
        }
        /*再判断蓝魔军*/
        if(bf.blueCreature[i] != nullptr && bf.blueCreature[i]->HP > 0 && bf.blueCreature[i]->ifHaveBomb() && bf.redCreature[i] != nullptr && bf.redCreature[i]->HP > 0){//加一条判断防止对面被射死依然会导致同归于尽
            if(ifCanBeKilled(bf, -1, bf.blueCreature[i], bf.redCreature[i], i)){//同归于尽
                /*输出信息*/
                PrintTime();
                cout << "blue " << PrintCreature[bf.blueCreature[i]->kind] << ' ' << bf.blueCreature[i]->number << " used a bomb and killed red ";
                cout << PrintCreature[bf.redCreature[i]->kind] << ' ' << bf.redCreature[i]->number << endl;
                /*处理worrier*/
                delete bf.blueCreature[i];
                delete bf.redCreature[i];
                bf.blueCreature[i] = nullptr;
                bf.redCreature[i] = nullptr;
            }
        }
    }
}


/*下面是对战斗完的处理，注意不会处理lion给对面加血的情况，这个特殊处理*/
/*战斗完双方都没死*/
void Win2Win(BattleField &bf, int city, int firstAttack){//如果都没死，dragon可能会怒吼，但依然会减怒气; firstAttack = 1代表红魔军先攻； = -1 代表蓝魔军先攻；lion会减loyalty
    bf.whichSideWin[city] = 0;
    if(firstAttack == 1 && bf.redCreature[city]->kind == 1){
        bf.redCreature[city]->MorialDown();
        if(bf.redCreature[city]->GetMorale() > 0.8){
            /*欢呼*/
            PrintTime();
            cout << "red dragon " << bf.redCreature[city]->number << " yelled in city " << city << endl;
        }
    } else if(firstAttack == -1 && bf.blueCreature[city]->kind == 1){
        bf.blueCreature[city]->MorialDown();
        if(bf.blueCreature[city]->GetMorale() > 0.8){
            /*欢呼*/
            PrintTime();
            cout << "blue dragon " << bf.blueCreature[city]->number << " yelled in city " << city << endl;
        }
    }
    /*lion减loyalty*/
    if(bf.blueCreature[city]->kind == 4){
        bf.blueCreature[city]->LoyaltyDown();
    }
    if(bf.redCreature[city]->kind == 4){
        bf.redCreature[city]->LoyaltyDown();
    }
}
/*战斗完双方都死了*/
void Lose2Lose(BattleField &bf, int city){
    bf.whichSideWin[city] = 0;
}
/*战斗完蓝魔军没死，红魔军死了*/
void BlueWin(BattleField &bf, int city, int firstAttack){//firstAttack = 1代表红魔军先攻； = -1 代表蓝魔军先攻
    bf.ifCityBlueWin[city] = 1;
    /*如果狼人赢了, 会偷武器*/
    if(bf.blueCreature[city]->kind == 5){
        bf.blueCreature[city]->GrabWeapon(bf.redCreature[city]);
    }
    /*如果dragon赢了，可能会欢呼*/
    if(bf.blueCreature[city]->kind == 1){
        bf.blueCreature[city]->MoraleAdd();
        if(firstAttack == -1 && bf.blueCreature[city]->GetMorale() > 0.8){//会欢呼
            /*欢呼*/
            PrintTime();
            cout << "blue dragon " << bf.blueCreature[city]->number << " yelled in city " << city << endl;
        }
    }
    /*输出信息*/
    PrintTime();
    cout << "blue " << PrintCreature[bf.blueCreature[city]->kind] << ' ' << bf.blueCreature[city]->number
         << " earned " << bf.citylife[city] << " elements for his headquarter" << endl;
    if(bf.whichSideWin[city] == -1 && bf.fieldFlag[city] != -1){//如果上一场也是蓝魔军赢了且本来插的不是蓝旗, 插旗帜
        bf.fieldFlag[city] = -1;
        /*输出信息*/
        PrintTime();
        cout << "blue flag raised in city " << city << endl;
    }
}
/*战斗完红魔军没死，蓝魔军死了*/
void RedWin(BattleField &bf, int city, int firstAttack){//firstAttack = 1代表红魔军先攻； = -1 代表蓝魔军先攻
    bf.ifCityRedWin[city] = 1;
    /*如果狼人赢了, 会偷武器*/
    if(bf.redCreature[city]->kind == 5){
        bf.redCreature[city]->GrabWeapon(bf.blueCreature[city]);
    }
    /*如果dragon赢了，可能会欢呼*/
    if(bf.redCreature[city]->kind == 1){
        bf.redCreature[city]->MoraleAdd();
        if(firstAttack == 1 && bf.redCreature[city]->GetMorale() > 0.8){//会欢呼
            /*欢呼*/
            PrintTime();
            cout << "red dragon " << bf.redCreature[city]->number << " yelled in city " << city << endl;
        }
    }
    /*输出信息*/
    PrintTime();
    cout << "red " << PrintCreature[bf.redCreature[city]->kind] << ' ' << bf.redCreature[city]->number
         << " earned " << bf.citylife[city] << " elements for his headquarter" << endl;
    if(bf.whichSideWin[city] == 1 && bf.fieldFlag[city] != 1){//如果上一场也是红魔军赢了且本来插的不是红旗, 插旗帜
        bf.fieldFlag[city] = 1;
        /*输出信息*/
        PrintTime();
        cout << "red flag raised in city " << city << endl;
    }
}


/*每小时的40分，开战*/
void Fight(BattleField &bf) {
    for (int i = 1; i <= bf.city; i++) {
        if (bf.blueCreature[i] != nullptr && bf.redCreature[i] != nullptr) {//都有人，开战
            if (bf.fieldFlag[i] == -1 || (bf.fieldFlag[i] == 0 && i % 2 == 0)) {//偶数号城市或者有蓝色方旗帜，蓝魔军先攻
                /*先特判是否有人死了*/
                if (bf.redCreature[i]->ifDead() && !bf.blueCreature[i]->ifDead()) {//红魔军死了，蓝魔军没死
                    BlueWin(bf, i, -1);
                    /*注意提前被射死的lion不会给对面加血*/
                } else if (!bf.redCreature[i]->ifDead() && bf.blueCreature[i]->ifDead()) {//红魔军没死，蓝魔军死了
                    RedWin(bf, i, -1);
                    /*注意提前被射死的lion不会给对面加血*/
                } else if (bf.redCreature[i]->ifDead() && bf.blueCreature[i]->ifDead()) {//都死了, 视为战斗未开始
                } else {//都没死, 正常开战, 蓝魔军先攻
                    int blueLionLife = 0;
                    int redLionLife = 0;
                    if (bf.blueCreature[i]->kind == 4) {
                        blueLionLife = bf.blueCreature[i]->HP;
                    }
                    if (bf.redCreature[i]->kind == 4) {
                        redLionLife = bf.redCreature[i]->HP;
                    }
                    bf.blueCreature[i]->Attack(-1, bf.redCreature[i], i);
                    if (!bf.redCreature[i]->ifDead() && bf.redCreature[i]->kind != 2) {//没死且不是ninja，进行反击
                        bf.redCreature[i]->FightBack(1, bf.blueCreature[i], i);
                    }
                    /*战斗结束，处理现场, 注意一旦开战不可能都死，最多一方死*/
                    if (bf.redCreature[i]->ifDead() && !bf.blueCreature[i]->ifDead()) {//红魔军死了，蓝魔军没死
                        if (redLionLife != 0) {
                            bf.blueCreature[i]->HP += redLionLife;
                        }
                        /*输出信息*/
                        PrintTime();
                        cout << "red " << PrintCreature[bf.redCreature[i]->kind] << ' ' << bf.redCreature[i]->number << " was killed in city " << i << endl;

                        BlueWin(bf, i, -1);
                    } else if (!bf.redCreature[i]->ifDead() && bf.blueCreature[i]->ifDead()) {//蓝魔军死了，红魔军没死
                        if (blueLionLife != 0) {
                            bf.redCreature[i]->HP += blueLionLife;
                        }
                        /*输出信息*/
                        PrintTime();
                        cout << "blue " << PrintCreature[bf.blueCreature[i]->kind] << ' ' << bf.blueCreature[i]->number << " was killed in city " << i << endl;

                        RedWin(bf, i, -1);
                    } else {//都没死
                        Win2Win(bf, i, -1);
                    }
                }
            } else if (bf.fieldFlag[i] == 1 || (bf.fieldFlag[i] == 0 && i % 2 == 1)) {//奇数号城市或者有红色方旗帜，红魔军先攻
                /*先特判是否有人死了*/
                if (bf.redCreature[i]->ifDead() && !bf.blueCreature[i]->ifDead()) {//红魔军死了，蓝魔军没死
                    BlueWin(bf, i, 1);
                    /*注意提前被射死的lion不会给对面加血*/
                } else if (!bf.redCreature[i]->ifDead() && bf.blueCreature[i]->ifDead()) {//红魔军没死，蓝魔军死了
                    RedWin(bf, i, 1);
                    /*注意提前被射死的lion不会给对面加血*/
                } else if (bf.redCreature[i]->ifDead() && bf.blueCreature[i]->ifDead()) {//都死了, 视为战斗没开始
                } else {//都没死, 正常开战, 红魔军先攻
                    int blueLionLife = 0;
                    int redLionLife = 0;
                    if (bf.blueCreature[i]->kind == 4) {
                        blueLionLife = bf.blueCreature[i]->HP;
                    }
                    if (bf.redCreature[i]->kind == 4) {
                        redLionLife = bf.redCreature[i]->HP;
                    }
                    bf.redCreature[i]->Attack(1, bf.blueCreature[i], i);
                    if (!bf.blueCreature[i]->ifDead() && bf.blueCreature[i]->kind != 2) {//没死且不是ninja，进行反击
                        bf.blueCreature[i]->FightBack(-1, bf.redCreature[i], i);
                    }
                    /*战斗结束，处理现场, 注意一旦开战不可能都死，最多一方死*/
                    if (bf.redCreature[i]->ifDead() && !bf.blueCreature[i]->ifDead()) {//红魔军死了，蓝魔军没死
                        if (redLionLife != 0) {
                            bf.blueCreature[i]->HP += redLionLife;
                        }
                        /*输出信息*/
                        PrintTime();
                        cout << "red " << PrintCreature[bf.redCreature[i]->kind] << ' ' << bf.redCreature[i]->number << " was killed in city " << i << endl;

                        BlueWin(bf, i, 1);
                    } else if (!bf.redCreature[i]->ifDead() && bf.blueCreature[i]->ifDead()) {//蓝魔军死了，红魔军没死
                        if (blueLionLife != 0) {
                            bf.redCreature[i]->HP += blueLionLife;
                        }
                        /*输出信息*/
                        PrintTime();
                        cout << "blue " << PrintCreature[bf.blueCreature[i]->kind] << ' ' << bf.blueCreature[i]->number << " was killed in city " << i << endl;

                        RedWin(bf, i, 1);
                    } else {//都没死
                        Win2Win(bf, i, 1);
                    }
                }
            }
        }
        /*在外面更新，因为有可能城市只有一个worrier被射死的情况*/
        if(bf.redCreature[i] != nullptr && bf.redCreature[i]->ifDead()){
            delete bf.redCreature[i];
            bf.redCreature[i] = nullptr;
        }
        if(bf.blueCreature[i] != nullptr && bf.blueCreature[i]->ifDead()){
            delete bf.blueCreature[i];
            bf.blueCreature[i] = nullptr;
        }
    }
}


/*开战结束，分发奖励*/
void Award(BattleField &bf){
    /*红魔军分发奖励*/
    for(int i = bf.city; i >= 1; i--){
        if(bf.ifCityRedWin[i] && redLife >= 8){
            bf.redCreature[i]->HP += 8;
            redLife -= 8;
        }
    }
    /*蓝魔军分发奖励*/
    for(int i = 1; i <= bf.city; i++){
        if(bf.ifCityBlueWin[i] && blueLife >= 8){
            bf.blueCreature[i]->HP += 8;
            blueLife -= 8;
        }
    }
}


/*分发完奖励，领取生命元*/
void CollectLife(BattleField &bf){
    for(int i = 1; i <= bf.city; i++){
        if(bf.ifCityRedWin[i]){
            redLife += bf.citylife[i];
            bf.citylife[i] = 0;
            bf.whichSideWin[i] = 1;
            bf.ifCityRedWin[i] = 0;
        }else if(bf.ifCityBlueWin[i]){
            /*输出信息*/
            blueLife += bf.citylife[i];
            bf.citylife[i] = 0;
            bf.whichSideWin[i] = -1;
            bf.ifCityBlueWin[i] = 0;
        }
    }
}


/*每小时的50分，司令部报告它拥有的生命元数量*/
void DeclareSquareLife(BattleField &bf){
    PrintTime();
    cout << redLife << " elements in red headquarter" << endl;
    PrintTime();
    cout << blueLife << " elements in blue headquarter" << endl;
}


/*每小时的55分，每个武士报告其拥有的武器情况*/
void DeclareWarriorWeapon(BattleField &bf){
    /*显然，在经过march后，如果还能经历到这一步，不会出现有武士在自家司令部的情况, 可能在对方司令部*/
    for(int i = 0; i <= bf.city + 1; i++){
        /*先输出红方*/
        if(bf.redCreature[i] != nullptr) {
            PrintTime();
            cout << "red " << PrintCreature[bf.redCreature[i]->kind] << ' ' << bf.redCreature[i]->number << " has ";
            int ifSword = 0;
            int ifBomb = 0;
            int ifArrow = 0;
            Weapon *sword;
            Weapon *bomb;
            Weapon *arrow;
            for(auto &p: bf.redCreature[i]->weaponList){
                if(p->kind == 0){
                    ifSword = 1;
                    sword = p;
                } else if(p->kind == 1){
                    ifBomb = 1;
                    bomb = p;
                } else{
                    ifArrow = 1;
                    arrow = p;
                }
            }
            if(ifArrow){
                cout << "arrow(" << 3 - arrow->GetUseTime() << ')';
            }
            if(ifBomb){
                if(ifArrow){
                    cout << ',';
                }
                cout << "bomb";
            }
            if(ifSword){
                if(ifArrow || ifBomb){
                    cout << ',';
                }
                cout << "sword(" << sword->ATK << ')';
            }
            if(!ifArrow && !ifBomb && !ifSword){
                cout << "no weapon";
            }
            cout << endl;
        }
    }
    for(int i = 0; i <= bf.city + 1; i++){
        /*再输出蓝方*/
        if(bf.blueCreature[i] != nullptr) {
            PrintTime();
            cout << "blue " << PrintCreature[bf.blueCreature[i]->kind] << ' ' << bf.blueCreature[i]->number << " has ";
            int ifSword = 0;
            int ifBomb = 0;
            int ifArrow = 0;
            Weapon *sword;
            Weapon *bomb;
            Weapon *arrow;
            if(!(bf.blueCreature[i]->weaponList).empty()) {
                for (auto &p: bf.blueCreature[i]->weaponList) {
                    if (p->kind == 0) {
                        ifSword = 1;
                        sword = p;
                    } else if (p->kind == 1) {
                        ifBomb = 1;
                        bomb = p;
                    } else {
                        ifArrow = 1;
                        arrow = p;
                    }
                }
            }
            if(ifArrow){
                cout << "arrow(" << 3 - arrow->GetUseTime() << ')';
            }
            if(ifBomb){
                if(ifArrow){
                    cout << ',';
                }
                cout << "bomb";
            }
            if(ifSword){
                if(ifArrow || ifBomb){
                    cout << ',';
                }
                cout << "sword(" << sword->ATK << ')';
            }
            if(!ifArrow && !ifBomb && !ifSword){
                cout << "no weapon";
            }
            cout << endl;
        }
    }
}


int main(){
    int t;
    /*M表示生命元，N表示城市数，K表示lion忠诚度降低数，T表示输出截止时间*/
    int M;
    int dragonHP, ninjaHP, icemanHP, lionHP, wolfHP;
    int dragonATK, ninjaATK, icemanATK, lionATK, wolfATK;
    cin >> t;
    /*初始化武器*/
    weaponNumber["sword"] = 0;
    weaponNumber["bomb"] = 1;
    weaponNumber["arrow"] = 2;
    /*初始化武士对应量*/
    PrintCreature[1] = "dragon";
    PrintCreature[2] = "ninja";
    PrintCreature[3] = "iceman";
    PrintCreature[4] = "lion";
    PrintCreature[5] = "wolf";
    /*为输出时间做准备*/
    cout << setfill('0');
    for(int i = 0; i < t; i++){
        cin >> M >> cityCount >> arrowATK >> loyalDown >> totalTime;
        cin >> dragonHP >> ninjaHP >> icemanHP >> lionHP >> wolfHP;
        cin >> dragonATK >> ninjaATK >> icemanATK >> lionATK >> wolfATK;
        /*每组样例初始化数据*/
        blueLife = redLife = M;
        timeCountHour = timeCountMinute = 0;
        blueNumber = redNumber = 1;
        ifRedWin = ifBlueWin = 0;
        creatureHP.clear();
        creatureATK.clear();
        creatureHP["dragon"] = dragonHP;
        creatureHP["ninja"] = ninjaHP;
        creatureHP["iceman"] = icemanHP;
        creatureHP["lion"] = lionHP;
        creatureHP["wolf"] = wolfHP;
        creatureATK["dragon"] = dragonATK;
        creatureATK["ninja"] = ninjaATK;
        creatureATK["iceman"] = icemanATK;
        creatureATK["lion"] = lionATK;
        creatureATK["wolf"] = wolfATK;
        BattleField battlefield(cityCount);
        cout << "Case " << i+1 << ':' << endl;
        while(timeCountHour * 60 + timeCountMinute <= totalTime){
            if(ifRedWin || ifBlueWin){//如果司令部被占领，就结束了
                break;
            }
            if(timeCountMinute == 0){//武士降生
                CreateWorrier(battlefield, 0);
                CreateWorrier(battlefield, 1);
            } else if(timeCountMinute == 5){//lion逃跑
                IfLionRun(battlefield);
            } else if(timeCountMinute == 10){//进军
                March(battlefield);
            } else if(timeCountMinute == 20){
                CityCreateLife(battlefield);
            }  else if(timeCountMinute == 30){
                WorrierGrabLife(battlefield);
            } else if(timeCountMinute == 35){//狼人偷武器
                ArrowAttack(battlefield);
            }  else if(timeCountMinute == 38) {
                BombAttack(battlefield);
            } else if(timeCountMinute == 40){//开战
                Fight(battlefield);
                Award(battlefield);
                CollectLife(battlefield);
            } else if(timeCountMinute == 50){//汇报生命元
                DeclareSquareLife(battlefield);
            } else if(timeCountMinute == 55){//汇报武士武器
                DeclareWarriorWeapon(battlefield);
            }
            timeCountMinute++;
            if(timeCountMinute == 60){
                timeCountHour++;
                timeCountMinute = 0;
            }
        }
    }
    return 0;
}