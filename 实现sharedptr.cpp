#include <iostream>

using namespace std;
//#define MySharedPtr shared_ptr

template <class T>
struct MySharedPtr
{
// 在此处补充你的代码
public:
    T *ptr;
    int *cnt;//记录共享同一指针的shared_ptr个数
    MySharedPtr(T *p):ptr(p){//构造函数
        cnt = new int(1);
    }
    MySharedPtr(){
        ptr = nullptr;
        cnt = nullptr;
    }
    MySharedPtr(const MySharedPtr<T>& p){//复制构造函数
        ptr = p.ptr;
        cnt = p.cnt;
        (*cnt)++;
    }

    T* operator ->(){//重载->运算符
        return ptr;
    }

    T *get(){//实现get函数
        return ptr;
    }

    T& operator *(){//重载*运算符, 注意这里一定要返回引用！否则会调用复制构造函数构造A构造临时对象, 并且在最后调用析构函数析构临时对象, 所以会多一个2 destructor
        return *ptr;
    }

    void reset(){//实现reset第一形式
        if(cnt != nullptr && *cnt == 1){
            delete cnt;
            delete ptr;
        } else if(cnt != nullptr)
            (*cnt)--;
        cnt = nullptr;
        ptr = nullptr;
    }

    void reset(T *p){//实现reset第二形式
        if(cnt != nullptr && *cnt == 1){
            delete cnt;
            delete ptr;
        } else if(cnt != nullptr)
            (*cnt)--;
        ptr = p;
        cnt = new int(1);
    }

    bool operator !() const{//重载！运算符
        return !ptr;
    }

    MySharedPtr<T>& operator = (MySharedPtr<T>& other){//重载=运算符
        if(other.ptr == ptr){
            return *this;
        } else{
            if(cnt != nullptr && *cnt == 1){
                delete cnt;
                delete ptr;
            } else if(cnt != nullptr)
                (*cnt)--;
            ptr = other.ptr;
            cnt = other.cnt;
            (*cnt)++;
            return *this;
        }
    }

    ~MySharedPtr(){//析构函数，这里注意当cnt的值为1的时候，再delete指针
        if(cnt != nullptr && *cnt == 1){
            delete cnt;
            delete ptr;
        } else if(cnt != nullptr){
            (*cnt)--;
        }
    }
};



struct A   {
    int n;
    A(int v = 0):n(v){ }
    ~A() { cout << n << " destructor" << endl; }
};
int main()
{
    MySharedPtr<A> sp1(new A(2));
    MySharedPtr<A> sp2(sp1);
    cout << "1)" << sp1->n  << "," << sp2->n << endl;
    MySharedPtr<A> sp3;
    A * p = sp1.get();
    cout << "2)" << p->n << endl;
    sp3 = sp1;
    cout << "3)" << (*sp3).n << endl;
    sp1.reset();
    if( !sp1 )
        cout << "4)sp1 is null" << endl; //会输出
    A * q = new A(3);
    sp1.reset(q); //
    cout << "5)" << sp1->n << endl;
    MySharedPtr<A> sp4(sp1);
    MySharedPtr<A> sp5;
    sp5.reset(new A(8));
    sp1.reset();
    cout << "before end main" <<endl;
    sp4.reset();
    cout << "end main" << endl;
    return 0; //程序结束，会delete 掉A(2)
}