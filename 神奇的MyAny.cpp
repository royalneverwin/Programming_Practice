#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
using namespace std;
class MyClass {
public:
    int n;
    MyClass(int m):n(m) { }
    void f() { cout << n << " func." << endl; }
};
// 在此处补充你的代码:抽象基类+模版派生 = 编译时的多态
class MyAny{
public:

    class BaseValue{
    public:
        virtual const type_info& GetValue(){
            return typeid(int);
        }
        /*在用MyAny给别人赋值时别人不知道你这是什么类型，所以应该在你这里就确定类型并给他*/
        virtual BaseValue *GetData() = 0;
        virtual ~BaseValue(){}
    };

    template <class T>
    class MyValue:public BaseValue{
    public:
        T value;
        MyValue(const T& n):value(n){}
        virtual const type_info& GetValue(){
            return typeid(value);
        }
        BaseValue *GetData(){/*注意这里的GetData！是点睛之笔，因为MyAny是不知道他的MyValue存的是什么类型的值的，所以两个MyAny用=赋值时被赋值的MyAny的content很难创建，只能让赋值的MyAny先创建好再给他*/
            return new MyValue<T>(value);
        }
        ~MyValue(){}
    };

    BaseValue *content;//用指针才能实现多态

    template <class T>
    MyAny(const T& n){//构造函数
        content = new MyValue<T>{n};
    }

    template <class T>
    MyAny(const MyValue<T> &other){//构造函数
        content = new MyValue<T>(other.value);
    }

    MyAny(const MyAny& other){//复制构造函数
        content = other.content->GetData();
    }

    ~MyAny(){
        if(content != nullptr){
            delete content;
        }
    }

    template <class T>
    void operator = (const T& n){
        if(content != nullptr){
            delete content;
        }
        content = new MyValue<T>{n};
    }

    void operator = (const MyAny &other){//重载=，防止两个MyAny赋值时直接复制content的值而不是再new一个
        if(content != nullptr)
            delete content;
        content = other.content->GetData();
    }
};

template <class T>
T MyAny_cast(const MyAny& a){
    return (dynamic_cast<MyAny::MyValue<T> *> (a.content))->value;
}

template <class T>
T* MyAny_cast(const MyAny* a){
    T tmp{1};
    if(typeid(tmp) == a->content->GetValue()){
        return &((dynamic_cast<MyAny::MyValue<T> *> (a->content))->value);
    } else{
        return nullptr;
    }
}
int main()
{
    while(true) {
        int n;
        string s;
        cin >>  n >> s;
        if ( n == 0)
            break;
        MyAny a = n;
        cout << MyAny_cast<int>(a) << endl;
        a = s;
        cout << MyAny_cast<string>(a) << endl;
        a = MyClass(n+1);
        MyAny b = n + 2;
        MyAny * p = new MyAny(MyClass(n+3));
        MyAny c = MyClass(n+4);
        c = * p;
        b = * p;
        delete p;
        MyAny d = b;
        MyAny_cast<MyClass>(&a)->f();
        MyAny_cast<MyClass>(&b)->f();
        MyAny_cast<MyClass>(&c)->f();
        MyAny_cast<MyClass>(&d)->f();
        c = s + "OK";
        cout << MyAny_cast<string>(c) << endl;
        int * pi = MyAny_cast<int> ( & c);
        if( pi == NULL)
            cout << "not a int" << endl;
        else
            cout << "the int is " << * pi << endl;
        string * ps = MyAny_cast<string> ( & c);
        if( ps == NULL)
            cout << "not a string" << endl;
        else
            cout << "the string is " << * ps << endl;
    }
}