#include<stdio.h>
#include<stdlib.h>
#include <unordered_map>
#include <algorithm>
#define MAXNUM ~(1<<31)
using namespace std;
unordered_map<int, int> f;


int main()
{
    int n;
    int score,square;
    int i,j;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        f.clear();
        for(j=0; j<MAXNUM; j++){
            scanf("%d",&score);
            scanf("%d",&square);
            if(square >= 0){
                f[square]+=score;
            }
            else{
                break;
            }
        }
        for(j=0; j<MAXNUM; j++){
            scanf("%d",&score);
            scanf("%d",&square);
            if(square>=0){
                f[square]+=score;
            }
            else{
                break;
            }
        }
        int flag = 0;

        for(auto& i: f) {
            if(i.second == 0) continue;
            if(flag != 0)
                printf(" ");
            flag++;
            printf("[ %d %d ]",i.second, i.first);
        }

		for(j=MAXNUM-1;j>-1;j--){
			if(f.count(j) != 0 && f[j] != 0){
			    if(flag != 0)
			        printf(" ");
			    flag++;
				printf("[ %d %d ]",f[j],j);
			}
		}
		printf("\n");
    }
    return 0;
}
