#include<iostream>
#include<time.h>
#include<graphics.h>        //�ϧήw���Y�ɮ� easyx
#include <conio.h>          //�I�s_getch�禡
using namespace std;
HWND hwnd;
int sum = 0;//�Ω��ܥثe�w�g�I�}����l��
//�ŧi�禡
void drawmap(int map[][12], IMAGE* img);
int mousedown(int map[][12]);
void swap(int map[][12], int mi, int mj);
//��l�ƹC��

//ø�s�a��

//�ƹ��I��

//���j�禡

int main()
{
    while (1)
    {
        startgame();
        if (MessageBox(hwnd, "�A�Ӥ@��", "�����C��", MB_YESNO)==IDNO)
            break;
    }
    //_getch();                //����{��
    closegraph();
    return 0;
}

void drawmap(int map[][12],IMAGE *img) //ø�s�a�� 
{
    int i, j;
    for (i = 1; i <= 10; i++)
    {
        for (j = 0; j <= 10; j++)
        {
            int x = 50 * (i - 1);//�o���m
            int y = 50 * (j - 1);
            if (map[i][j]>25)
            {
                putimage(x, y, &img[9]);//�аOflag
            }
            else
            {
                switch (map[i][j])
                {
                case 9:
                    putimage(x, y, &img[11]);//��X�Ϥ��p
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
                    putimage(x, y, &img[10]);//�a��
                    break;
                }
            }
        }
    }
}

int mousedown(int map[][12]) //�ƹ��I�� 
{ 
    MOUSEMSG m;    //�w�q�ƹ��T���ܼ�
    while (1)
    {
        //����ƹ��T��
        m = GetMouseMsg();
        int mi = m.x / 50 + 1;
        int mj = m.y / 50 + 1;

        //�P�_�ƹ��T��
        switch (m.uMsg)
        {
        case WM_LBUTTONDOWN:
            if (map[mi][mj] > 9)    //�w½�}�����p
            {
                continue;
            }
            if (map[mi][mj] == 0)   //�p�G�I�אּ0�A�h½�}�@���C
            {
                //�ϥλ��j�禡
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
            if (map[mi][mj] > 9&& map[mi][mj] < 25)    //�w½�}�����p
            {
                continue;
            }
            if (map[mi][mj] > 25)       //�A���I�����flag
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

void swap(int map[][12],int mi,int mj) //���j�禡 
{
    map[mi][mj] = 10;
    sum += 1;
    for (int i = mi - 1; i <= mi + 1; i++)
    {
        for (int j = mj - 1; j <= mj + 1; j++)
        {
            //�}�C�U�Ф���V��
            if (i >= 1 && i <= 10 && j >= 1 && j <= 10)
            {
                //½�}���u��O�Ʀr
                if (map[i][j] < 9)
                {
                    //�p�G��0�A�h�i�滼�j�C
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

void startgame() //��l�ƹC�� 
{
    initgraph(500, 500);    //��l�Ʀa��500x500
    int map[12][12] = { 0 };
    int i,j,m,n;
    //�H���禡�ؤl
    srand((unsigned int)time(NULL));
    //�H���ͦ�10�ӹp
    for (n = 0; n < 10;)
    {
        i = rand() % 10 + 1;    //[1,10]
        j = rand() % 10 + 1;
        if (map[i][j] == 0)     //�ư����ӴN���p�����p
        {
            map[i][j] = -1;     //-1��ܦ��p
            n++;
        }
    }
    //���ͼƦr
    for (i = 1; i <= 10; i++)
    {
        for (j = 1; j <= 10; j++)
        {
            //�ư��O�p�����p
            if (map[i][j] != -1)
            {
                for (m = i - 1; m <= i + 1; m++)    //�P�_�P��O�_���p
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
    IMAGE img[12];              //�w�q�Ϥ��ܼ�
    loadimage(&img[0], "E:\\C++ project\\minesweeping\\0.jpg", 50, 50);
    loadimage(&img[1], "E:\\C++ project\\minesweeping\\1.gif", 50, 50);//���J�Ϥ�
    loadimage(&img[2], "E:\\C++ project\\minesweeping\\2.gif", 50, 50);
    loadimage(&img[3], "E:\\C++ project\\minesweeping\\3.gif", 50, 50);
    loadimage(&img[4], "E:\\C++ project\\minesweeping\\4.gif", 50, 50);
    loadimage(&img[5], "E:\\C++ project\\minesweeping\\5.gif", 50, 50);
    loadimage(&img[6], "E:\\C++ project\\minesweeping\\6.gif", 50, 50);
    loadimage(&img[7], "E:\\C++ project\\minesweeping\\7.gif", 50, 50);
    loadimage(&img[8], "E:\\C++ project\\minesweeping\\8.gif", 50, 50);
    loadimage(&img[9], "E:\\C++ project\\minesweeping\\flag.gif", 50, 50);
    loadimage(&img[10], "E:\\C++ project\\minesweeping\\�a��.gif", 50, 50);
    loadimage(&img[11], "E:\\C++ project\\minesweeping\\�p.gif", 50, 50);
    while (1)
   {
        drawmap(map, img);
        //�I��a�p
        if (mousedown(map)==9)
        {
            sum = 0;    //���m�P�_�ܼ�
            drawmap(map, img);
            MessageBox(hwnd,"�A���p�F�I","Game Over",MB_OK);
            return;
        }
        //���\�����C��
        if (sum == 90)
        {
            sum = 0;    //���m�P�_�ܼ�
            drawmap(map, img);
            MessageBox(hwnd, "�A���\�����F�C���I", "Game Over", MB_OK);
            return;
        }
    }
}
