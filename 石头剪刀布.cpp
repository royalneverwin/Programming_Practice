#include <iostream>
using namespace std;


int a[101];
int b[101];


int main(){
    int n, na, nb;
    cin >> n >> na >> nb;
    for(int i = 0; i < na; i++){
        cin >> a[i];
    }
    for(int i = 0; i < nb; i++){
        cin >> b[i];
    }
    int cnta = 0, cntb = 0;
    for(int i = 0; i < n; i++){
        if(a[i % na] == b[i % nb]){
            continue;
        }
        /*a输*/
        if(a[i % na] == 0 && b[i % nb] == 5 || a[i % na] == 2 && b[i % nb] == 0 || a[i % na] == 5 && b[i % nb] == 2){
            cntb++;
        }
        /*b输*/
        else if(a[i % na] == 0 && b[i % nb] == 2 || a[i % na] == 2 && b[i % nb] == 5 || a[i % na] == 5 && b[i % nb] == 0){
            cnta++;
        }
    }
    if(cnta > cntb){
        cout << 'A' << endl;
    } else if(cnta < cntb){
        cout << 'B' << endl;
    } else{
        cout << "draw" << endl;
    }
    return 0;
}