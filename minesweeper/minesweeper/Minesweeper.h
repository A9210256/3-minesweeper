#include <iostream>
#include <utility>//pair包含兩個數值，與容器一樣，一種模板型別，也可以在定義時為每個成員提供初始化式
#include <cstdlib>//標準函式庫，命名空間用
#include <ctime>//時間函數，取隨機變數時用
#include <vector>//使用動態陣列的標頭檔
using namespace std;
#ifndef Minesweeper_H
#define Minesweeper_H

class Minesweeper
{
private:
    int ROWS;
    int COLUMNS;
    int MINES;
public:
    Minesweeper(int = 0, int = 0, int = 0);//初始值:行=0，列=0，地雷=0
    void setRows(int);
    void setColumns(int);
    void setMines(int);
    int getRows()const;
    int getColumns()const;
    int getMines()const;
    void clearBoards(char mineBoard[][30], char gameBoard[][30]);//清除玩完遊戲版面
    void placeMines(char mineBoard[][30], int mines);//放置地雷
    void replaceMine(int row, int col, char mineBoard[][30]);//重新放置地雷
    char indexToChar(int index);//將數字變為字元
    int charToIndex(char ch);//將字元變為數字
    void displayBoard(char gameBoard[][30]);//設置展示遊戲版面
    bool isValid(int row, int col);//確定行列的數目是否為正確
    bool isMine(int row, int col, char board[][30]);//查看此位置是否為地雷
    vector < pair <int, int> > getNeighbours(int row, int col);//陣列的pair可以將一對值，合成一個值
    int countAdjacentMines(int row, int col, char mineBoard[][30]);//數相鄰的地雷數目
    void uncoverBoard(char gameBoard[][30], char mineBoard[][30], int row, int col, int* nMoves);//設置揭開地板(移動)
    void markMines(char gameBoard[][30], char mineBoard[][30], bool won);//確認是否標記正確的地雷
    void playMinesweeper();//踩地雷

};

#endif // !Board_H