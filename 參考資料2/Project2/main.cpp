#include "Minesweeper.h"

int main() {

    while (true) {
        /*�гy�H������*/
        Minesweeper* app = new Minesweeper(30, 16, 55);
        delete app;/*�R���n��*/
        cout << endl;
        Sleep(3000); /*����3��*/
    }

    return 0;
}