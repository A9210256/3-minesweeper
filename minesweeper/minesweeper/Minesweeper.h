#include <iostream>
#include <utility>//pair�]�t��ӼƭȡA�P�e���@�ˡA�@�ؼҪO���O�A�]�i�H�b�w�q�ɬ��C�Ӧ������Ѫ�l�Ʀ�
#include <cstdlib>//�зǨ禡�w�A�R�W�Ŷ���
#include <ctime>//�ɶ���ơA���H���ܼƮɥ�
#include <vector>//�ϥΰʺA�}�C�����Y��
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
    Minesweeper(int = 0, int = 0, int = 0);//��l��:��=0�A�C=0�A�a�p=0
    void setRows(int);
    void setColumns(int);
    void setMines(int);
    int getRows()const;
    int getColumns()const;
    int getMines()const;
    void clearBoards(char mineBoard[][30], char gameBoard[][30]);//�M�������C������
    void placeMines(char mineBoard[][30], int mines);//��m�a�p
    void replaceMine(int row, int col, char mineBoard[][30]);//���s��m�a�p
    char indexToChar(int index);//�N�Ʀr�ܬ��r��
    int charToIndex(char ch);//�N�r���ܬ��Ʀr
    void displayBoard(char gameBoard[][30]);//�]�m�i�ܹC������
    bool isValid(int row, int col);//�T�w��C���ƥجO�_�����T
    bool isMine(int row, int col, char board[][30]);//�d�ݦ���m�O�_���a�p
    vector < pair <int, int> > getNeighbours(int row, int col);//�}�C��pair�i�H�N�@��ȡA�X���@�ӭ�
    int countAdjacentMines(int row, int col, char mineBoard[][30]);//�Ƭ۾F���a�p�ƥ�
    void uncoverBoard(char gameBoard[][30], char mineBoard[][30], int row, int col, int* nMoves);//�]�m���}�a�O(����)
    void markMines(char gameBoard[][30], char mineBoard[][30], bool won);//�T�{�O�_�аO���T���a�p
    void playMinesweeper();//��a�p

};

#endif // !Board_H