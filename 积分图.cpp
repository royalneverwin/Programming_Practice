#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class IntegralImage{
public:
    int ** image;
    int H;
    int W;
    int row;
    IntegralImage(int h, int w):H(h), W(w){
        row = 0;
        image = new int*[h];
        for(int i = 0; i < h; i++){
            image[i] = new int[w];
        }
    }
    void operator()(const int *ima){
        for(int i = 0; i < W; i++){
            if(i > 0 && row > 0)
                image[row][i] = image[row][i-1] + image[row-1][i] - image[row-1][i-1] + ima[i];
            else if(row > 0)
                image[row][i] = image[row-1][i] + ima[i];
            else if(i > 0)
                image[row][i] = image[row][i-1] + ima[i];
            else
                image[row][i] = ima[i];
        }
        row++;
    }
    int *operator[](int idx) const{
        return image[idx];
    }
};
int main(){
    int H, W;
    cin >> H >> W;
    int ** image = new int*[H];
    for(int i=0;i<H;++i){
        image[i]=new int[W];
    }
    for(int i=0;i<H;++i)
        for(int j=0;j<W;++j)
            cin >> image[i][j];
    IntegralImage it(H,W);
    for_each(image, image+H, it);
    for(int i=0;i<H;++i){
        for(int j=0;j<W;++j)
            cout<<it[i][j]<<" ";
        cout<<endl;
    }

}