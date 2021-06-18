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
void  Minesweeper::clearBoards(char mineBoard[][30], char gameBoard[][30]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLUMNS; j++)
            gameBoard[i][j] = mineBoard[i][j] = '.';
}

void  Minesweeper::placeMines(char mineBoard[][30], int mines) {
    int placed = 0;
    while (placed < mines) {
        int random = rand() % (ROWS * COLUMNS);
        int row = random / COLUMNS;
        int col = random % ROWS;
        if (mineBoard[row][col] == '#') continue; // already a mine
        mineBoard[row][col] = '#';
        placed++;
    }
}
void  Minesweeper::replaceMine(int row, int col, char mineBoard[][30]) {
    placeMines(mineBoard, 1);  // add a new mine
    mineBoard[row][col] = '.'; // remove the old one
    return;
}
char  Minesweeper::indexToChar(int index) {
    if (index < 10)
        return index + '0';
    else
        return 'a' + (index - 10);
}
int  Minesweeper::charToIndex(char ch) {
    if (ch <= '9')
        return ch - '0';
    else
        return (ch - 'a') + 10;
}
void  Minesweeper::displayBoard(char gameBoard[][30]) {
    // top line
    cout << "    ";
    for (int i = 0; i < COLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl << endl;

    // rows
    for (int i = 0; i < ROWS; i++) {
        cout << indexToChar(i) << "   ";
        for (int j = 0; j < COLUMNS; j++)
            cout << gameBoard[i][j] << " ";
        cout << "  " << indexToChar(i);
        cout << endl;
    }

    // bottom line
    cout << endl << "    ";
    for (int i = 0; i < COLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl;

    return;
}
bool  Minesweeper::isValid(int row, int col) {
    return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLUMNS);
}

bool  Minesweeper::isMine(int row, int col, char board[][30]) {
    return (board[row][col] == '#');
}
vector < pair <int, int> >  Minesweeper::getNeighbours(int row, int col) {
    vector < pair <int, int> > neighbours;

    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++)
            if (dx != 0 || dy != 0)
                if (isValid(row + dx, col + dy))
                    neighbours.push_back(make_pair(row + dx, col + dy));

    return neighbours;
}
int  Minesweeper::countAdjacentMines(int row, int col, char mineBoard[][30]) {
    vector < pair <int, int> > neighbours = getNeighbours(row, col);

    int count = 0;
    for (int i = 0; i < neighbours.size(); i++)
        if (isMine(neighbours[i].first, neighbours[i].second, mineBoard))
            count++;

    return count;
}
void  Minesweeper::uncoverBoard(char gameBoard[][30], char mineBoard[][30], int row, int col, int* nMoves) {
    (*nMoves)++;
    int count = countAdjacentMines(row, col, mineBoard);
    gameBoard[row][col] = count + '0';
    if (count == 0) {
        vector < pair <int, int> > neighbours = getNeighbours(row, col);

        for (int i = 0; i < neighbours.size(); i++)
            if (gameBoard[neighbours[i].first][neighbours[i].second] == '.')
                uncoverBoard(gameBoard, mineBoard, neighbours[i].first, neighbours[i].second, nMoves);
    }
}

void  Minesweeper::markMines(char gameBoard[][30], char mineBoard[][30], bool won) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (gameBoard[i][j] == '.' && mineBoard[i][j] == '#') {
                if (won) {
                    gameBoard[i][j] = 'F';
                }
                else {
                    gameBoard[i][j] = '#';
                }
            }
        }
    }
}
void  Minesweeper::playMinesweeper() {
    char mineBoard[30][30], gameBoard[30][30];
    int nMovesTotal = ROWS * COLUMNS - MINES;
    int flags = MINES;
    clearBoards(mineBoard, gameBoard);
    placeMines(mineBoard, MINES);

    int nMoves = 0;
    bool gameOver = false;

    while (!gameOver) {
        displayBoard(gameBoard);
        cout << flags << " flags left" << endl << endl;
        char x, y, z;

        cout << "Enter your move(0~" << indexToChar(ROWS - 1) << "), (¡õ) -> ";
        cin >> x;
        int row = charToIndex(x);
        while (row >= ROWS) {
            cout << "Please enter(0~" << indexToChar(ROWS - 1) << "), (¡õ) ->";
            cin >> x;
            row = charToIndex(x);
        }

        cout << "Enter your move(0~" << indexToChar(COLUMNS - 1) << "), (¡÷) -> ";
        cin >> y;
        int col = charToIndex(y);
        while (col >= COLUMNS) {
            cout << "Please enter(0~" << indexToChar(COLUMNS - 1) << "), (¡÷) ->";
            cin >> y;
            col = charToIndex(y);
        }

        cout << "Enter your move, (safe(s)/flag(f)) -> ";
        cin >> z;
        while (z != 's' && z != 'S' && z != 'f' && z != 'F') {
            cout << "Please enter(safe(s)/flag(f)) -> ";
            cin >> z;
        }
        
        
        cout << endl;


        if (nMoves == 0)
            if (isMine(row, col, mineBoard))
                replaceMine(row, col, mineBoard);

        if (z == 's') {
            if (gameBoard[row][col] == '.' && mineBoard[row][col] == '.') {
                uncoverBoard(gameBoard, mineBoard, row, col, &nMoves);
                if (nMoves == nMovesTotal) {
                    markMines(gameBoard, mineBoard, true);
                    displayBoard(gameBoard);
                    cout << endl << "You won!!! :)" << endl;
                    gameOver = true;
                }
            }
            else if (gameBoard[row][col] == '.' && mineBoard[row][col] == '#') {
                gameBoard[row][col] = '#';
                markMines(gameBoard, mineBoard, false);
                displayBoard(gameBoard);
                cout << endl << "You lost! :(" << endl;
                gameOver = true;
            }
            else {
                cout << "Illegal move. ";
                if (gameBoard[row][col] == 'F')
                    cout << "Cell is a flag. Use f to toggle flag off. ";
                else
                    cout << "Cell is already a number. ";
                cout << endl;
            }
        }
        if (z == 'f') {
            if (gameBoard[row][col] == '.') {
                if (flags != 0) {
                    gameBoard[row][col] = 'F';
                    flags--;
                }
                else {
                    cout << "Illegal move. Too many flags!" << endl;
                }
            }
            else if (gameBoard[row][col] == 'F') {
                gameBoard[row][col] = '.';
                flags++;
            }
            else {
                cout << "Illegal move. Cell is a number. " << endl;
            }
        }
    }
}