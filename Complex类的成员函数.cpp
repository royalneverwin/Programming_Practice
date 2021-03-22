#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }

    Complex & operator = (const char *s){
        char sCopy[10];
        char *start = sCopy;
        strcpy(sCopy, s);
        char *tmp = strchr(start, '+');
        *tmp = '\0';
        r = atof(start);
        start = tmp + 1;
        tmp = strchr(start, 'i');
        *tmp = '\0';
        i = atof(start);
        return *this;
    }
};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}