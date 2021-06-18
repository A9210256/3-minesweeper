#include "Minesweeper.h"

int main() {

    srand(time(0));/*�]�w�ؤl��*/

    Minesweeper gameboard;

    bool level = true;/*�^�ǹC�����Ŭ����T*/
    while (level) {
        cout << "Enter the Difficulty Level" << endl;
        cout << "Press 0 for 10 * 10 cells and 10 mines" << endl;
        cout << "Press 1 for 15 * 15 cells and 15 mines" << endl;
        cout << "Press 2 for 20 * 20 cells and 20 mines" << endl;

        int board;
        cin >> board;
        switch (board) {/*���Ū����P�A�a�O�����n�B�ƶq�]�|���P*/
        case 0:
            gameboard.setRows(10);
            gameboard.setColumns(10);
            gameboard.setMines(10);
            level = false;
            break;
        case 1:
            gameboard.setRows(15);
            gameboard.setColumns(15);
            gameboard.setMines(15);
            level = false;
            break;
        case 2:
            gameboard.setRows(20);
            gameboard.setColumns(20);
            gameboard.setMines(20);
            level = false;
            break;
        default:
            cout << "Please enter 0 or 1 or 2!!" << endl;
            cout << "-----------------------------------------" << endl;
        }
    }

    gameboard.playMinesweeper();/*�}�l��a�p*/

    return 0;
}