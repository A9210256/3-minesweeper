#ifndef Minesweeper_H
#define Minesweeper_H

#include <iostream> //to show in command prompt
#include <vector> //to create 2D Vector
#include <algorithm> //to create random bombs
#include <random> //to create random bombs
#include <chrono> //to create random bombs
#include <windows.h> //to Sleep()

using namespace std;

class Minesweeper
{
private:
    int rows; //rows, given by the user
    int columns; //columns, given by the user
    int max_size; //rows*columns
    int bomb_count; //total bombs, given by the user
    vector<vector<int>> table; //2D Vector
    vector<int> bombs; //the vector that contains locations of the bombs

    int find_column(int); //find the column of a field
    int find_row(int, int); //find the row of a field, with the known column

    void create_table(); // 1. Create table
    void add_bombs(); //2. Create random bombs
    void add_numbers(); //3. Add numbers around bombs

    void show_table(); //4. Show the table in Command Prompt

public:
    //Default constructor
    Minesweeper(int columns_get = 9, int rows_get = 9, int bomb_count_get = 10);

    //Default destructor
    ~Minesweeper();

};

#endif // !Minesweeper_H