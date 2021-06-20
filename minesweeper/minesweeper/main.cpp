#include "Minesweeper.h"

int main() {

    srand(time(0));//設定種子數

    Minesweeper gameboard;

    bool level = true;//設定level為true以執行以下while迴圈
    while (level) {
        cout << "Enter the Difficulty Level" << endl;
        cout << "Press 0 for 10 * 10 cells and 10 mines" << endl;
        cout << "Press 1 for 15 * 15 cells and 15 mines" << endl;
        cout << "Press 2 for 20 * 20 cells and 20 mines" << endl;

        int board;
        cin >> board;
        switch (board) {//等級的不同，地板的面積、地雷數量也會不同
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

    gameboard.playMinesweeper();//呼叫物件，開始踩地雷

    return 0;
}