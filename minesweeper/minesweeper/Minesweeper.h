#include <iostream>
#include <utility>
#include <cstdlib>/*�зǨ禡�w*/
#include <ctime>/*�ɶ����*/
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
    Minesweeper(int = 0, int = 0, int = 0);/*��=0�A�C=0�A�a�p=0*/
    void setRows(int);
    void setColumns(int);
    void setMines(int);
    int getRows()const;
    int getColumns()const;
    int getMines()const;
    void clearBoards(char mineBoard[][30], char gameBoard[][30]);/*�M�������C������*/
    void placeMines(char mineBoard[][30], int mines);/*��m�a�p*/
    void replaceMine(int row, int col, char mineBoard[][30]);/*���s��m�a�p*/
    char indexToChar(int index);/*���ި�r��*/
    int charToIndex(char ch);/*�r������*/
    void displayBoard(char gameBoard[][30]);/*�]�m�i�ܹC������*/
    bool isValid(int row, int col);/*�^�Ǧ�C���ƥجO�_�����T*/
    bool isMine(int row, int col, char board[][30]);/*�^�Ǧa�p���ƥجO�_�����T�A�B��m�b�a�O����*/
    vector < pair <int, int> > getNeighbours(int row, int col);/*�}�C��pair�i�H�N�@��ȲզX���@�ӭ�*/
    int countAdjacentMines(int row, int col, char mineBoard[][30]);/*�۾F���a�p�ƥ�*/
    void uncoverBoard(char gameBoard[][30], char mineBoard[][30], int row, int col, int* nMoves);/*�]�m���}�a�O*/
    void markMines(char gameBoard[][30], char mineBoard[][30], bool won);/*�]�m�аO���a�p*/
    void playMinesweeper();/*�]�m�}�l��a�p*/

};

#endif // !Board_H