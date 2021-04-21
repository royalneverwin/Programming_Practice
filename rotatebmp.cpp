/*王新昊
 * 1900011102
 * rotatebmp
 */
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#pragma pack(1)

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned int LONG;


const int MAX = 3000;


typedef struct tagBITMAPFILEHEADER//BMP文件头
{
    WORD bfType; // 位图文件的类型，必须为“BM”
    DWORD bfSize; // 位图文件的大小，以字节为单位
    WORD bfReserved1; // 位图文件保留字，必须为0
    WORD bfReserved2; // 位图文件保留字，必须为0
    DWORD bfOffBits; // 位图数据的起始位置，以相对于位图文件头的偏移量表示，以字节为单位
} BITMAPFILEHEADER;//该结构占据14个字节


typedef struct tagBITMAPINFOHEADER{//BMP位图信息头
    DWORD biSize; // 本结构所占用字节数
    LONG biWidth; // 位图的宽度，以像素为单位
    LONG biHeight; // 位图的高度，以像素为单位
    WORD biPlanes; // 目标设备的平面数不清，必须为1
    WORD biBitCount;// 每个像素所需的位数，必须是1(双色), 4(16色)，8(256色)或24(真彩色)之一
    DWORD biCompression; // 位图压缩类型，必须是 0(不压缩),1(BI_RLE8压缩类型)或2(BI_RLE4压缩类型)之一
    DWORD biSizeImage; // 位图的大小，以字节为单位
    LONG biXPelsPerMeter; // 位图水平分辨率，每米像素数
    LONG biYPelsPerMeter; // 位图垂直分辨率，每米像素数
    DWORD biClrUsed;// 位图实际使用的颜色表中的颜色数
    DWORD biClrImportant;// 位图显示过程中重要的颜色数
} BITMAPINFOHEADER; //该结构占据40个字节


typedef struct tagRGB24 {//32字节
    BYTE rgbBlue;// 蓝色的亮度(值范围为0-255)
    BYTE rgbGreen; // 绿色的亮度(值范围为0-255)
    BYTE rgbRed; // 红色的亮度(值范围为0-255)
} RGB24;


typedef struct tagRGB32 {//32字节
    BYTE rgbBlue;// 蓝色的亮度(值范围为0-255)
    BYTE rgbGreen; // 绿色的亮度(值范围为0-255)
    BYTE rgbRed; // 红色的亮度(值范围为0-255)
    BYTE rgbReserved;// 保留，必须为0
} RGB32;



BITMAPFILEHEADER bmpFileHeader;
BITMAPINFOHEADER bmpInfoHeader;
RGB24 bmp24[MAX][MAX];
RGB32 bmp32[MAX][MAX];


int main(int argc, char *argv[]){//命令行输入有两个文件名, 将第一个文件的照片顺时针旋转90度放到第二个文件中
    ifstream fin(argv[1],ios::in|ios::binary);
    ofstream fout(argv[2], ios::out | ios::binary);
    int count = 0;
    int ifInterval = 0;//在两个Header和数据之间可能还有一些无关数据, 要都记录并且平移
    char *interval;
    int intervalCnt;
    int width;
    int height;
    if(!fin.is_open()){//若打开文件错误, 则输出错误
        cerr << "Error in opening files" << endl;
        exit(1);
    }
    fin.read((char *)&bmpFileHeader, sizeof(bmpFileHeader));//read的首项必须是char *
    fin.read((char *)&bmpInfoHeader, sizeof(bmpInfoHeader));
    count = count + sizeof(bmpFileHeader) + sizeof(bmpInfoHeader);
    width = bmpInfoHeader.biWidth;
    height = bmpInfoHeader.biHeight;
    if(width > MAX || height > MAX){
        cerr << "too big" << endl;
        exit(2);
    }
    if(bmpInfoHeader.biBitCount == 24){//如果是24位
        intervalCnt = bmpFileHeader.bfOffBits - count;
        if(intervalCnt != 0)
            ifInterval = 1;
        if(ifInterval){
            interval = new char[intervalCnt];
            fin.read(interval, intervalCnt);
        }

        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                fin.read((char *)&bmp24[j][i], sizeof(bmp24[j][i]));//第i行第j列数据实际上是第n-i行第j列数据, 翻转后变为第j行第i列, 存放在第n-j行第i列
            }
            /*计算每行要填充的字节数（每行必须是4的倍数）, 这里是为了让fin到下一行, 所以读取完丢掉就行*/
            //int makeUp = 4 - (height * 3) % 4;
            int makeUp = (width * 3 + 3) / 4 * 4 - width * 3;
            BYTE tmp;
            for(int j = 0; j < makeUp; j++){
                fin.read((char *)&tmp, sizeof(tmp));
            }
        }
        /*rotate 90度*/
        bmpInfoHeader.biWidth = height;
        bmpInfoHeader.biHeight=  width;
        fout.write((char *)&bmpFileHeader, sizeof(bmpFileHeader));
        fout.write((char *)&bmpInfoHeader, sizeof(bmpInfoHeader));
        if(ifInterval){
            fout.write(interval, intervalCnt);
            delete []interval;
        }
        /*注意上面读图像数据区的注释, bmp24[i][j]存放在第n-i行第j列*/
        for(int i = width - 1; i >= 0; i--){
            for(int j = 0; j < height; j++){
                fout.write((char *)&bmp24[i][j], sizeof(bmp24[i][j]));
            }
            /*注意这里也要填充字节确保每行字节是4的倍数*/
            //int makeUpNew = 4 - (width * 3) % 4;
            int makeUpNew = (height * 3 + 3) / 4 * 4 - height * 3;
            BYTE tmp = 0;
            for(int j = 0; j < makeUpNew; j++){
                fout.write((char *)&tmp, sizeof(tmp));
            }
        }
    } else if(bmpInfoHeader.biBitCount == 32){//如果是32位
        intervalCnt = bmpFileHeader.bfOffBits - count;
        if(intervalCnt != 0)
            ifInterval = 1;
        if(ifInterval){
            interval = new char[intervalCnt];
            fin.read(interval, intervalCnt);
        }

        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                fin.read((char *)&bmp32[j][i], sizeof(bmp32[j][i]));//第i行第j列数据实际上是第n-i行第j列数据, 翻转后变为第j行第i列, 存放在第n-j行第i列
            }
            /*32是4的倍数, 所以后端不可能补0*/
        }
        /*rotate 90度*/
        bmpInfoHeader.biWidth = height;
        bmpInfoHeader.biHeight=  width;
        fout.write((char *)&bmpFileHeader, sizeof(bmpFileHeader));
        fout.write((char *)&bmpInfoHeader, sizeof(bmpInfoHeader));
        if(ifInterval){
            cout << intervalCnt << endl;
            fout.write(interval, intervalCnt);
            delete []interval;
        }
        /*注意上面读图像数据区的注释, bmp24[i][j]存放在第n-i行第j列*/
        for(int i = width - 1; i >= 0; i--){
            for(int j = 0; j < height; j++){
                fout.write((char *)&bmp32[i][j], sizeof(bmp32[i][j]));
            }
            /*32是4的倍数, 所以后端不可能补0*/
        }
    } else{
        cerr << "not 24/32 " << endl;
        exit(3);
    }
    fin.close();
    fout.close();
    return 0;
}