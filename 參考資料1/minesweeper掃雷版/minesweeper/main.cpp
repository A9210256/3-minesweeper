#include "Minesweeper.h"

int main() {

    while (true) {
        //create random tables continiously on the heap
        //30 rows 16 columns and 55 bombs
        Minesweeper* app = new Minesweeper(30, 16, 55);
        delete app;
        cout << endl;
        Sleep(3000); //wait for 3 sec
    }

    return 0;
}