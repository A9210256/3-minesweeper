/*
* Assignment 09
* 04/12/18
* Section 02
*/

#include <iostream>
#include <time.h>

using namespace std;

/*全域變數*/
const int ROWS = 9;
const int COLS = 9;
bool game_over = false;
char field[ROWS][COLS];
char secret[ROWS][COLS];
int win_count = 0;

/*函式原型*/
void rules();
void random_gopher();/*隨機地雷*/
void create_gopher();/*創造地雷*/
void create_field(char arr[][COLS]);/*創造欄位字元陣列*/
void print_field(char arr[][COLS]);/*印出欄位字元陣列*/
//void print_gopher(char arr[][COLS]);
void choose();/*設定選擇*/
int reveal(int, int);/*顯示*/




/*主程式*/
int main()
{
	rules();

	create_field(field);

	create_gopher();

	do
	{
		cout << endl;
		print_field(field);
		//print_gopher(secret);
		choose();
		win_count += 1;
	}

	while (game_over != true && win_count < 71);/*當遊戲結束和贏的數目<71*/

	if (game_over == true)
	{
		cout << "You chose a gopher! Game over!" << endl;
	}

	if (win_count > 71)
	{
		cout << "Congrats, you win!" << endl;
	}

	cin.ignore();/*超過71的字元則被忽略*/
	cout << "Press enter to exit." << endl;
	cin.ignore();

	return 0;
}



/*其他函式*/
void rules()
{
	cout << "Welcome to gopher hunt!\n\nTo play, enter an X value to pick a row and a Y value to pick a column.\n\n";
}

void create_field(char field[ROWS][COLS])/*創造字元欄位*/
{
	cout << "Generating field...\n\n";
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)/*當j=0,j<列時*/
		{
			field[i][j] = '+';/*欄位陣列則顯示'+'*/
		}
	}
}

void print_field(char field[ROWS][COLS])/*印出字元欄位*/
{
	for (int a = 0; a < ROWS; a++)
	{
		cout << a << " ";
	}

	cout << COLS;/*輸出列*/
	cout << endl;

	for (int i = 0; i < ROWS; i++)/*宣告i=0;i<行*/
	{
		cout << i + 1 << " ";/*輸出i+1*/

		for (int j = 0; j < COLS; j++)/*宣告j=0;j<列*/
		{
			cout << field[i][j] << " ";/*輸出欄位陣列*/
		}

		cout << endl;
	}
}

/*void print_gopher(char secret[ROWS][COLS])
{
for (int a = 0; a < ROWS; a++)
{
cout << a << " ";
}

cout << COLS;
cout << endl;

for (int i = 0; i < ROWS; i++)
{
cout << i + 1 << " ";

for (int j = 0; j < COLS; j++)
{
cout << secret[i][j] << " ";
}

cout << endl;
}
}*/

void choose()
{
	int horizontal = 0, vertical = 0;/*宣告垂直和水平=0*/
	cout << endl;
	cin >> horizontal;
	cin >> vertical;

	horizontal -= 1;
	vertical -= 1;

	if (horizontal > 8 || horizontal < 0 || vertical > 8 || vertical < 0)/*如果水平的數量>8或是水平的數量<0或是垂直的數量>8或是或是垂直的數量<0*/
	{
		cout << "Illegal move. Try again." << endl;/*則輸出'超過這個範圍，再試一次'*/
	}

	if (secret[horizontal][vertical] == 'G')/*如果地面下的垂直水平陣列='G'(踩中)*/
	{
		game_over = true;/*則遊戲結束*/
	}

	else
	{
		field[horizontal][vertical] = reveal(horizontal, vertical);/*否則繼續*/
	}
}

int reveal(int horizontal, int vertical)/*顯示垂直水平*/
{
	int revealed_number = 0;

	if (secret[horizontal + 1][vertical] == 'G')
	{
		revealed_number += 1;
	}

	if (secret[horizontal - 1][vertical] == 'G')
	{
		revealed_number += 1;
	}

	if (secret[horizontal][vertical + 1] == 'G')
	{
		revealed_number += 1;
	}

	if (secret[horizontal][vertical - 1] == 'G')
	{
		revealed_number += 1;
	}

	if (revealed_number == 0)
	{
		secret[horizontal + 1][vertical] == 0;
	}



	switch (revealed_number)/*顯示數字的開關*/
	{
	case 0:
		revealed_number = '0';
		break;
	case 1:
		revealed_number = '1';
		break;
	case 2:
		revealed_number = '2';
		break;
	case 3:
		revealed_number = '3';
		break;
	}

	return revealed_number;
}



/*void random_gopher()
{

srand(time(NULL));

for (int i = 0; i < ROWS; i++)
{
for (int j = 0; j < COLS; j++)
{
secret[i][j] = 'S';
}
}

for (int a = 0; a < 10; a++)
{
int b = rand() % ROWS;
int c = rand() % COLS;

if (secret[b][c] == 'G')
{
a--;
continue;
}

secret[b][c] = 'G';
}3

}*/

void create_gopher()/*創造地雷*/
{
	secret[2][3] = 'G';
	secret[5][6] = 'G';
	secret[4][1] = 'G';
	secret[8][9] = 'G';
	secret[3][6] = 'G';
	secret[7][4] = 'G';
	secret[9][9] = 'G';
	secret[5][8] = 'G';
	secret[2][9] = 'G';
	secret[1][7] = 'G';
}