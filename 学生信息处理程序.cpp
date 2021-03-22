#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
    char name[21];
    int age;
    char stu_number[20];
    double av_grade;
    int fir_grade;
    int sec_grade;
    int th_grade;
    int for_grade;
public:
    void input(){
        char info[200];
        char *s = info;
        cin.getline(info, 200);
        //得到name
        char *tmp = strchr(s, ',');
        *tmp = '\0';
        tmp += 1;
        strcpy(name, s);
        //得到age
        s = tmp;
        tmp = strchr(s, ',');
        *tmp = '\0';
        tmp += 1;
        age = atoi(s);
        //得到stu_number
        s = tmp;
        tmp = strchr(s, ',');
        *tmp = '\0';
        tmp += 1;
        strcpy(stu_number, s);
        //得到fir_grade
        s = tmp;
        tmp = strchr(s, ',');
        *tmp = '\0';
        tmp += 1;
        fir_grade = atoi(s);
        //得到sec_grade
        s = tmp;
        tmp = strchr(s, ',');
        *tmp = '\0';
        tmp += 1;
        sec_grade = atoi(s);
        //得到th_grade
        s = tmp;
        tmp = strchr(s, ',');
        *tmp = '\0';
        tmp += 1;
        th_grade = atoi(s);
        //得到for_grade
        s = tmp;
        for_grade = atoi(s);
    }
    void calculate(){
        av_grade = ((double)(fir_grade + sec_grade + th_grade + for_grade))/4;
    }
    void output(){
        cout << name << ',' << age << ',' << stu_number << ',' << av_grade << endl;
    }
};

int main() {
    Student student;        // 定义类的对象
    student.input();        // 输入数据
    student.calculate();    // 计算平均成绩
    student.output();       // 输出数据
}