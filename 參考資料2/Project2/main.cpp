#include "Minesweeper.h"

int main() {

    while (true) {
        /*創造隨機介面*/
        Minesweeper* app = new Minesweeper(30, 16, 55);
        delete app;/*刪除軟體*/
        cout << endl;
        Sleep(3000); /*等待3秒*/
    }

    return 0;
}