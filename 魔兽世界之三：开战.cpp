#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
#define xDEBUG

unordered_map<string, int> weaponNumber;//武器编号
/*事件进行时间*/
int timeCountHour;
int timeCountMinute;


/*初始输入*/
int blueLife, redLife;
int cityCount;
int loyalDown;
int totalTime;
unordered_map<string, int> creatureHP;
unordered_map<string, int> creatureATK;


/*红魔军，蓝魔军*/
const string redList[5] = {"iceman", "lion", "wolf", "ninja", "dragon"};
const string blueList[5] = {"lion", "dragon", "ninja", "iceman", "wolf"};
int blueNumber, redNumber;//武士编号
int blueIfCreateWarrior, redIfCreateWarrior;//能否继续制造武士
int ifWin;
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
    Bomb(int atk):Weapon(atk, 1){}
    Bomb():Weapon(){}
    ~Bomb(){}
};


class Arrow:public Weapon{
public:
    int useTime;
    Arrow(int atk):Weapon(atk, 2){
        useTime = 0;
    }
    Arrow():Weapon(){
        useTime = 0;
    }
    virtual int GetUseTime(){
        return useTime;
    }
    virtual void AddUseTime(){
        useTime++;
    }
    ~Arrow(){}
};

/*编写cmp函数，便于给weaponList排序，cmp1用于Fight时候排序，cmp2用于wolf抢武器时候排序*/
bool cmp1 (Weapon * w1, Weapon *w2){
    if(w1->kind < w2->kind){//编号从小到大排序
        return true;
    } else if(w1->kind == w2->kind && w1->kind == 2){//arrow按照使用次数排序
        return w1->GetUseTime() > w2->GetUseTime();
    } else{
        return false;
    }
}
bool cmp2 (Weapon * w1, Weapon *w2){
    if(w1->kind < w2->kind){//编号从小到大排序
        return true;
    } else if(w1->kind == w2->kind && w1->kind == 2){//arrow按照使用次数排序
        return w1->GetUseTime() < w2->GetUseTime();
    } else{
        return false;
    }
}


class Creature{//基类，有两个成员变量HP和ATK
public:
    int HP;
    int ATK;
    int number;//编号
    int swordCount;
    int bombCount;
    int arrowCount;
    /*种类，判断creature是哪一种，我们规定dragon、ninja、iceman、lion、wolf分别是1，2，3，4，5*/
    int kind;
    vector<Weapon *> weaponList;
    Creature(int hp, int atk, int num, int k): HP(hp),ATK(atk), number(num), kind(k){
        weaponList.clear();
        swordCount = bombCount = arrowCount = 0;
    }
    Creature(){
        weaponList.clear();
        HP = 0;
        ATK = 0;
        number = 0;
        kind = -1;
        swordCount = bombCount = arrowCount = 0;
    }
    virtual int GetLoyalty(){//对于除lion的warrior，用不到这个，这个函数是专门给lion编写的
        return 1;
    }
    virtual void DoMoveCost(){}//lion会降低loyalty，iceman会掉血
    virtual void GrabWeapon(Creature *enemy, int n, int city){}//wolf抢武器的特殊函数
    void GrabWeaponWin(Creature *enemy){//战利品夺取
        /*抢敌人编号最小的武器, 这里没用过的arrow先抢*/
        sort((enemy->weaponList).begin(), (enemy->weaponList).end(), cmp2);
        while(weaponList.size() < 10 && !enemy->weaponList.empty()){//可以抢，就抢
            if(enemy->weaponList[0]->kind == 0){//抢夺sword
                Sword *tmp = new Sword(ATK * 2 / 10);
                swordCount++;
                enemy->swordCount--;
                weaponList.push_back(tmp);
            } else if(enemy->weaponList[0]->kind == 1){//抢夺bomb
                Bomb *tmp = new Bomb(ATK * 4 /10);
                bombCount++;
                enemy->bombCount--;
                weaponList.push_back(tmp);
            } else if(enemy->weaponList[0]->kind == 2){//抢夺arrow, arrow的usetime要保持一致
                Arrow *tmp = new Arrow(ATK * 3 / 10);
                arrowCount++;
                tmp->useTime = enemy->weaponList[0]->GetUseTime();
                enemy->arrowCount--;
                weaponList.push_back(tmp);
            }
            enemy->weaponList.erase(enemy->weaponList.begin());//敌人武器被抢夺，删去
        }
    }
    bool IfDead() const{
        return HP <= 0;
    }
    void Attack(Creature *enemy){
        if(weaponList.empty()){//如果没有武器 被动挨打
            return;
        }
        Weapon *curWeapon = weaponList[0];
        weaponList.erase(weaponList.begin());
        enemy->HP -= curWeapon->ATK;
#ifdef DEBUG
        cout << "kind:" << curWeapon->kind << endl;
        cout << "enemy->HP:" << enemy->HP + curWeapon->ATK << "->" << enemy->HP << endl;
        for(int check = 0; check < weaponList.size(); check++){
            cout << weaponList[check]->kind << endl;
        }
#endif
        if(curWeapon->kind == 1){//如果武器是bomb
            if (kind != 2) {//除ninja外都会被炸伤, 且bomb用完丢弃
                HP -= curWeapon->ATK / 2;
            }
            bombCount--;
        } else if(curWeapon->kind == 2){
            curWeapon->AddUseTime();
            if(curWeapon->GetUseTime() != 2){//arrow用两次才扔掉
                weaponList.push_back(curWeapon);
            } else{
                arrowCount--;
            }
        } else{
            weaponList.push_back(curWeapon);
        }
    }
    virtual ~Creature(){
        while(!weaponList.empty()) {
            Weapon *tmp = weaponList.front();
            delete tmp;
            weaponList.erase(weaponList.begin());
        }
    }
};


class Dragon:public Creature{//派生类，表示Dragon，count表示存在个数
public:
    Dragon(int hp, int atk, int num):Creature(hp, atk, num, 1){
        /*分配武器*/
        if(num % 3 == 0) {
            Sword *tmp = new Sword(atk * 2 / 10);
            swordCount++;
            weaponList.push_back(tmp);
        }
        else if(num % 3 == 1) {
            Bomb *tmp = new Bomb(atk * 4 /10);
            bombCount++;
            weaponList.push_back(tmp);
        }
        else {
            Arrow *tmp = new Arrow(atk * 3 / 10);
            arrowCount++;
            weaponList.push_back(tmp);
        }
    };
    Dragon():Creature(){}
    ~Dragon(){}
};


class Ninja:public Creature{//派生类，表示Ninja，count表示存在个数
public:
    Ninja(int hp, int atk, int num):Creature(hp, atk, num, 2){
        /*分配武器*/
        if(num % 3 == 0) {
            Sword *tmp1 = new Sword(atk * 2 / 10);
            swordCount++;
            weaponList.push_back(tmp1);
        }
        else if(num % 3 == 1) {
            Bomb *tmp1 = new Bomb(atk * 4 /10);
            bombCount++;
            weaponList.push_back(tmp1);
        }
        else {
            Arrow *tmp1 = new Arrow(atk * 3 / 10);
            arrowCount++;
            weaponList.push_back(tmp1);
        }
        if((num+1) % 3 == 0) {
            Sword *tmp2 = new Sword(atk * 2 / 10);
            swordCount++;
            weaponList.push_back(tmp2);
        }
        else if((num+1) % 3 == 1) {
            Bomb *tmp2 = new Bomb(atk * 4 /10);
            bombCount++;
            weaponList.push_back(tmp2);
        }
        else {
            Arrow *tmp2 = new Arrow(atk * 3 / 10);
            arrowCount++;
            weaponList.push_back(tmp2);
        }

    };
    Ninja():Creature(){}
    ~Ninja(){}
};


class Iceman:public Creature{//派生类，表示Iceman，count表示存在个数
public:
    Iceman(int hp, int atk, int num):Creature(hp, atk, num, 3){
        /*分配武器*/
        if(num % 3 == 0) {
            Sword *tmp = new Sword(atk * 2 / 10);
            swordCount++;
            weaponList.push_back(tmp);
        }
        else if(num % 3 == 1) {
            Bomb *tmp = new Bomb(atk * 4 /10);
            bombCount++;
            weaponList.push_back(tmp);
        }
        else {
            Arrow *tmp = new Arrow(atk * 3 / 10);
            arrowCount++;
            weaponList.push_back(tmp);
        }
    };
    Iceman():Creature(){}
    virtual void DoMoveCost(){
        int hpCost = HP / 10;
        HP -= hpCost;
    }
    ~Iceman(){}
};


class Lion:public Creature{//派生类，表示Lion，count表示存在个数
public:
    int loyalty;
    Lion(int hp, int atk, int num, int loyal):Creature(hp, atk, num, 4), loyalty(loyal){
        /*分配武器*/
        if(num % 3 == 0) {
            Sword *tmp = new Sword(atk * 2 / 10);
            swordCount++;
            weaponList.push_back(tmp);
        }
        else if(num % 3 == 1) {
            Bomb *tmp = new Bomb(atk * 4 /10);
            bombCount++;
            weaponList.push_back(tmp);
        }
        else {
            Arrow *tmp = new Arrow(atk * 3 / 10);
            arrowCount++;
            weaponList.push_back(tmp);
        }
    };
    Lion():Creature(){
        loyalty = -1;
    }
    virtual int GetLoyalty(){
        return loyalty;
    }
    virtual void DoMoveCost(){
        loyalty -= loyalDown;
    }
    ~Lion(){}
};


class Wolf:public Creature{//派生类，表示Wolf，count表示存在个数
public:
    Wolf(int hp, int atk, int num):Creature(hp, atk, num, 5){};
    Wolf():Creature(){}
    virtual void GrabWeapon(Creature *enemy, int n, int city){//n = 0表示是红魔军，n = 1表示是蓝魔军
        if (enemy->kind == 5){//对方也是wolf，不抢
            return;
        }
        int grabSwordCount = 0;
        int grabBombCount = 0;
        int grabArrowCount = 0;
        /*抢敌人编号最小的武器, 这里没用过的arrow先抢，注意只抢一种武器*/
        sort((enemy->weaponList).begin(), (enemy->weaponList).end(), cmp2);
        int GrabKind = enemy->weaponList[0]->kind;
        while(weaponList.size() < 10 && !enemy->weaponList.empty() && enemy->weaponList[0]->kind == GrabKind){//可以抢，就抢
            if(enemy->weaponList[0]->kind == 0){//抢夺sword
                grabSwordCount++;
                Sword *tmp = new Sword(ATK * 2 / 10);
                swordCount++;
                enemy->swordCount--;
                weaponList.push_back(tmp);
            } else if(enemy->weaponList[0]->kind == 1){//抢夺bomb
                grabBombCount++;
                Bomb *tmp = new Bomb(ATK * 4 /10);
                bombCount++;
                enemy->bombCount--;
                weaponList.push_back(tmp);
            } else if(enemy->weaponList[0]->kind == 2){//抢夺arrow, 注意这里是抢夺arrow，所以arrow的usetime要保持一致
                grabArrowCount++;
                Arrow *tmp = new Arrow(ATK * 3 / 10);
                arrowCount++;
                tmp->useTime = enemy->weaponList[0]->GetUseTime();
                enemy->arrowCount--;
                weaponList.push_back(tmp);
            }
            enemy->weaponList.erase(enemy->weaponList.begin());//敌人武器被抢夺，删去
        }
        /*打印信息*/
        if(grabSwordCount != 0){
            PrintTime();
            if(n == 0){
                cout << "red wolf " << number << " took " << grabSwordCount << " sword from blue " << PrintCreature[enemy->kind]
                << ' ' << enemy->number << " in city " << city << endl;
            } else{
                cout << "blue wolf " << number << " took " << grabSwordCount << " sword from red " << PrintCreature[enemy->kind]
                     << ' ' << enemy->number << " in city " << city << endl;
            }
        }
        if(grabBombCount != 0){
            PrintTime();
            if(n == 0){
                cout << "red wolf " << number << " took " << grabBombCount << " bomb from blue " << PrintCreature[enemy->kind]
                     << ' ' << enemy->number << " in city " << city << endl;
            } else{
                cout << "blue wolf " << number << " took " << grabBombCount << " bomb from red " << PrintCreature[enemy->kind]
                     << ' ' << enemy->number << " in city " << city << endl;
            }
        }
        if(grabArrowCount != 0){
            PrintTime();
            if(n == 0){
                cout << "red wolf " << number << " took " << grabArrowCount << " arrow from blue " << PrintCreature[enemy->kind]
                     << ' ' << enemy->number << " in city " << city << endl;
            } else{
                cout << "blue wolf " << number << " took " << grabArrowCount << " arrow from red " << PrintCreature[enemy->kind]
                     << ' ' << enemy->number << " in city " << city << endl;
            }
        }
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
    int city;//城市个数
    BattleField(int c):city(c){
        for(int i = 0; i <= cityCount+1; i++){
            blueCreature[i] = nullptr;
            redCreature[i] = nullptr;
        }
    }
    BattleField(){
        city = 0;
        for(int i = 0; i < 22; i++){
            blueCreature[i] = nullptr;
            redCreature[i] = nullptr;
        }
    }

};


/*司令部生成武士, 0表示红魔军（西）生成武士，1表示蓝魔君（东）生成武士，在每小时的第0分降生武士*/
void CreateWorrier(BattleField &bf, int n){
    int whichOne;//用来判断生成哪一种武士
    if(n == 0) {//红魔军
        if (!redIfCreateWarrior)//无法制造武士了
            bf.redCreature[0] = nullptr;
        whichOne = (redNumber - 1) % 5;
        string tmp = redList[whichOne];
        if (redLife >= creatureHP[tmp]) {//如果可以生成该武士
            PrintTime();
            cout << "red ";
            redLife -= creatureHP[tmp];
            if (tmp == "dragon") {
                cout << "dragon " << redNumber << " born" << endl;
                Dragon *dra = new Dragon(creatureHP["dragon"], creatureATK["dragon"], redNumber);
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
            redIfCreateWarrior = 0;
            bf.redCreature[0] = nullptr;
        }
    }
    else {//蓝魔军
        if (!blueIfCreateWarrior)//无法制造武士了
            bf.blueCreature[bf.city+1] = nullptr;
        whichOne = (blueNumber - 1) % 5;
        string tmp = blueList[whichOne];
        if (blueLife >= creatureHP[tmp]) {//如果可以生成该武士
            PrintTime();
            cout << "blue ";
            blueLife -= creatureHP[tmp];
            if (tmp == "dragon") {
                cout << "dragon " << blueNumber << " born" << endl;
                Dragon *dra = new Dragon(creatureHP["dragon"], creatureATK["dragon"], blueNumber);
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
            blueIfCreateWarrior = 0;
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
    /*红魔军进军*/
    for(int i = bf.city + 1; i > 0; i--) {
        bf.redCreature[i] = bf.redCreature[i-1];
        if(bf.redCreature[i] != nullptr) {
            bf.redCreature[i]->DoMoveCost();
            if (bf.redCreature[i]->IfDead()) {//iceman在march过程中死了
                delete bf.redCreature[i];
                bf.redCreature[i] = nullptr;
            }
        }
    }
    /*把司令部的warrior清除*/
    bf.redCreature[0] = nullptr;
    /*蓝魔军进军*/
    for(int i = 0; i < bf.city + 1; i++){
        bf.blueCreature[i] = bf.blueCreature[i+1];
        if(bf.blueCreature[i] != nullptr) {
            bf.blueCreature[i]->DoMoveCost();
            if (bf.blueCreature[i]->IfDead()) {//iceman在march过程中死了
                delete bf.blueCreature[i];
                bf.blueCreature[i] = nullptr;
            }
        }
    }
    /*把司令部的warrior清除*/
    bf.blueCreature[bf.city+1] = nullptr;
    /*输出结果*/
    if(bf.blueCreature[0] != nullptr){//红魔军司令部被占领
        PrintTime();
        cout << "blue " << PrintCreature[bf.blueCreature[0]->kind] << ' ' << bf.blueCreature[0]->number
        << " reached red headquarter with " << bf.blueCreature[0]->HP << " elements and force " << bf.blueCreature[0]->ATK << endl;
        PrintTime();
        cout << "red headquarter was taken" << endl;
        ifWin = 1;
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
    if(bf.redCreature[bf.city+1] != nullptr){//蓝魔军司令部被占领
        PrintTime();
        cout << "red " << PrintCreature[bf.redCreature[bf.city+1]->kind] << ' ' << bf.redCreature[bf.city+1]->number
             << " reached blue headquarter with " << bf.redCreature[bf.city+1]->HP << " elements and force " << bf.redCreature[bf.city+1]->ATK << endl;
        PrintTime();
        cout << "blue headquarter was taken" << endl;
        ifWin = 1;
    }
}


/*每小时的35分，wolf+敌人，wolf抢夺对方武器*/
void WolfGrabWeapon(BattleField &bf){
    for(int i = 0; i <= bf.city + 1; i++){
        /*对红魔军wolf判断*/
        if(bf.redCreature[i] != nullptr) {
            if (bf.redCreature[i]->kind == 5 && bf.blueCreature[i] != nullptr) {
                bf.redCreature[i]->GrabWeapon(bf.blueCreature[i], 0, i);
            }
        }
        /*对蓝魔军wolf判断*/
        if(bf.blueCreature[i] != nullptr) {
            if (bf.blueCreature[i]->kind == 5 && bf.redCreature[i] != nullptr) {
                bf.blueCreature[i]->GrabWeapon(bf.redCreature[i], 1, i);
            }
        }
    }
}


/*每小时的40分，开战*/
void Fight(BattleField &bf){
    for(int i = 0; i <= bf.city+1; i++){
        if(bf.blueCreature[i] != nullptr && bf.redCreature[i] != nullptr){//都有人，开战
            sort(bf.blueCreature[i]->weaponList.begin(), bf.blueCreature[i]->weaponList.end(), cmp1);
            sort(bf.redCreature[i]->weaponList.begin(), bf.redCreature[i]->weaponList.end(), cmp1);
            if(i % 2 == 0){//偶数号城市，蓝魔军先攻
                while(!bf.redCreature[i]->IfDead() && !bf.blueCreature[i]->IfDead() &&
                (!bf.redCreature[i]->weaponList.empty() || !bf.blueCreature[i]->weaponList.empty())){
                    bf.blueCreature[i]->Attack(bf.redCreature[i]);
                    /*当一方死了，战斗就结束了*/
                    if(bf.redCreature[i]->IfDead() || bf.blueCreature[i]->IfDead() ||
                       (bf.redCreature[i]->weaponList.empty() && bf.blueCreature[i]->weaponList.empty())){
                        break;
                    }
                    bf.redCreature[i]->Attack(bf.blueCreature[i]);
                    /*处理武器攻击力为零的情况*/
                    int flag = 1;
                    for(int check = 0; check < bf.redCreature[i]->weaponList.size(); check++){
                        if(bf.redCreature[i]->weaponList[check]->ATK != 0 || bf.redCreature[i]->weaponList[check]->kind != 0){
                            flag = 0;
                            break;
                        }
                    }
                    for(int check = 0; check < bf.blueCreature[i]->weaponList.size(); check++){
                        if(bf.blueCreature[i]->weaponList[check]->ATK != 0 || bf.blueCreature[i]->weaponList[check]->kind != 0){
                            flag = 0;
                            break;
                        }
                    }
                    if(flag){
                        break;
                    }
                }
            } else{//奇数号城市，红魔军先攻
                while(!bf.redCreature[i]->IfDead() && !bf.blueCreature[i]->IfDead() &&
                      (!bf.redCreature[i]->weaponList.empty() || !bf.blueCreature[i]->weaponList.empty())){
                    bf.redCreature[i]->Attack(bf.blueCreature[i]);
                    /*当一方死了，战斗就结束了*/
                    if(bf.redCreature[i]->IfDead() || bf.blueCreature[i]->IfDead() ||
                       (bf.redCreature[i]->weaponList.empty() && bf.blueCreature[i]->weaponList.empty())){
                        break;
                    }
                    bf.blueCreature[i]->Attack(bf.redCreature[i]);
                    /*处理武器攻击力为零,注意 只能是sword的情况！！*/
                    int flag = 1;
                    for(int check = 0; check < bf.redCreature[i]->weaponList.size(); check++){
                        if(bf.redCreature[i]->weaponList[check]->ATK != 0 || bf.redCreature[i]->weaponList[check]->kind != 0){
                            flag = 0;
                            break;
                        }
                    }
                    for(int check = 0; check < bf.blueCreature[i]->weaponList.size(); check++){
                        if(bf.blueCreature[i]->weaponList[check]->ATK != 0 || bf.blueCreature[i]->weaponList[check]->kind != 0){
                            flag = 0;
                            break;
                        }
                    }
                    if(flag){
                        break;
                    }
                }
            }
            /*战利品获取 + 打印信息*/
            if(bf.redCreature[i]->IfDead() && !bf.blueCreature[i]->IfDead()){//红死了，蓝活着
                PrintTime();
                cout << "blue " << PrintCreature[bf.blueCreature[i]->kind] << ' ' << bf.blueCreature[i]->number
                << " killed red " << PrintCreature[bf.redCreature[i]->kind] << ' ' << bf.redCreature[i]->number
                << " in city " << i << " remaining " << bf.blueCreature[i]->HP << " elements" << endl;
                bf.blueCreature[i]->GrabWeaponWin(bf.redCreature[i]);
                delete bf.redCreature[i];
                bf.redCreature[i] = nullptr;
                /*如果活的是dragon，会欢呼*/
                if(bf.blueCreature[i]->kind == 1){
                    PrintTime();
                    cout << "blue dragon " << bf.blueCreature[i]->number << " yelled in city " << i << endl;
                }
            } else if(!bf.redCreature[i]->IfDead() && bf.blueCreature[i]->IfDead()){//蓝死了，红活着
                PrintTime();
                cout << "red " << PrintCreature[bf.redCreature[i]->kind] << ' ' << bf.redCreature[i]->number
                << " killed blue " << PrintCreature[bf.blueCreature[i]->kind] << ' ' << bf.blueCreature[i]->number
                << " in city " << i << " remaining " << bf.redCreature[i]->HP << " elements" << endl;
                bf.redCreature[i]->GrabWeaponWin(bf.blueCreature[i]);
                delete bf.blueCreature[i];
                bf.blueCreature[i] = nullptr;
                /*如果活的是dragon，会欢呼*/
                if(bf.redCreature[i]->kind == 1){
                    PrintTime();
                    cout << "red dragon " << bf.redCreature[i]->number << " yelled in city " << i << endl;
                }
            } else if(bf.redCreature[i]->IfDead() && bf.blueCreature[i]->IfDead()){//都死了
                PrintTime();
                cout << "both red " << PrintCreature[bf.redCreature[i]->kind] << ' ' << bf.redCreature[i]->number
                << " and blue " << PrintCreature[bf.blueCreature[i]->kind] << ' ' << bf.blueCreature[i]->number
                << " died in city " << i << endl;
                delete bf.redCreature[i];
                delete bf.blueCreature[i];
                bf.redCreature[i] = nullptr;
                bf.blueCreature[i] = nullptr;
            } else {//都活着不必处理,只打印信息
                PrintTime();
                cout << "both red " << PrintCreature[bf.redCreature[i]->kind] << ' ' << bf.redCreature[i]->number
                << " and blue " << PrintCreature[bf.blueCreature[i]->kind] << ' ' << bf.blueCreature[i]->number
                << " were alive in city " << i << endl;
                /*红：如果活的是dragon，会欢呼*/
                if(bf.redCreature[i]->kind == 1){
                    PrintTime();
                    cout << "red dragon " << bf.redCreature[i]->number << " yelled in city " << i << endl;
                }
                /*蓝：如果活的是dragon，会欢呼*/
                if(bf.blueCreature[i]->kind == 1){
                    PrintTime();
                    cout << "blue dragon " << bf.blueCreature[i]->number << " yelled in city " << i << endl;
                }
            }
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
    /*显然，在经过march后，如果还能经历到这一步，不会出现有武士在自家司令部或对方司令部的情况*/
    for(int i = 1; i <= bf.city; i++){
        /*先输出红方，再输出蓝方*/
        if(bf.redCreature[i] != nullptr) {
            PrintTime();
            cout << "red " << PrintCreature[bf.redCreature[i]->kind] << ' ' << bf.redCreature[i]->number
            << " has " <<  bf.redCreature[i]->swordCount << " sword " << bf.redCreature[i]->bombCount << " bomb "
            << bf.redCreature[i]->arrowCount << " arrow and " << bf.redCreature[i]->HP << " elements" << endl;
        }
        if(bf.blueCreature[i] != nullptr){
            PrintTime();
            cout << "blue " << PrintCreature[bf.blueCreature[i]->kind] << ' ' << bf.blueCreature[i]->number
            << " has " <<  bf.blueCreature[i]->swordCount << " sword " << bf.blueCreature[i]->bombCount << " bomb "
            << bf.blueCreature[i]->arrowCount << " arrow and " << bf.blueCreature[i]->HP << " elements" << endl;
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
        cin >> M >> cityCount >> loyalDown >> totalTime;
        cin >> dragonHP >> ninjaHP >> icemanHP >> lionHP >> wolfHP;
        cin >> dragonATK >> ninjaATK >> icemanATK >> lionATK >> wolfATK;
        /*每组样例初始化数据*/
        blueLife = redLife = M;
        blueIfCreateWarrior = redIfCreateWarrior = 1;
        timeCountHour = timeCountMinute = 0;
        blueNumber = redNumber = 1;
        ifWin = 0;
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
            if(ifWin){//如果司令部被占领，就结束了
                break;
            }
            if(timeCountMinute == 0){//武士降生
                CreateWorrier(battlefield, 0);
                CreateWorrier(battlefield, 1);
            } else if(timeCountMinute == 5){//lion逃跑
                IfLionRun(battlefield);
            } else if(timeCountMinute == 10){//进军
                March(battlefield);
            } else if(timeCountMinute == 35){//狼人偷武器
                WolfGrabWeapon(battlefield);
            } else if(timeCountMinute == 40){//开战
                Fight(battlefield);
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