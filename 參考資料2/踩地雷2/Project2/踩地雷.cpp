/*
* Assignment 09
* 04/12/18
* Section 02
*/

#include <iostream>
#include <time.h>

using namespace std;

/*�����ܼ�*/
const int ROWS = 9;
const int COLS = 9;
bool game_over = false;
char field[ROWS][COLS];
char secret[ROWS][COLS];
int win_count = 0;

/*�禡�쫬*/
void rules();
void random_gopher();/*�H���a�p*/
void create_gopher();/*�гy�a�p*/
void create_field(char arr[][COLS]);/*�гy���r���}�C*/
void print_field(char arr[][COLS]);/*�L�X���r���}�C*/
//void print_gopher(char arr[][COLS]);
void choose();/*�]�w���*/
int reveal(int, int);/*���*/




/*�D�{��*/
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

	while (game_over != true && win_count < 71);/*��C�������MĹ���ƥ�<71*/

	if (game_over == true)
	{
		cout << "You chose a gopher! Game over!" << endl;
	}

	if (win_count > 71)
	{
		cout << "Congrats, you win!" << endl;
	}

	cin.ignore();/*�W�L71���r���h�Q����*/
	cout << "Press enter to exit." << endl;
	cin.ignore();

	return 0;
}



/*��L�禡*/
void rules()
{
	cout << "Welcome to gopher hunt!\n\nTo play, enter an X value to pick a row and a Y value to pick a column.\n\n";
}

void create_field(char field[ROWS][COLS])/*�гy�r�����*/
{
	cout << "Generating field...\n\n";
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)/*��j=0,j<�C��*/
		{
			field[i][j] = '+';/*���}�C�h���'+'*/
		}
	}
}

void print_field(char field[ROWS][COLS])/*�L�X�r�����*/
{
	for (int a = 0; a < ROWS; a++)
	{
		cout << a << " ";
	}

	cout << COLS;/*��X�C*/
	cout << endl;

	for (int i = 0; i < ROWS; i++)/*�ŧii=0;i<��*/
	{
		cout << i + 1 << " ";/*��Xi+1*/

		for (int j = 0; j < COLS; j++)/*�ŧij=0;j<�C*/
		{
			cout << field[i][j] << " ";/*��X���}�C*/
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
	int horizontal = 0, vertical = 0;/*�ŧi�����M����=0*/
	cout << endl;
	cin >> horizontal;
	cin >> vertical;

	horizontal -= 1;
	vertical -= 1;

	if (horizontal > 8 || horizontal < 0 || vertical > 8 || vertical < 0)/*�p�G�������ƶq>8�άO�������ƶq<0�άO�������ƶq>8�άO�άO�������ƶq<0*/
	{
		cout << "Illegal move. Try again." << endl;/*�h��X'�W�L�o�ӽd��A�A�դ@��'*/
	}

	if (secret[horizontal][vertical] == 'G')/*�p�G�a���U�����������}�C='G'(��)*/
	{
		game_over = true;/*�h�C������*/
	}

	else
	{
		field[horizontal][vertical] = reveal(horizontal, vertical);/*�_�h�~��*/
	}
}

int reveal(int horizontal, int vertical)/*��ܫ�������*/
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



	switch (revealed_number)/*��ܼƦr���}��*/
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

void create_gopher()/*�гy�a�p*/
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