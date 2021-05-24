//https://seckinpoyraz.com/blog/create-minesweeper-in-cpp.html
#include <iostream>
#include <vector>/*陣列的標頭檔*/
#include <algorithm>/*定義了一些函式，可以接受函式或 lambda 運算式作為引數*/
#include <random>/*隨機亂數的標頭檔*/
#include <chrono>/*紀錄時間的類別的標頭檔*/
#include <windows.h>

using namespace std;

class Minesweeper
{
private:
    int rows;/*宣告行*/
    int columns;/*宣告列*/
    int max_size;/*宣告最大值*/
    int bomb_count;/*宣告炸彈的數量*/
    vector<vector<int>> table; /*遊戲介面*/
    vector<int> bombs; /*包含炸彈位址的陣列*/
 

    int find_column(int);
    int find_row(int, int);

    void create_table();/*創造一個遊戲介面*/
    void add_bombs();/*設置炸彈*/
    void add_numbers();/*設置數字*/

    void show_table();/*設置顯示介面*/

public:
    Minesweeper(int columns_get = 9, int rows_get = 9, int bomb_count_get = 10);
    ~Minesweeper();/*解構者*/

};
