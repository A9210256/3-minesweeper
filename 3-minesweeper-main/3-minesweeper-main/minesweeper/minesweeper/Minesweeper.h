#include <iostream>
#include <utility>
#include <cstdlib>/*標準函式庫*/
#include <ctime>/*時間函數*/
#include <vector>
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
    Minesweeper(int = 0, int = 0, int = 0);/*行=0，列=0，地雷=0*/
    void setRows(int);
    void setColumns(int);
    void setMines(int);
    int getRows()const;
    int getColumns()const;
    int getMines()const;
    void clearBoards(char mineBoard[][30], char gameBoard[][30]);/*清除玩完遊戲版面*/
    void placeMines(char mineBoard[][30], int mines);/*放置地雷*/
    void replaceMine(int row, int col, char mineBoard[][30]);/*重新放置地雷*/
    char indexToChar(int index);/*索引到字元*/
    int charToIndex(char ch);/*字元索引*/
    void displayBoard(char gameBoard[][30]);/*設置展示遊戲版面*/
    bool isValid(int row, int col);/*回傳行列的數目是否為正確*/
    bool isMine(int row, int col, char board[][30]);/*回傳地雷的數目是否為正確，且放置在地板之內*/
    vector < pair <int, int> > getNeighbours(int row, int col);/*陣列的pair可以將一對值組合成一個值*/
    int countAdjacentMines(int row, int col, char mineBoard[][30]);/*相鄰的地雷數目*/
    void uncoverBoard(char gameBoard[][30], char mineBoard[][30], int row, int col, int* nMoves);/*設置揭開地板*/
    void markMines(char gameBoard[][30], char mineBoard[][30], bool won);/*設置標記的地雷*/
    void playMinesweeper();/*設置開始踩地雷*/

};

#endif // !Board_H