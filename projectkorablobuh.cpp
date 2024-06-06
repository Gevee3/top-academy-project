#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 10;
const char EMPTY = '.';
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';

typedef vector<vector<char>> Board;

Board createBoard() {
    setlocale(LC_ALL, "RUS");
    return Board(SIZE, vector<char>(SIZE, EMPTY));
}

void displayBoard(const Board& board) {
    setlocale(LC_ALL, "RUS");
    cout << "  ";
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool placeShip(Board& board, int x, int y, int length, char direction) {
    setlocale(LC_ALL, "RUS");
    if (direction == 'H') {
        if (y + length > SIZE) return false;
        for (int i = 0; i < length; i++) {
            if (board[x][y + i] != EMPTY) return false;
        }
        for (int i = 0; i < length; i++) {
            board[x][y + i] = SHIP;
        }
    }
    else if (direction == 'V') {
        if (x + length > SIZE) return false;
        for (int i = 0; i < length; i++) {
            if (board[x + i][y] != EMPTY) return false;
        }
        for (int i = 0; i < length; i++) {
            board[x + i][y] = SHIP;
        }
    }
    else {
        return false;
    }
    return true;
}

bool attack(Board& board, int x, int y) {
    setlocale(LC_ALL, "RUS");
    if (board[x][y] == SHIP) {
        board[x][y] = HIT;
        return true;
    }
    else if (board[x][y] == EMPTY) {
        board[x][y] = MISS;
        return false;
    }
    return false;
}

bool allShipsSunk(const Board& board) {
    setlocale(LC_ALL, "RUS");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == SHIP) {
                return false;
            }
        }
    }
    return true;
}

void placeShips(Board& board) {
    setlocale(LC_ALL, "RUS");
    int x, y, length;
    char direction;
    for (int i = 0; i < 5; i++) {
        bool placed = false;
        while (!placed) {
            displayBoard(board);
            cout << "Введите координаты (x y), длину и направление (H/V) для корабля " << i + 1 << ": ";
            cin >> x >> y >> length >> direction;
            if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || (direction != 'H' && direction != 'V')) {
                cout << "Неверные координаты или направление, попробуйте снова." << endl;
                continue;
            }
            placed = placeShip(board, x, y, length, direction);
            if (!placed) {
                cout << "Неверная позиция, попробуйте снова." << endl;
            }
        }
    }
}

void computerPlaceShips(Board& board) {
    setlocale(LC_ALL, "RUS");
    int x, y, length;
    char direction;
    for (int i = 0; i < 5; i++) {
        bool placed = false;
        while (!placed) {
            x = rand() % SIZE;
            y = rand() % SIZE;
            length = rand() % 3 + 2; // Длина корабля от 2 до 4
            direction = rand() % 2 == 0 ? 'H' : 'V';
            placed = placeShip(board, x, y, length, direction);
        }
    }
}

void playGame(Board& player1Board, Board& player2Board) {
    setlocale(LC_ALL, "RUS");
    int x, y;
    while (true) {
        displayBoard(player2Board);
        cout << "Игрок 1, введите координаты для атаки (x y): ";
        cin >> x >> y;
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            cout << "Неверные координаты, попробуйте снова." << endl;
            continue;
        }
        if (attack(player2Board, x, y)) {
            cout << "Попадание!" << endl;
        }
        else {
            cout << "Мимо!" << endl;
        }
        if (allShipsSunk(player2Board)) {
            cout << "Игрок 1 выиграл!" << endl;
            break;
        }

        displayBoard(player1Board);
        cout << "Игрок 2, введите координаты для атаки (x y): ";
        cin >> x >> y;
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            cout << "Неверные координаты, попробуйте снова." << endl;
            continue;
        }
        if (attack(player1Board, x, y)) {
            cout << "Попадание!" << endl;
        }
        else {
            cout << "Мимо!" << endl;
        }


        if (allShipsSunk(player1Board)) {
            cout << "Игрок 2 выиграл!" << endl;
            break;
        }
    }
}

void playGameWithComputer(Board& playerBoard, Board& computerBoard) {
    setlocale(LC_ALL, "RUS");
    int x, y;
    while (true) {
        // Игрок атакует
        cout << "Ваше поле:" << endl;
        displayBoard(playerBoard);
        cout << "Игрок, введите координаты для атаки (x y): ";
        cin >> x >> y;
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            cout << "Неверные координаты, попробуйте снова." << endl;
            continue;
        }
        if (attack(computerBoard, x, y)) {
            cout << "Попадание!" << endl;
        }
        else {
            cout << "Мимо!" << endl;
        }
        if (allShipsSunk(computerBoard)) {
            cout << "Игрок выиграл!" << endl;
            break;
        }

        // Компьютер атакует
        x = rand() % SIZE;
        y = rand() % SIZE;
        cout << "Компьютер атакует координаты (" << x << ", " << y << ")!" << endl;
        if (attack(playerBoard, x, y)) {
            cout << "Компьютер попал по координатам (" << x << ", " << y << ")!" << endl;
        }
        else {
            cout << "Компьютер промахнулся по координатам (" << x << ", " << y << ")!" << endl;
        }
        if (allShipsSunk(playerBoard)) {
            cout << "Компьютер выиграл!" << endl;
            break;
        }
    }
}


int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(0));
    Board player1Board, player2Board;
    int mode;

    cout << "Выберите режим игры:" << endl;
    cout << "1. Игрок против игрока" << endl;
    cout << "2. Игрок против компьютера" << endl;
    cout << "Введите ваш выбор: ";
    cin >> mode;

    if (mode == 1) {
        player1Board = createBoard();
        player2Board = createBoard();

        cout << "Игрок 1, разместите ваши корабли." << endl;
        placeShips(player1Board);

        cout << "Игрок 2, разместите ваши корабли." << endl;
        placeShips(player2Board);

        playGame(player1Board, player2Board);
    }
    else if (mode == 2) {
        player1Board = createBoard();
        player2Board = createBoard();

        cout << "Игрок, разместите ваши корабли." << endl;
        placeShips(player1Board);

        cout << "Компьютер размещает корабли..." << endl;
        computerPlaceShips(player2Board);

        playGameWithComputer(player1Board, player2Board);
    }
    else {
        cout << "Выбран неверный режим!" << endl;
    }

    return 0;
}
