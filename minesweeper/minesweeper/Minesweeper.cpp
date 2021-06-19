#include "Minesweeper.h"

Minesweeper::Minesweeper(int ROWS, int COLUMNS, int MINES) {
    this->ROWS = ROWS;
    this->COLUMNS = COLUMNS;
    this->MINES = MINES;
}
void Minesweeper::setRows(int ROWS) {
    this->ROWS = ROWS;
}
void Minesweeper::setColumns(int COLUMNS) {
    this->COLUMNS = COLUMNS;
}
void Minesweeper::setMines(int MINES) {
    this->MINES = MINES;
}
int Minesweeper::getRows()const {
    return ROWS;
}
int Minesweeper::getColumns()const {
    return COLUMNS;
}
int Minesweeper::getMines()const {
    return MINES;
}
void  Minesweeper::clearBoards(char mineBoard[][30], char gameBoard[][30]) {/*清除玩完遊戲版面*/
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLUMNS; j++)
            gameBoard[i][j] = mineBoard[i][j] = '.';/*遊戲版[行][列]=地雷版[行][列]*/
}

void  Minesweeper::placeMines(char mineBoard[][30], int mines) {/*放置地雷*/
    int placed = 0;/*設一個變數(放置)=0*/
    while (placed < mines) {/*當地雷的數>能放置的數*/
        int random = rand() % (ROWS * COLUMNS);/*取行列的亂數*/
        int row = random / COLUMNS;/*行=亂數/列*/
        int col = random % ROWS;/*亂數對行取餘數=列*/
        if (mineBoard[row][col] == '#') continue; // 如果碰到地雷顯示'#'，就繼續*/
        mineBoard[row][col] = '#';
        placed++;
    }
}
void  Minesweeper::replaceMine(int row, int col, char mineBoard[][30]) {/*重新放置地雷*/
    placeMines(mineBoard, 1);  /* 增加一個新地雷*/
    mineBoard[row][col] = '.'; /* 重新移動到舊地雷的位置*/
    return;
}
char  Minesweeper::indexToChar(int index) {
    if (index < 10)/*如果索引值<10*/
        return index + '0';/*回傳字元索引*/
    else
        return 'a' + (index - 10);/*否則回傳97(ASCII'a')+(索引-10)*/
}
int  Minesweeper::charToIndex(char ch) {
    if (ch <= '9')/*如果字元<=9*/
        return ch - '0';/*回傳字元-48*/
    else
        return (ch - 'a') + 10;/*否則(字元-97)+10*/
}
void  Minesweeper::displayBoard(char gameBoard[][30]) {/*設置展示遊戲版面*/
   /*最頂部*/
    cout << "    ";
    for (int i = 0; i < COLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl << endl;

    /*行跟列*/
    for (int i = 0; i < ROWS; i++) {
        cout << indexToChar(i) << "   ";
        for (int j = 0; j < COLUMNS; j++)
            cout << gameBoard[i][j] << " ";
        cout << "  " << indexToChar(i);
        cout << endl;
    }

    /* 最底部*/
    cout << endl << "    ";
    for (int i = 0; i < COLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl;

    return;
}
bool  Minesweeper::isValid(int row, int col) {/*回傳行列的數目是否為正確*/
    return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLUMNS);/*回傳(行>=0和行<設置的數目)和(列>=0和列<設置的數目)*/
}

bool  Minesweeper::isMine(int row, int col, char board[][30]) {/*回傳地雷的數目是否為正確，且放置在地板之內*/
    return (board[row][col] == '#');/*回傳地板的行列*/
}
vector < pair <int, int> >  Minesweeper::getNeighbours(int row, int col) {/*陣列的pair可以將一對值組合成一個值*/
    vector < pair <int, int> > neighbours;/*陣列的pair可以將一對值組合成一個值給neighbours這個變數*/

    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++)
            if (dx != 0 || dy != 0)
                if (isValid(row + dx, col + dy))
                    neighbours.push_back(make_pair(row + dx, col + dy));/*變數neighbours新增一個元素到最後面，由傳給make_pair的值產生一個新的pair*/

    return neighbours;
}
int  Minesweeper::countAdjacentMines(int row, int col, char mineBoard[][30]) {/*相鄰的地雷數目*/
    vector < pair <int, int> > neighbours = getNeighbours(row, col);/*陣列的pair可以將一對值組合成一個值給neighbours這個變數產生getNeighbours(新的pair)*/

    int count = 0;/*設置數目為0*/
    for (int i = 0; i < neighbours.size(); i++)
        if (isMine(neighbours[i].first, neighbours[i].second, mineBoard))/*如果neighbours第一個,第二個地雷在地版上*/
            count++;/*則數目增加*/

    return count;/*回傳數目*/
}
void  Minesweeper::uncoverBoard(char gameBoard[][30], char mineBoard[][30], int row, int col, int* nMoves) {/*設置揭開地板*/
    (*nMoves)++;/*移動的位值增加*/
    int count = countAdjacentMines(row, col, mineBoard);/*數目=相鄰的地雷數目*/
    gameBoard[row][col] = count + '0';/*遊戲版的[行][列]=數目+48(變成字元*/
    if (count == 0) {/*如果數目=0*/
        vector < pair <int, int> > neighbours = getNeighbours(row, col);/*陣列的pair可以將一對值組合成一個值給neighbours這個變數產生getNeighbours(新的pair)*/

        for (int i = 0; i < neighbours.size(); i++)
            if (gameBoard[neighbours[i].first][neighbours[i].second] == '.')/*如果遊戲版的[行][列]='.'*/
                uncoverBoard(gameBoard, mineBoard, neighbours[i].first, neighbours[i].second, nMoves);/*揭開地板(遊戲地板,地雷地板,[行],[列],移動的位值)*/
    }
}

void  Minesweeper::markMines(char gameBoard[][30], char mineBoard[][30], bool won) {/*設置標記的地雷*/
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (gameBoard[i][j] == '.' && mineBoard[i][j] == '#') {/*如果遊戲版安全的行列顯示'.'與地雷版的行列顯示'#'*/
                if (won) {
                    gameBoard[i][j] = 'F';/*如果贏了，地板會顯示'F'*/
                }
                else {
                    gameBoard[i][j] = '#';/*否則會顯示踩到地雷'#'的標示*/
                }
            }
        }
    }
}
void  Minesweeper::playMinesweeper() {/*設置玩踩地雷*/
    char mineBoard[30][30], gameBoard[30][30];/*地雷的數[行=30][列=30],安全地的數[行=30][列=30]*/
    int nMovesTotal = ROWS * COLUMNS - MINES;/*移動次數=行數*列數-地雷數*/
    int flags = MINES;/*設一個變數為地雷數*/
    clearBoards(mineBoard, gameBoard);/*清理場地*/
    placeMines(mineBoard, MINES);/*設置地雷*/

    int nMoves = 0;/*設置一開始移動次數為0*/
    bool gameOver = false;/*回傳遊戲結束為false*/

    while (!gameOver) {/*當不是遊戲結束*/
        displayBoard(gameBoard);/*展示遊戲地板*/
        cout << flags << " flags left" << endl << endl;/*剩下的地雷*/
        char x, y, z;
        /*開始遊戲*/
        cout << "Enter your move(0~" << indexToChar(ROWS - 1) << "), (¡õ) -> ";/*確定移動，開始索引轉變字元(行-1)*/
        cin >> x;
        int row = charToIndex(x);/*設置行=字元索引(x)*/
        while (row >= ROWS) {/*當移動行的次數>行設置的數目*/
            cout << "Please enter(0~" << indexToChar(ROWS - 1) << "), (¡õ) ->";
            cin >> x;
            row = charToIndex(x);/*行=字元索引(x)*/
        }

        cout << "Enter your move(0~" << indexToChar(COLUMNS - 1) << "), (¡÷) -> ";
        cin >> y;
        int col = charToIndex(y);/*設置列=字元索引(y)*/
        while (col >= COLUMNS) {/*當移動列的次數>列設置的數目*/
            cout << "Please enter(0~" << indexToChar(COLUMNS - 1) << "), (¡÷) ->";
            cin >> y;
            col = charToIndex(y);/*列=字元索引(y)*/
        }

        cout << "Enter your move, (safe(s)/flag(f)) -> ";/*確認你的移動，安全(s),地雷(f)*/
        cin >> z;
        while (z != 's' && z != 'S' && z != 'f' && z != 'F') {/*當z不是安全，也不是踩到地雷，也不是贏了*/
            cout << "Please enter(safe(s)/flag(f)) -> ";/*請確認安全(s),地雷(f)*/
            cin >> z;
        }


        cout << endl;


        if (nMoves == 0)/*如果移動次數變為0*/
            if (isMine(row, col, mineBoard))/*如果回傳地雷的地雷版的索引沒有結果*/
                replaceMine(row, col, mineBoard);/*將重新設置地雷*/

        if (z == 's') {/*當z是安全的*/
            if (gameBoard[row][col] == '.' && mineBoard[row][col] == '.') {/*如果遊戲地板與地雷版的[行][列]顯示為'.'沒被踩到*/
                uncoverBoard(gameBoard, mineBoard, row, col, &nMoves);/*則開始揭開遊戲地板下面的地雷版*/
                if (nMoves == nMovesTotal) {/*如果移動的次數=移動的總數*/
                    markMines(gameBoard, mineBoard, true);
                    displayBoard(gameBoard);/*展示遊戲地版*/
                    cout << endl << "You won!!! :)" << endl;
                    gameOver = true;
                }
            }
            else if (gameBoard[row][col] == '.' && mineBoard[row][col] == '#') {/*否則如果遊戲地板[行][列]顯示為'.'，地雷版為[行][列]顯示為'#'*/
                gameBoard[row][col] = '#';/*地板顯示為'#'*/
                markMines(gameBoard, mineBoard, false);
                displayBoard(gameBoard);/*展示遊戲地版*/
                cout << endl << "You lost! :(" << endl;
                gameOver = true;
            }
            else {
                cout << "Illegal move. ";/*違規的移動*/
                if (gameBoard[row][col] == 'F')
                    cout << "Cell is a flag. Use f to toggle flag off. ";
                else
                    cout << "Cell is already a number. ";
                cout << endl;
            }
        }
        if (z == 'f') {/*如果z=地雷*/
            if (gameBoard[row][col] == '.') {
                if (flags != 0) {/*如果地雷!=0*/
                    gameBoard[row][col] = 'F';/*地板安全*/
                    flags--;/*地雷減少*/
                }
                else {
                    cout << "Illegal move. Too many flags!" << endl;
                }
            }
            else if (gameBoard[row][col] == 'F') {/*否則如果z不是地雷*/
                gameBoard[row][col] = '.';
                flags++;/*地雷增加*/
            }
            else {
                cout << "Illegal move. Cell is a number. " << endl;
            }
        }
    }
}