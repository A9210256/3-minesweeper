#include <iostream>
#include <utility>
#include <cstdlib>
#include <ctime>
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
	Minesweeper(int = 0, int = 0, int = 0);
	void setRows(int);
	void setColumns(int);
	void setMines(int);
	int getRows()const;
	int getColumns()const;
	int getMines()const;
    void clearBoards(char mineBoard[][30], char gameBoard[][30]);
    void placeMines(char mineBoard[][30], int mines);
    void replaceMine(int row, int col, char mineBoard[][30]);
    char indexToChar(int index);
    int charToIndex(char ch);
    void displayBoard(char gameBoard[][30]);
    bool isValid(int row, int col);
    bool isMine(int row, int col, char board[][30]);
    vector < pair <int, int> > getNeighbours(int row, int col);
    int countAdjacentMines(int row, int col, char mineBoard[][30]);
    void uncoverBoard(char gameBoard[][30], char mineBoard[][30], int row, int col, int* nMoves);
    void markMines(char gameBoard[][30], char mineBoard[][30], bool won);
    void playMinesweeper();

};

#endif // !Board_H