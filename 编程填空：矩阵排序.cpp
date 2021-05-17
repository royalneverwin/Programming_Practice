#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Mat {
    int h, w;
public:
    Mat(int height, int width) : h(height), w(width)
// 在此处补充你的代码
    {}
    static int line;
    int localLine;
    int *matrix;
    int Geth() const{
        return h;
    }
    int Getw() const{
        return w;
    }
    friend istream& operator >> (istream& is, Mat& m){
        line++;
        m.localLine = line;
        m.matrix = new int[m.Geth() * m.Getw()];
        for(int i = 0; i < m.Geth() * m.Getw(); i++){
            is >> m.matrix[i];
        }
        return is;
    }
    friend ostream& operator << (ostream& os, Mat& m){
        for(int i = 0; i < m.Geth(); i++){
            for(int j = 0; j < m.Getw(); j++){
                os << m.matrix[i * m.Getw() + j] << ' ';
            }
            cout << endl;
        }
        return os;
    }
    bool operator < (const Mat& m) const{
        return (h*w != m.Geth() * m.Getw()) ? h*w < m.Geth() * m.Getw() : localLine > m.localLine;
    }
};

int Mat::line = 0;


bool comparator_1(const Mat& m1, const Mat& m2){
    int sum1 = 0, sum2 = 0;
    for(int i = 0; i < m1.Getw() * m1.Geth(); i++){
        sum1 += m1.matrix[i];
    }
    for(int i = 0; i < m2.Getw() * m2.Geth(); i++){
        sum2 += m2.matrix[i];
    }
    return (sum1 != sum2) ? sum1 < sum2 : m1.localLine > m2.localLine;
};

class comparator_2{
public:
    bool operator ()(const Mat& m1, const Mat& m2){
        return m1.localLine < m2.localLine;
    }
};

    int main()
    {
        vector<Mat> m;
        m.push_back(Mat(2,2));
        m.push_back(Mat(3,4));
        m.push_back(Mat(2,2));
        cin >> m[0] >> m[1] >> m[2];
        sort(m.begin(),m.end());
        cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
        cout<<"*************"<<endl;
        sort(m.begin(),m.end(),comparator_1);
        cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
        cout<<"*************"<<endl;
        sort(m.begin(),m.end(),comparator_2());
        cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
        return 0;
    }