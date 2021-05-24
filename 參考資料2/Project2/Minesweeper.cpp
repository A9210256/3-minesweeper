#include "Minesweeper.h"

Minesweeper::Minesweeper(int columns_get, int rows_get, int bomb_count_get) :
    rows{ rows_get }, columns{ columns_get }, max_size{ rows * columns }, bomb_count{ bomb_count_get }
{
    /*��l���ܼƵM��}�l�]�H�U���禡*/
    create_table(); /*�гy����*/
    add_bombs(); /*�]�m���u*/
    add_numbers(); /*�]�m�Ʀr*/
    show_table(); /*��ܤ���*/
}

Minesweeper::~Minesweeper()/*�]�m�@�ӸѺc�̥h�O�s�@�ӰO����*/
{

}

void Minesweeper::create_table() {
    table.resize(rows, vector<int>(columns, 0)); /*���O�H����rows,columns���ȥh�]�m�j�p*/
}

void Minesweeper::add_bombs() {

   
    for (int i{ 1 }; i <= max_size; ++i) {
        bombs.push_back(i);/*�s�W�����쬵�u������*/
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    /*���t�Ϊ��ɶ��d���H���o�t*/
    
    shuffle(bombs.begin(), bombs.end(), default_random_engine(seed));
    /*���u���H����m*/
 
    bombs.reserve(bomb_count);/*���ܬ��u�����t�Ŷ��A�õL��l��*/
    bombs.resize(bomb_count);/*���ܬ��u�����t�Ŷ��A�ӥB������l��*/

}

int Minesweeper::find_column(int a) {
    /*�p��@�C���h��*/
    int column_of_it{ 0 };
    if (a % columns == 0) {
        column_of_it = columns;/*�p�Ga��n�㰣�A���N�O�@��*/
    }
    else {
        column_of_it = a % columns;/*�p�G���O�N�~��*/
    }
    return column_of_it;/*�@���^��*/
}

int Minesweeper::find_row(int a, int column) {
  
    int row_of_it{ ((a - column) / columns) + 1 };/*a-�C��/�C��=��*/
    return row_of_it;
}

void Minesweeper::add_numbers() {
   
    int column_of_the_bomb_real{};/*�ŧi�@�C�����u�ƶq*/
    int row_of_the_bomb_real{};/*�ŧi�@�檺���u�ƶq*/
    int column_of_the_bomb{}; /*���@�C���}�C���s�k�s*/
    int row_of_the_bomb{}; /*���@�檺�}�C���s�k�s*/

    for (auto bomb : bombs) {

        column_of_the_bomb_real = find_column(bomb); /*�M��@�C���������u*/
        row_of_the_bomb_real = find_row(bomb, column_of_the_bomb_real); /*�M��@�椧�������u*/
        column_of_the_bomb = column_of_the_bomb_real - 1; 
        row_of_the_bomb = row_of_the_bomb_real - 1; 

        /*�ϰ�1*/
        if (row_of_the_bomb != 0 && column_of_the_bomb != 0) /*�@��M�@�C���������u������s*/
            table[row_of_the_bomb - 1][column_of_the_bomb - 1] += 1;

        /*�ϰ�2*/
        if (row_of_the_bomb != 0) 
            table[row_of_the_bomb - 1][column_of_the_bomb] += 1;/*�p�G�����W���檺���u������s�A����-1,�C����*/

        /*�ϰ�3*/
        if (row_of_the_bomb != 0 && column_of_the_bomb != columns - 1) /*�p�G��񪺬��u������s��C�񪺬��u������C-1*/
            table[row_of_the_bomb - 1][column_of_the_bomb + 1] += 1;/*�h�C-1�A��+1*/

        /*�ϰ�4*/
        if (column_of_the_bomb != 0) /*�p�G�����W���C�����u������s�A���椣��,�C��-1*/
            table[row_of_the_bomb][column_of_the_bomb - 1] += 1;

        /*�ϰ�5*/
        if (column_of_the_bomb != columns - 1) /*�p�G�����W���C�����u������C-1�A���椣��,�C+1*/
            table[row_of_the_bomb][column_of_the_bomb + 1] += 1;

        /*�ϰ�6*/
        if (row_of_the_bomb != rows - 1 && column_of_the_bomb != 0) /*�p�G��񪺬��u������s��C�񪺬��u������C-1*/
            table[row_of_the_bomb + 1][column_of_the_bomb - 1] += 1;/*�h�C-1,��+1*/

        /*�ϰ�7*/
        if (row_of_the_bomb != rows - 1) /*�p�G��񪺬��u�������-1*/
            table[row_of_the_bomb + 1][column_of_the_bomb] += 1;/*�h��+1,�C����*/

        /*�ϰ�8*/
        if (row_of_the_bomb != rows - 1 && column_of_the_bomb != columns - 1) /*�p�G��񪺬��u�������-1�M�P�񪺬��u������C-1*/
            table[row_of_the_bomb + 1][column_of_the_bomb + 1] += 1;/*�h��+1,�C+1*/

    }


}

void Minesweeper::show_table() {
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