#include<iostream>
#include<time.h>
#include<graphics.h>        //圖形庫標頭檔案 easyx
#include <conio.h>          //呼叫_getch函式
using namespace std;
HWND hwnd;
int sum = 0;//用於表示目前已經點開的格子數
//宣告函式
void drawmap(int map[][12], IMAGE* img);
int mousedown(int map[][12]);
void swap(int map[][12], int mi, int mj);
//初始化遊戲

//繪製地圖

//滑鼠點選

//遞迴函式

int main()
{
    while (1)
    {
        startgame();
        if (MessageBox(hwnd, "再來一次", "結束遊戲", MB_YESNO)==IDNO)
            break;
    }
    //_getch();                //防止閃屏
    closegraph();
    return 0;
}

void drawmap(int map[][12],IMAGE *img) //繪製地圖 
{
    int i, j;
    for (i = 1; i <= 10; i++)
    {
        for (j = 0; j <= 10; j++)
        {
            int x = 50 * (i - 1);//得到位置
            int y = 50 * (j - 1);
            if (map[i][j]>25)
            {
                putimage(x, y, &img[9]);//標記flag
            }
            else
            {
                switch (map[i][j])
                {
                case 9:
                    putimage(x, y, &img[11]);//輸出圖片雷
                    break;
                case 10:
                    putimage(x, y, &img[0]);//0
                    break;
                case 11:
                    putimage(x, y, &img[1]);//1
                    break;
                case 12:
                    putimage(x, y, &img[2]);//2
                    break;
                case 13:
                    putimage(x, y, &img[3]);//3
                    break;
                case 14:
                    putimage(x, y, &img[4]);//4
                    break;
                case 15:
                    putimage(x, y, &img[5]);//5
                    break;
                case 16:
                    putimage(x, y, &img[6]);//6
                    break;
                case 17:
                    putimage(x, y, &img[7]);//7
                    break;
                case 18:
                    putimage(x, y, &img[8]);//8
                    break;
                default:
                    putimage(x, y, &img[10]);//地圖
                    break;
                }
            }
        }
    }
}

int mousedown(int map[][12]) //滑鼠點選 
{ 
    MOUSEMSG m;    //定義滑鼠訊息變數
    while (1)
    {
        //獲取滑鼠訊息
        m = GetMouseMsg();
        int mi = m.x / 50 + 1;
        int mj = m.y / 50 + 1;

        //判斷滑鼠訊息
        switch (m.uMsg)
        {
        case WM_LBUTTONDOWN:
            if (map[mi][mj] > 9)    //已翻開的情況
            {
                continue;
            }
            if (map[mi][mj] == 0)   //如果點選為0，則翻開一片。
            {
                //使用遞迴函式
                swap(map, mi, mj);
            }
            else
            {
                map[mi][mj] += 10;
                sum += 1;
            }
            return  map[mi][mj];
            break;
        case WM_RBUTTONDOWN:
            if (map[mi][mj] > 9&& map[mi][mj] < 25)    //已翻開的情況
            {
                continue;
            }
            if (map[mi][mj] > 25)       //再次點選取消flag
            {
                map[mi][mj] -= 30;
            }
            else
            {
                map[mi][mj] += 30;
            }
            return  map[mi][mj];
            break;
        }
    }
}

void swap(int map[][12],int mi,int mj) //遞迴函式 
{
    map[mi][mj] = 10;
    sum += 1;
    for (int i = mi - 1; i <= mi + 1; i++)
    {
        for (int j = mj - 1; j <= mj + 1; j++)
        {
            //陣列下標不能越界
            if (i >= 1 && i <= 10 && j >= 1 && j <= 10)
            {
                //翻開的只能是數字
                if (map[i][j] < 9)
                {
                    //如果為0，則進行遞迴。
                    if (map[i][j] == 0)
                    {
                        swap(map, i, j);
                    }
                    else
                    {
                        map[i][j] += 10;
                        sum += 1;
                    }
                }
            }
        }
    }
}

void startgame() //初始化遊戲 
{
    initgraph(500, 500);    //初始化地圖500x500
    int map[12][12] = { 0 };
    int i,j,m,n;
    //隨機函式種子
    srand((unsigned int)time(NULL));
    //隨機生成10個雷
    for (n = 0; n < 10;)
    {
        i = rand() % 10 + 1;    //[1,10]
        j = rand() % 10 + 1;
        if (map[i][j] == 0)     //排除本來就有雷的情況
        {
            map[i][j] = -1;     //-1表示有雷
            n++;
        }
    }
    //產生數字
    for (i = 1; i <= 10; i++)
    {
        for (j = 1; j <= 10; j++)
        {
            //排除是雷的情況
            if (map[i][j] != -1)
            {
                for (m = i - 1; m <= i + 1; m++)    //判斷周圍是否有雷
                {
                    for (n = j - 1; n <= j + 1; n++)
                    {
                        if (map[m][n] == -1)
                        {
                            map[i][j]++;
                        }
                    }
                }
            }
        }
    }
    IMAGE img[12];              //定義圖片變數
    loadimage(&img[0], "E:\\C++ project\\minesweeping\\0.jpg", 50, 50);
    loadimage(&img[1], "E:\\C++ project\\minesweeping\\1.gif", 50, 50);//載入圖片
    loadimage(&img[2], "E:\\C++ project\\minesweeping\\2.gif", 50, 50);
    loadimage(&img[3], "E:\\C++ project\\minesweeping\\3.gif", 50, 50);
    loadimage(&img[4], "E:\\C++ project\\minesweeping\\4.gif", 50, 50);
    loadimage(&img[5], "E:\\C++ project\\minesweeping\\5.gif", 50, 50);
    loadimage(&img[6], "E:\\C++ project\\minesweeping\\6.gif", 50, 50);
    loadimage(&img[7], "E:\\C++ project\\minesweeping\\7.gif", 50, 50);
    loadimage(&img[8], "E:\\C++ project\\minesweeping\\8.gif", 50, 50);
    loadimage(&img[9], "E:\\C++ project\\minesweeping\\flag.gif", 50, 50);
    loadimage(&img[10], "E:\\C++ project\\minesweeping\\地圖.gif", 50, 50);
    loadimage(&img[11], "E:\\C++ project\\minesweeping\\雷.gif", 50, 50);
    while (1)
   {
        drawmap(map, img);
        //點到地雷
        if (mousedown(map)==9)
        {
            sum = 0;    //重置判斷變數
            drawmap(map, img);
            MessageBox(hwnd,"你踩到雷了！","Game Over",MB_OK);
            return;
        }
        //成功完成遊戲
        if (sum == 90)
        {
            sum = 0;    //重置判斷變數
            drawmap(map, img);
            MessageBox(hwnd, "你成功完成了遊戲！", "Game Over", MB_OK);
            return;
        }
    }
}
