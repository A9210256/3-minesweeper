#include "Minesweeper.h"

//Constructor
Minesweeper::Minesweeper(int columns_get, int rows_get, int bomb_count_get) :
	rows{ rows_get },
	columns{ columns_get },
	max_size{ rows * columns },
	bomb_count{ bomb_count_get }
{
	//initialize the variables
	//then run the methods below in order

	create_table(); // 1. create table;
	add_bombs(); // 2. add bombs;
	add_numbers(); // 3. add numbers;
	show_table(); // 4. show table;

}

//We don't need any destructors in this case
Minesweeper::~Minesweeper()
{}

void Minesweeper::create_table() {
	//resize the table
	//with the given values of "row" and "column"
	table.resize(rows, vector<int>(columns, 0));
}

void Minesweeper::add_bombs() {

	// Assume rows=20 columns=10
	// so max_size=rows*columns
	// max_size=200 in this case
	// create a vector of integers called 'bombs' [1,2,3,4,5....,199,200]
	for (int i{ 1 }; i <= max_size; ++i) {
		bombs.push_back(i);
	}

	// feed the shuffle function by the system clock
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();

	// because we want random bombs, we need to shuffle
	// shuffle bombs vector [1,2,3,4,5....,199,200]
	// e.g. output [20,32,50,120,153,.....1,12]
	shuffle(bombs.begin(), bombs.end(), default_random_engine(seed));

	// user asks 3 bombs to be generated for example
	// bomb_count=3
	// then the expected output of bombs: [20,32,50]
	// now we have 3 bombs at the 20th, 32nd and 50th squares
	bombs.reserve(bomb_count);
	bombs.resize(bomb_count);

}

int Minesweeper::find_column(int a) {
	//calculate the column by the given square number
	int column_of_it{ 0 };
	if (a % columns == 0) {
		column_of_it = columns;
	}
	else {
		column_of_it = a % columns;
	}
	return column_of_it;
}

int Minesweeper::find_row(int a, int column) {
	//calculate the row by the given square number and the column
	//we have to find_column first in order to find_row
	int row_of_it{ ((a - column) / columns) + 1 };
	return row_of_it;
}

void Minesweeper::add_numbers() {
    // add numbers
    int column_of_the_bomb_real{};
    int row_of_the_bomb_real{};
    int column_of_the_bomb{}; //for vector starting at 0
    int row_of_the_bomb{}; //for vector starting at 0

    for (auto bomb : bombs) {
        //for each of the bombs

        //find the column of the bomb
        column_of_the_bomb_real = find_column(bomb);

        //find the row of the bomb
        row_of_the_bomb_real = find_row(bomb, column_of_the_bomb_real);

        //for vector starting at 0
        column_of_the_bomb = column_of_the_bomb_real - 1;

        //for vector starting at 0
        row_of_the_bomb = row_of_the_bomb_real - 1;

        // add the numbers around each bomb
        // if statements are checking for the edges of the table
        // the areas around one bomb look like this:
        //   1 2 3
        //   4 * 5 
        //   6 7 8

        //for area "1"
        if (row_of_the_bomb != 0 && column_of_the_bomb != 0) //check for edge
            table[row_of_the_bomb - 1][column_of_the_bomb - 1] += 1;

        //for area "2"
        if (row_of_the_bomb != 0) //check for edge
            table[row_of_the_bomb - 1][column_of_the_bomb] += 1;

        //for area "3"
        if (row_of_the_bomb != 0 && column_of_the_bomb != columns - 1) //check for edge
            table[row_of_the_bomb - 1][column_of_the_bomb + 1] += 1;

        //for area "4"
        if (column_of_the_bomb != 0) //check for edge
            table[row_of_the_bomb][column_of_the_bomb - 1] += 1;

        //for area "5"
        if (column_of_the_bomb != columns - 1) //check for edge
            table[row_of_the_bomb][column_of_the_bomb + 1] += 1;

        //for area "6"
        if (row_of_the_bomb != rows - 1 && column_of_the_bomb != 0) //check for edge
            table[row_of_the_bomb + 1][column_of_the_bomb - 1] += 1;

        //for area "7"
        if (row_of_the_bomb != rows - 1) //check for edge
            table[row_of_the_bomb + 1][column_of_the_bomb] += 1;

        //for area "8"
        if (row_of_the_bomb != rows - 1 && column_of_the_bomb != columns - 1) //check for edge
            table[row_of_the_bomb + 1][column_of_the_bomb + 1] += 1;

    }

}

void Minesweeper::show_table() {
    //print the 2D vector table

    int square_of_the_bomb{ 0 };

    for (int r = 1; r <= rows; r++) {
        for (int c = 1; c <= columns; c++) {

            // find the square of the bomb formula
            // (by given row and column)
            square_of_the_bomb = ((r - 1) * columns) + c;

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