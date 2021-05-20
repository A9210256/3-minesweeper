// https://codereview.stackexchange.com/questions/141717/minesweeper-in-c 
/*Minesweeper C++
Written by:-Teodor D.*/  

#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<iomanip>
#include <time.h>

/*Rules:
The player enters 'o' , then enters value of i and j to open cell[i][j].
Enter 'f' ,then enter value of i and j to place a flag on cell[i][j] */

using namespace std;

void reveal(int, int);  /// reveals a cell with given coordinates 
void create_mine_positions(); 
void cell_number(); //increases the number of a cell with 1
void create_table(); //creates the game table
void open_cell(); // opens a cell
void game(); 
void print_table(char); // prints the game table

char table[10][10]; //the game table visible ot the player
char table_mine_positions[10][10]; //table with the positions of the mines and the number of each cell
char symbol; //the input symbol, it can be 'o' or f'
int flag_counter=0;
int mines_flagged_counter=0;
bool end_game_lose=false;
time_t time_since_epoch = time(0);
time_t game_time;

void cell_number(int i,int j)
{
if(i>=0&&i<10&&j>=0&&j<10&&table_mine_positions[i][j]!='X')
table_mine_positions[i][j]++;
}

void create_mine_positions()
{
int counter=0;
srand(time(NULL));

for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            table_mine_positions[i][j]='0';

        int i=0;
        int j=0;
 while(counter<10)
    {
        int i=rand()%10;
        int j=rand()%10;
        if(table_mine_positions[i][j]=='0'){
            table_mine_positions[i][j]='X';

            cell_number(i-1,j);
            cell_number(i+1,j);
            cell_number(i,j-1);
            cell_number(i,j+1);
            cell_number(i-1,j-1);
            cell_number(i-1,j+1);
            cell_number(i+1,j-1);
            cell_number(i+1,j+1);
            counter++;
        }
    }
}

void create_table()
{
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            table[i][j]='*';
}

void print_table(char arr[10][10])
{
    cout<<"    ";
    for(int i=0;i<10;i++)
        cout<<setw(3)<<i;

    cout<<endl<<"  ";
    for(int i=0;i<32;i++)
        cout<<"_";
        cout<<endl;

    for(int i=0;i<10;i++){
            cout<<setw(3)<<i<<"|";
        for(int j=0;j<10;j++)
            cout<<setw(3)<<arr[i][j];
            cout<<endl;
    }
}

void open_cell()
{
int i,j;

do
cin>>i>>j;
while(i<0||i>9||j<0||j>9);

if(table_mine_positions[i][j]=='X')
    {
        table[i][j]='X';
        end_game_lose=true;

        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                if(table_mine_positions[i][j]=='X')
                    table[i][j]='X';
    }
    else
        reveal(i,j);
}

void place_or_remove_flag()
{
int i,j;
do
cin>>i>>j;
while(i<0||i>9||j<0||j>9);

if (table[i][j]=='*')
    {
    table[i][j]='F';
    flag_counter++;

    if(table_mine_positions[i][j]=='X')
        mines_flagged_counter++;
    }

else if (table[i][j]=='F')
    {
    table[i][j]='*';
    flag_counter--;
    if(table_mine_positions[i][j]=='X')
        mines_flagged_counter--;
    }
}

void input_symbol()
{
   cin>>symbol;
    switch (symbol){
    case 'o' : open_cell(); break;
    case 'f' : place_or_remove_flag(); break;
    default  : input_symbol();
    }
}

void reveal(int i,int j)
{
if (table[i][j]=='*'&&table_mine_positions[i][j]!='X'&&i>=0&&i<10&&j>=0&&j<10)
    {
    table[i][j]=table_mine_positions[i][j];

    if(table_mine_positions[i][j]=='0')
        {
        reveal(i,j-1);
        reveal(i,j+1);
        reveal(i-1,j-1);
        reveal(i+1,j-1);
        reveal(i+1,j+1);
        reveal(i-1,j+1);
        reveal(i-1,j);
        reveal(i+1,j);
        }
    }
}

bool end_game_win_check()
{
    if(flag_counter==10&&mines_flagged_counter==10)
    return 1;
    else
    return 0;
}

void game()
{
    create_table();
    create_mine_positions();

    while(!end_game_lose&&!end_game_win_check())
    {
    game_time=time(0);
    print_table(table);
    cout<<endl<<"Flags:"<<flag_counter<<endl;
    cout<<"Time:"<<game_time-time_since_epoch<<endl;
    input_symbol();
    }

    if(end_game_lose){
    print_table(table);
    cout<<endl<<"GAME OVER"<<endl;
    }

    if(end_game_win_check())
    cout<<"Time to complete:"<<game_time-time_since_epoch<<endl;
    cout<<endl<<"YOU WIN!"<<endl;
}

int main()
{
cout
<<"Rules:"
<<endl<<"Enter 'o' , then enter value of i and j to open cell[i][j]."
<<endl<<"Enter 'f' ,then enter value of i and j to place "
<<"or remove flag on cell [i][j]."
<<endl<<endl;

game();

return 0;
}
