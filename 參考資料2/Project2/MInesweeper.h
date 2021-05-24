#include <iostream>
#include <vector>/*�}�C�����Y��*/
#include <algorithm>/*�w�q�F�@�Ǩ禡�A�i�H�����禡�� lambda �B�⦡�@���޼�*/
#include <random>/*�H���üƪ����Y��*/
#include <chrono>/*�����ɶ������O�����Y��*/
#include <windows.h>

using namespace std;

class Minesweeper
{
private:
    int rows;/*�ŧi��*/
    int columns;/*�ŧi�C*/
    int max_size;/*�ŧi�̤j��*/
    int bomb_count;/*�ŧi���u���ƶq*/
    vector<vector<int>> table; /*�C������*/
    vector<int> bombs; /*�]�t���u��}���}�C*/
 

    int find_column(int);
    int find_row(int, int);

    void create_table();/*�гy�@�ӹC������*/
    void add_bombs();/*�]�m���u*/
    void add_numbers();/*�]�m�Ʀr*/

    void show_table();/*�]�m��ܤ���*/

public:
    Minesweeper(int columns_get = 9, int rows_get = 9, int bomb_count_get = 10);
    ~Minesweeper();/*�Ѻc��*/

};
