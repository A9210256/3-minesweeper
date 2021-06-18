#include "Minesweeper.h"

Minesweeper::Minesweeper(int columns_get, int rows_get, int bomb_count_get) :
    rows{ rows_get }, columns{ columns_get }, max_size{ rows * columns }, bomb_count{ bomb_count_get }
{
    /*初始化變數然後開始跑以下的函式*/
    create_table(); /*創造介面*/
    add_bombs(); /*設置炸彈*/
    add_numbers(); /*設置數字*/
    show_table(); /*顯示介面*/
}

Minesweeper::~Minesweeper()/*設置一個解構者去保存一個記憶體*/
{

}

void Minesweeper::create_table() {/*設置遊戲介面*/
    table.resize(rows, vector<int>(columns, 0)); /*讓別人給的rows,columns的值去設置大小*/
}

void Minesweeper::add_bombs() {/*設置加入炸彈*/

   
    for (int i{ 1 }; i <= max_size; ++i) {
        bombs.push_back(i);/*新增元素到炸彈的尾端*/
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    /*讓系統的時間範圍隨機發配*/
    
    shuffle(bombs.begin(), bombs.end(), default_random_engine(seed));
    /*炸彈的隨機放置*/
 
    bombs.reserve(bomb_count);/*改變炸彈的分配空間，並無初始化*/
    bombs.resize(bomb_count);/*改變炸彈的分配空間，而且全部初始化*/

}

int Minesweeper::find_column(int a) {/*找到列裡面的沒有踩到炸彈的數量*/
    /*計算一列有多少*/
    int column_of_it{ 0 };
    if (a % columns == 0) {
        column_of_it = columns;/*如果a剛好整除，那就是一行*/
    }
    else {
        column_of_it = a % columns;/*如果不是就繼續除*/
    }
    return column_of_it;/*一直回傳*/
}

int Minesweeper::find_row(int a, int column) {
  
    int row_of_it{ ((a - column) / columns) + 1 };/*a-列數/列數=行*/
    return row_of_it;
}

void Minesweeper::add_numbers() {/*設置加入數量*/
   
    int column_of_the_bomb_real{};/*宣告一列的炸彈數量*/
    int row_of_the_bomb_real{};/*宣告一行的炸彈數量*/
    int column_of_the_bomb{}; /*讓一列的陣列重新歸零*/
    int row_of_the_bomb{}; /*讓一行的陣列重新歸零*/

    for (auto bomb : bombs) {

        column_of_the_bomb_real = find_column(bomb); /*尋找一列之中的炸彈*/
        row_of_the_bomb_real = find_row(bomb, column_of_the_bomb_real); /*尋找一行之中的炸彈*/
        column_of_the_bomb = column_of_the_bomb_real - 1; /*一列的炸彈=真正放置炸彈的數量-1*/
        row_of_the_bomb = row_of_the_bomb_real - 1; /*一行的炸彈=真正放置炸彈的數量-1*/

        /*區域1*/
        if (row_of_the_bomb != 0 && column_of_the_bomb != 0) /*一行和一列之中的炸彈不等於零*/
            table[row_of_the_bomb - 1][column_of_the_bomb - 1] += 1;

        /*區域2*/
        if (row_of_the_bomb != 0) 
            table[row_of_the_bomb - 1][column_of_the_bomb] += 1;/*如果介面上的行的炸彈不等於零，那行-1,列不變*/

        /*區域3*/
        if (row_of_the_bomb != 0 && column_of_the_bomb != columns - 1) /*如果行放的炸彈不等於零跟列放的炸彈不等於列-1*/
            table[row_of_the_bomb - 1][column_of_the_bomb + 1] += 1;/*則列-1，行+1*/

        /*區域4*/
        if (column_of_the_bomb != 0) /*如果介面上的列的炸彈不等於零，那行不變,列不-1*/
            table[row_of_the_bomb][column_of_the_bomb - 1] += 1;

        /*區域5*/
        if (column_of_the_bomb != columns - 1) /*如果介面上的列的炸彈不等於列-1，那行不變,列+1*/
            table[row_of_the_bomb][column_of_the_bomb + 1] += 1;

        /*區域6*/
        if (row_of_the_bomb != rows - 1 && column_of_the_bomb != 0) /*如果行放的炸彈不等於零跟列放的炸彈不等於列-1*/
            table[row_of_the_bomb + 1][column_of_the_bomb - 1] += 1;/*則列-1,行+1*/

        /*區域7*/
        if (row_of_the_bomb != rows - 1) /*如果行放的炸彈不等於行-1*/
            table[row_of_the_bomb + 1][column_of_the_bomb] += 1;/*則行+1,列不變*/

        /*區域8*/
        if (row_of_the_bomb != rows - 1 && column_of_the_bomb != columns - 1) /*如果行放的炸彈不等於行-1和烈放的炸彈不等於列-1*/
            table[row_of_the_bomb + 1][column_of_the_bomb + 1] += 1;/*則行+1,列+1*/

    }


}

void Minesweeper::show_table() {/*設置顯示遊戲介面*/
    //print the 2D vector table

    int square_of_the_bomb{ 0 };

    for (int r = 1; r <= rows; r++) {
        for (int c = 1; c <= columns; c++) {
            square_of_the_bomb = ((r - 1) * columns) + c; // find the square of the bomb formula (by given row and column)
            if (find(bombs.begin(), bombs.end(), square_of_the_bomb) != bombs.end()) {
                //if the square is bomb, print *
                cout << "*" << " ";
            }
            else if (table[r - 1][c - 1] == 0) {
                //if the square is empty, print white space
                cout << "  ";
            }
            else {
                //if the square is number, print number
                cout << table[r - 1][c - 1] << " ";
            }

        }
        cout << endl;
    }

    //print the bomb locations
    cout << endl << "[ ";
    for (auto a : bombs)
        cout << a << ", ";
    cout << "]" << endl;

}
