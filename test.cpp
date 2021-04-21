#include <cstdio>
int main(){
    int a, b, c, m, n = 1;
    a = 1;
    b = 2;
    c = 3;
    m = (a++ > --b) || !--a && (a == 0) && (b=1) && (c=4) || (n=5);
    printf("%d %d %d %d %d\n", a, b, c, m, n);
  return 0;
}