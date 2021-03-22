/*老同学李明开了一家小型客栈还起了一个好听的名字“君悦”，2019年过去了，他想统计一下客栈的入住情况，分析问题，改善经营。他知道你一直是学霸，所以来找你帮忙统计一下。已知客栈已经有了每名客人的进店、离店时间，现在希望你帮忙统计一下客栈每个月所有人的入住天数之和。
备注：客人的进店、离店时间都是2019年内的日期，且进店时间早于或等于离店时间, 如果进店时间早于离店时间，离店当天不算住店。比如5 1 5 4 表示这名客人5月1日进店，5月4日离店，5月4日当日不算住店，实际入住算3天。如果进店时间等于离店时间，离店当天算住店，比如5 1 5 1 表示这名客人5月1日进店，5月1日离店，5月1日当日算住店，实际入住算1天。

输入
输入第一行为客人的数量n；(n不超过200)
之后n行为n名客人的进店时间和离店时间，每行前两个数为进店时间的月份和日期，后两个数是离店时间的月份和日期，年份均为2019年。
输出
输出包括12行,每行为月份和客栈每个月所有人的入住天数之和，以空格分隔。*/
#include<stdio.h>
int f1(int p,int q,int r,int s){
    int day = 0;
    if(p>1){
        day = 0;
    }
    else{
        if(r>1){
            day=32-q;
        }
        else{
            day=s-q;
        }
    }
    if((p==r)&&(q==s)&&(p==1)) day+=1;
    return day;
}
int f2(int p,int q,int r,int s){
    int day = 0;
    if(p>2){
        day=0;
    }
    else if(p<2){
        if(r>2){
            day=28;
        }
        else if(r<2){
            day=0;
        }
        else{
            day=s-1;
        }
    }
    else{
        if(r>2){
            day=29-q;
        }
        else{
            day=s-q;
        }
    }
    if((p==r)&&(q==s)&&(p==2)) day+=1;
    return day;
}
int f3(int p,int q,int r,int s){
    int day = 0;
    if(p>3){
        day=0;
    }
    else if(p<3){
        if(r>3){
            day=31;
        }
        else if(r<3){
            day=0;
        }
        else{
            day=s-1;
        }
    }
    else{
        if(r>3){
            day=32-q;
        }
        else{
            day=s-q;
        }
    }
    if((p==r)&&(q==s)&&(p==3)) day+=1;
    return day;
}
int f4(int p,int q,int r,int s){
    int day = 0;
    if(p>4){
        day=0;
    }
    else if(p<4){
        if(r>4){
            day=30;
        }
        else if(r<4){
            day=0;
        }
        else{
            day=s-1;
        }
    }
    else{
        if(r>4){
            day=31-q;
        }
        else{
            day=s-q;
        }
    }
    if((p==r)&&(q==s)&&(p==4))day+=1;
    return day;
}
int f5(int p,int q,int r,int s){
    int day = 0;
    if(p>5){
        day=0;
    }
    else if(p<5){
        if(r>5){
            day=31;
        }
        else if(r<5){
            day=0;
        }
        else{
            day=s-1;
        }
    }
    else{
        if(r>5){
            day=32-q;
        }
        else{
            day=s-q;
        }
    }
    if((p==r)&&(q==s)&&(p==5))day+=1;
    return day;
}
int f6(int p,int q,int r,int s){
    int day = 0;
    if(p>6){
        day=0;
    }
    else if(p<6){
        if(r>6){
            day=30;
        }
        else if(r<6){
            day=0;
        }
        else{
            day=s-1;
        }
    }
    else{
        if(r>6){
            day=31-q;
        }
        else{
            day=s-q;
        }
    }
    if((p==r)&&(q==s)&&(p==6))day+=1;
    return day;
}
int f7(int p,int q,int r,int s){
    int day = 0;
    if(p>7){
        day=0;
    }
    else if(p<7){
        if(r>7){
            day=31;
        }
        else if(r<7){
            day=0;
        }
        else{
            day=s-1;
        }
    }
    else{
        if(r>7){
            day=32-q;
        }
        else{
            day=s-q;
        }
    }
    if((p==r)&&(q==s)&&(p==7))day+=1;
    return day;
}
int f8(int p,int q,int r,int s){
    int day = 0;
    if(p>8){
        day=0;
    }
    else if(p<8){
        if(r>8){
            day=31;
        }
        else if(r<8){
            day=0;
        }
        else{
            day=s-1;
        }
    }
    else{
        if(r>8){
            day=32-q;
        }
        else{
            day=-q;
        }
    }
    if((p==r)&&(q==s)&&(p==8))day+=1;
    return day;
}
int f9(int p,int q,int r,int s){
    int day = 0;
    if(p>9){
        day=0;
    }
    else if(p<9){
        if(r>9){
            day=30;
        }
        else if(r<9){
            day=0;
        }
        else{
            day=s-1;
        }
    }
    else{
        if(r>9){
            day=31-q;
        }
        else{
            day=s-q;
        }
    }
    if((p==r)&&(q==s)&&(p==9))day+=1;
    return day;
}
int f10(int p,int q,int r,int s){
    int day = 0;
    if(p>10){
        day=0;
    }
    else if(p<10){
        if(r>10){
            day=31;
        }
        else if(r<10){
            day=0;
        }
        else{
            day=s-1;
        }
    }
    else{
        if(r>10){//这个地方我也抄错了
            day=32-q;
        }
        else{
            day=s-q;
        }
    }
    if((p==r)&&(q==s)&&(p==10))day+=1;
    return day;
}
int f11(int p,int q,int r,int s){
    int day = 0;
    if(p>11){
        day=0;
    }
    else if(p<11){//这个地方我曾经抄错了，结果死活查不出来
        if(r>11){
            day=30;
        }
        else if(r<11){
            day=0;
        }
        else{
            day=s-1;
        }
    }
    else{
        if(r>11){
            day=31-q;
        }
        else{
            day=s-q;
        }
    }
    if((p==r)&&(q==s)&&(p==11))day+=1;
    return day;
}
int f12(int p,int q,int r,int s){
    int day = 0;
    if(p>12){
        day=0;
    }
    else if(p<12){
        if(r>12){
            day=31;
        }
        else if(r<12){
            day=0;
        }
        else{
            day=s-1;
        }
    }
    else{
        if(r>12){
            day=32-q;
        }
        else{
            day=s-q;
        }
    }
    if((p==r)&&(q==s)&&(p==12))day+=1;
    return day;
}
int main()
{
    int n;
    int a[500][4];
    int a1=0,a2=0,a3=0,a4=0,a5=0,a6=0,a7=0,a8=0,a9=0,a10=0,a11=0,a12=0;
    scanf("%d",&n);
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<4;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(i=0;i<n;i++){
        a1+=f1(a[i][0],a[i][1],a[i][2],a[i][3]);
        a2+=f2(a[i][0],a[i][1],a[i][2],a[i][3]);
        a3+=f3(a[i][0],a[i][1],a[i][2],a[i][3]);
        a4+=f4(a[i][0],a[i][1],a[i][2],a[i][3]);
        a5+=f5(a[i][0],a[i][1],a[i][2],a[i][3]);
        a6+=f6(a[i][0],a[i][1],a[i][2],a[i][3]);
        a7+=f7(a[i][0],a[i][1],a[i][2],a[i][3]);
        a8+=f8(a[i][0],a[i][1],a[i][2],a[i][3]);
        a9+=f9(a[i][0],a[i][1],a[i][2],a[i][3]);
        a10+=f10(a[i][0],a[i][1],a[i][2],a[i][3]);
        a11+=f11(a[i][0],a[i][1],a[i][2],a[i][3]);
        a12+=f12(a[i][0],a[i][1],a[i][2],a[i][3]);
    }
    printf("1 %d\n2 %d\n3 %d\n4 %d\n5 %d\n6 %d\n7 %d\n8 %d\n9 %d\n10 %d\n11 %d\n12 %d",a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);
    return 0;
}



/*
#include<stdio.h>

int main(){
    int num;
    scanf("%d",&num);
    int ruzhu[4][num];
    for(int i=0;i<num;i++){
        for(int j=0;j<4;++j){
            scanf("%d",&ruzhu[j][i]);
        }
    }
    int yue[13];
    for(int i=0;i<13;++i){
        yue[i]=0;
    }
    int sj[13];
    sj[1]=sj[3]=sj[5]=sj[7]=sj[8]=sj[10]=sj[12]=31;
    sj[4]=sj[6]=sj[9]=sj[11]=30;
    sj[2]=28;
    for(int i=0;i<num;i++){
        if(ruzhu[0][i]==ruzhu[2][i]){
            if(ruzhu[1][i]==ruzhu[3][i]){
                ++yue[ruzhu[0][i]];
            }else{
                yue[ruzhu[0][i]]+=ruzhu[3][i]-ruzhu[1][i];
            }
        }else{
            yue[ruzhu[0][i]]+=sj[ruzhu[0][i]]-ruzhu[1][i]+1;
            yue[ruzhu[2][i]]+=ruzhu[3][i]-1;
        }
    }
    for(int i=1;i<12;i++){
        printf("%d %d\n",i,yue[i]);
    }
    printf("%d %d\n",12,yue[12]);
    return 0;
}
 */