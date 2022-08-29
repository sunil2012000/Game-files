
/******************* MINE - SWEEPER GAME ***********************/

#include <bits/stdc++.h>
using namespace std;

int SIDE1; // number of rows of the board
int SIDE2; // number of columns of the board
int MINES; // number of mines on the board
int movesLeft; // number of moves left for the player

vector <int> dx = {0, 1, 0, -1, 1, 1, -1, -1}; // for directions along x - axis
vector <int> dy = {1, 0, -1, 0, 1, -1, -1, 1}; // for directions along y - axis

vector <vector <char>> board; // board which the user can see
vector <vector <char>> hboard; // board which is hidden from user 
vector <vector <bool>> vis; // keeps track of visited cells of the user's board

bool isValid(int row, int col) { // Checks whether (row, col) is a valid cell or not
	return row >= 0 && row < SIDE1 && col >= 0 && col < SIDE2;
}
void showBoard() { // prints the board
	cout << endl << "    ";
	for (int j = 0; j < SIDE2; j++) {
		if (j < 9) cout << j << ":| ";
		else cout << j << ":|";
	}
	cout << endl << "   ";
	for (int j = 0; j < SIDE2; j++) {
		cout << "----";
	}
	cout << endl;
	for (int i = 0; i < SIDE1; i ++) {
		cout << i << ":| ";
		for (int j = 0; j < SIDE2; j++) {
			cout << board[i][j] << " | ";
		}
		cout << endl << "   ";
		for (int j = 0; j < SIDE2; j++) {
			cout << "----";
		}
		cout << endl;
	}
	cout << endl;
}
void showhboard() { // prints the hidden board
	cout << endl << "    ";
	for (int j = 0; j < SIDE2; j++) {
		if (j < 9) cout << j << ":| ";
		else cout << j << ":|";
	}
	cout << endl << "   ";
	for (int j = 0; j < SIDE2; j++) {
		cout << "----";
	}
	cout << endl;
	for (int i = 0; i < SIDE1; i ++) {
		cout << i << ":| ";
		for (int j = 0; j < SIDE2; j++) {
			cout << hboard[i][j] << " | ";
		}
		cout << endl << "   ";
		for (int j = 0; j < SIDE2; j++) {
			cout << "----";
		}
		cout << endl;
	}
	cout << endl;
}
pair <int, int> move() { // Player makes a move
	int row, col;
	cout << "Enter a valid empty / flagged cell to move (row, col): ";
	cin >> row >> col;
	while (!isValid(row, col) || !(board[row][col] == ' ' || board[row][col] == 'F')) {
		cout << "The cell you have entered is invalid or is already occupied!" << endl;
		cout << "Enter a valid empty / flagged cell to move (row, col): ";
		cin >> row >> col;
	}
	cout << "Press 'F' to Flag / Unflag and 'O' to Open the cell: ";
	char t;
	cin >> t;
	if (t == 'F') {
		if (board[row][col] == 'F') board[row][col] = ' ';
		else board[row][col] = 'F';
		showBoard();
		pair <int, int> cell = move();
		row = cell.first;
		col = cell.second;
	}
	return {row, col};
}
int countAdjacentMines(int x, int y) { // Counts mines adjacent to (x, y)
	int cnt = 0;
	for (int k = 0; k < 8; k ++) {
		int nx = x + dx[k], ny = y + dy[k];
		cnt += (isValid(nx, ny) && hboard[nx][ny] == 'M');
	}
	return cnt;
}
void placeMines() { // Places mines on the board
	for (int i = 0; i < MINES;) {
		int x = rand() % SIDE1, y = rand() % SIDE2;
		if (hboard[x][y] == ' ') {
			hboard[x][y] = 'M';
			i ++;
		}
	}
}
void getNumbers() { // Populate the hidden board cells with numbers denoting the adjacent mine counts
	for (int i = 0; i < SIDE1; i ++) {
		for (int j = 0; j < SIDE2; j ++) {
			if (hboard[i][j] == ' ') {
				hboard[i][j] = countAdjacentMines(i, j) + '0';
			}
		}
	}
}
void open (int x, int y) { // opens up (x, y) on the board for player
	board[x][y] = hboard[x][y];
	vis[x][y] = 1;
	movesLeft --;
	if (board[x][y] == '0') {
		for (int k = 0; k < 8; k ++) {
			int nx = x + dx[k], ny = y + dy[k];
			if (isValid(nx, ny) && vis[nx][ny] == 0 && hboard[nx][ny] != 'M') {
				open(nx, ny);
			}
		}
	}
}
void playMineSweeper() { // plays the game
	movesLeft = SIDE1 * SIDE2 - MINES;
	while (movesLeft) {
		showBoard();
		pair <int, int> cell = move();
		int row = cell.first, col = cell.second;
		if (hboard[row][col] == 'M') {
			showhboard();
			cout << "Oops! You Lost!" << endl;
			return;
		}
		else {
			open(row, col);
		}
	}
	showhboard();
	cout << "Congratulations! You Won!" << endl;
}
void initialise() { // initialises the game
	cout << "Enter the dimensions of board (number of rows, number of columns): ";
	cin >> SIDE1 >> SIDE2;
	cout << "Enter the number of mines: ";
	cin >> MINES;
	while (SIDE1 * SIDE2 < MINES) {
		cout << "Number of mines has to be less than the size of the board!" << endl;
		cout << "Enter the dimensions of board (number of rows, number of columns): ";
		cin >> SIDE1 >> SIDE2;
		cout << "Enter the number of mines: ";
		cin >> MINES;
	}
	board = hboard = vector <vector <char>> (SIDE1, vector <char> (SIDE2, ' '));
	vis = vector <vector <bool>> (SIDE1, vector <bool> (SIDE2, 0));
	placeMines();
	getNumbers();
}
int main() {
	cout << endl << "Hi! Welcome to MineSweeper! Play the game as per your level by customizing the grid dimensions and number of mines!" << endl << endl;
	cout << "Press 'Y' to start the game and 'N' to quit: ";
	char play;
	cin >> play;
    while (play == 'Y') {
    	cout << endl << "##########################################################################################################################" << endl << endl;
        initialise();
        playMineSweeper();
        cout << endl << "Do you want to play another game of MineSweeper? Press 'Y' for YES and 'N' for NO: ";
        cin >> play;
    }
    cout << endl << "Thank You!" << endl << endl;
}
