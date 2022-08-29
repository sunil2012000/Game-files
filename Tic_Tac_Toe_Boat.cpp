
************* TIC - TAC - TOE MACHINE ****************
*/

#include <iostream> 
#include <string>
using namespace std; 
int human, machine; // player numbers for human and machine
char symbol[3]; // 'X' for player 1, 'O' for player 2
char board[3][3]; // tic-tac-toe board
int cell, prevCell; // current cell, previous cell, respectively, where both moves are made by human
string blockCell, trapCell; // cells machine needs to block to not lose, cells which human needs to block to not lose, respectively
// shows the board
void showBoard() {
    cout << "\n";
    for(int i = 0; i < 3; i ++) {
        for(int j = 0; j < 3; j ++) {
            cout << "| " << board[i][j];
        }
        cout << " |\n--------------\n";
    }
    cout << "\n";
}
// initialises the board
void initialise() {
    for(int i = 0; i < 3; i ++) {
        for(int j = 0; j < 3; j ++) {
            board[i][j] = ' ';
        }
    }
    symbol[1] = 'X';
    symbol[2] = 'O';
}
// shows the instructions
void showInstructions() {
    cout << "Which player do you want to be? 1 or 2: ( Player 1 moves first and has symbol 'X' ! ): ";
    cin >> human;
    machine = (human % 2) + 1;
    cout << endl << "Choose a cell numbered from 1 to 9 as below to play: \n" << endl; 
    for(int i = 0; i < 3; i ++) {
        for(int j = 0; j < 3; j ++) {
            cout << "| " << 3 * i + j + 1;
        }
        cout << " |\n--------------\n";
    }
    cout << endl;
}
// checks if board is full
bool fullBoard() {
	for(int i = 0; i < 3; i  ++) {	
		for(int j = 0; j < 3; j ++) {
			if(board[i][j] == ' ') return false;
		}
	}
	return true;
}
// returns any empty cell of the board
int emptyCell() {
	for(int i = 0; i < 3; i  ++) {	
		for(int j = 0; j < 3; j ++) {
			if(board[i][j] == ' ') return i * 3 + j;
		}
	}
	return 9;
}
// returns the endangered cells
string dangerCell() {
	string cells = "99"; // "99" means no cell is endangered
	// maximum 2 cells can be endangered at a time
	// if 2 cells x and y are endangered, then cells = "xy"
	// if only 1 cell x is endangered, then cells = "x9"
	int i = 0;
	if(board[0][0] == ' ') {
		if(board[0][1] != ' ' && board[0][2] != ' ' && board[0][1] == board[0][2]) cells[i++] = '0';
		if(board[1][0] != ' ' && board[2][0] != ' ' && board[1][0] == board[2][0]) cells[i++] = '0';
		if(board[1][1] != ' ' && board[2][2] != ' ' && board[1][1] == board[2][2]) cells[i++] = '0';
	}
	if(board[0][1] == ' ') {
		if(board[0][0] != ' ' && board[0][2] != ' ' && board[0][0] == board[0][2]) cells[i++] = '1';
		if(board[1][1] != ' ' && board[2][1] != ' ' && board[1][1] == board[2][1]) cells[i++] = '1';
	}
	if(board[0][2] == ' ') {
		if(board[0][0] != ' ' && board[0][1] != ' ' && board[0][0] == board[0][1]) cells[i++] = '2';
		if(board[1][2] != ' ' && board[2][2] != ' ' && board[1][2] == board[2][2]) cells[i++] = '2';
		if(board[1][1] != ' ' && board[2][0] != ' ' && board[1][1] == board[2][0]) cells[i++] = '2';
	}
	if(board[1][0] == ' ') {
		if(board[0][0] != ' ' && board[2][0] != ' ' && board[0][0] == board[2][0]) cells[i++] = '3';
		if(board[1][1] != ' ' && board[1][2] != ' ' && board[1][1] == board[1][2]) cells[i++] = '3';
	}
	if(board[1][1] == ' ') {
		if(board[0][1] != ' ' && board[2][1] != ' ' && board[0][1] == board[2][1]) cells[i++] = '4';
		if(board[1][0] != ' ' && board[1][2] != ' ' && board[1][0] == board[1][2]) cells[i++] = '4';
		if(board[0][0] != ' ' && board[2][2] != ' ' && board[0][0] == board[2][2]) cells[i++] = '4';
		if(board[0][2] != ' ' && board[2][0] != ' ' && board[0][2] == board[2][0]) cells[i++] = '4';
	}
	if(board[1][2] == ' ') {
		if(board[1][0] != ' ' && board[1][1] != ' ' && board[1][0] == board[1][1]) cells[i++] = '5';
		if(board[0][2] != ' ' && board[2][2] != ' ' && board[0][2] == board[2][2]) cells[i++] = '5';
	}
	if(board[2][0] == ' ') {
		if(board[0][0] != ' ' && board[1][0] != ' ' && board[0][0] == board[1][0]) cells[i++] = '6';
		if(board[2][1] != ' ' && board[2][2] != ' ' && board[2][1] == board[2][2]) cells[i++] = '6';
		if(board[1][1] != ' ' && board[0][2] != ' ' && board[1][1] == board[0][2]) cells[i++] = '6';
	}
	if(board[2][1] == ' ') {
		if(board[2][0] != ' ' && board[2][2] != ' ' && board[2][0] == board[2][2]) cells[i++] = '7';
		if(board[0][1] != ' ' && board[1][1] != ' ' && board[0][1] == board[1][1]) cells[i++] = '7';
	}
	if(board[2][2] == ' ') {
		if(board[2][0] != ' ' && board[2][1] != ' ' && board[2][0] == board[2][1]) cells[i++] = '8';
		if(board[0][2] != ' ' && board[1][2] != ' ' && board[0][2] == board[1][2]) cells[i++] = '8';
		if(board[0][0] != ' ' && board[1][1] != ' ' && board[0][0] == board[1][1]) cells[i++] = '8';
	}
	return cells;
}
// fills a cell in board for machine
void fillCell(int cell) {
	int row = cell / 3, col = cell % 3;
	board[row][col] = symbol[machine];
	showBoard();
}
// takes a cell as input for human and fills the cell in board
int enterCell() {
	cout << "Choose a cell: ";
	cin >> cell;
	-- cell;
	int row = cell / 3, col = cell % 3;
	while(board[row][col] != ' ') {
		cout << "The cell you have chosen is occupied! Choose another cell: " ;
		cin >> cell;
		-- cell;
		row = cell / 3, col = cell % 3;
	}
	board[row][col] = symbol[human];
	return cell;
}
// display message when machine wins
void machineWin() { 
    cout << "You lost! \n";
}
// display message when game ends in a draw
void gameTie() {	
    cout << "It is a draw! \n";
}
// play tic-tac-toe
void playTicTacToe() {
	// if machine moves first
	if(human == 2) {
		fillCell(4); // fill center of board
		cell = enterCell();
		// edge cell, then machine wins always
		if(cell == 1 || cell == 3 || cell == 5 || cell == 7) {
			if(cell == 1 || cell == 3) {
				fillCell(8);
				if(cell == 1) {
					cell = enterCell();
					if(cell == 0) {
						fillCell(2);
						cell = enterCell();
						if(cell == 6) {
							fillCell(5);
							machineWin();
						}
						else if(cell == 5) {
							fillCell(6);
							machineWin();
						}
						else {
							fillCell(6);
							machineWin();
						}
					}
					else {
						fillCell(0);
						machineWin();
					}
				}
				else if(cell == 3) {
					cell = enterCell();
					if(cell == 0) {
						fillCell(6);
						cell = enterCell();
						if(cell == 2) {
							fillCell(7);
							machineWin();
						}
						else if(cell == 7) {
							fillCell(2);
							machineWin();
						}
						else {
							fillCell(2);
							machineWin();
						}
					}
					else {
						fillCell(0);
						machineWin();
					}
				}
			}
			else if(cell == 5 || cell == 7) {
				fillCell(0);
				if(cell == 5) {
					cell = enterCell();
					if(cell == 8) {
						fillCell(2);
						cell = enterCell();
						if(cell == 1) {
							fillCell(6);
							machineWin();
						}
						else if(cell == 6) {
							fillCell(1);
							machineWin();
						}
						else {
							fillCell(1);
							machineWin();
						}
					}
					else {
						fillCell(8);
						machineWin();
					}
				}
				else if(cell == 7) {
					cell = enterCell();
					if(cell == 8) {
						fillCell(6);
						cell = enterCell();
						if(cell == 2) {
							fillCell(5);
							machineWin();
						}
						else if(cell == 5) {
							fillCell(2);
							machineWin();
						}
						else {
							fillCell(2);
							machineWin();
						}
					}
					else {
						fillCell(8);
						machineWin();
					}
				}
			}
		}
		// corner cell, then fill opposite corner, either machine wins or draws
		else {
			if(cell == 0 || cell == 2 || cell == 6 || cell == 8) {
				if(cell == 0) {
					fillCell(8);
					cell = enterCell();
					if(cell == 1 || cell == 7) {
						fillCell(2);
						cell = enterCell();
						if(cell == 6) {
							fillCell(5);
							machineWin();
						}
						else if(cell == 5) {
							fillCell(6);
							machineWin();
						}
						else {
							fillCell(6);
							machineWin();
						}
					}
					else if(cell == 3 || cell == 5) {
						fillCell(6);
						cell = enterCell();
						if(cell == 2) {
							fillCell(7);
							machineWin();
						}
						else if(cell == 7) {
							fillCell(2);
							machineWin();
						}
						else {
							fillCell(2);
							machineWin();
						}
					}
					else if(cell == 2) {
						fillCell(1);
						cell = enterCell();
						if(cell == 7) {
							fillCell(5);
							cell = enterCell();
							if(cell == 3) {
								fillCell(6);
								gameTie();
							}
							else {
								fillCell(3);
								machineWin();
							}
						}
						else {
							fillCell(7);
							machineWin();
						}
					}
					else if(cell == 6) {
						fillCell(3);
						cell = enterCell();
						if(cell == 5) {
							fillCell(7);
							cell = enterCell();
							if(cell == 2) {
								fillCell(3);
								gameTie();
							}
							else {
								fillCell(2);
								machineWin();
							}
						}
						else {
							fillCell(5);
							machineWin();
						}
					}
				}
				else if(cell == 2) {
					fillCell(6);
					cell = enterCell();
					if(cell == 1 || cell == 7) {
						fillCell(0);
						cell = enterCell();
						if(cell == 8) {
							fillCell(3);
							machineWin();
						}
						else if(cell == 3) {
							fillCell(8);
							machineWin();
						}
						else {
							fillCell(8);
							machineWin();
						}
					}
					else if(cell == 3 || cell == 5) {
						fillCell(8);
						cell = enterCell();
						if(cell == 0) {
							fillCell(7);
							machineWin();
						}
						else if(cell == 7) {
							fillCell(0);
							machineWin();
						}
						else {
							fillCell(0);
							machineWin();
						}
					}
					else if(cell == 0) {
						fillCell(1);
						cell = enterCell();
						if(cell == 7) {
							fillCell(3);
							cell = enterCell();
							if(cell == 5) {
								fillCell(6);
								gameTie();
							}
							else {
								fillCell(5);
								machineWin();
							}
						}
						else {
							fillCell(7);
							machineWin();
						}
					}
					else if(cell == 8) {
						fillCell(5);
						cell = enterCell();
						if(cell == 3) {
							fillCell(7);
							cell = enterCell();
							if(cell == 1) {
								fillCell(0);
								gameTie();
							}
							else {
								fillCell(1);
								machineWin();
							}
						}
						else {
							fillCell(3);
							machineWin();
						}
					}
				}
				else if(cell == 6) {
					fillCell(2);
					cell = enterCell();
					if(cell == 1 || cell == 7) {
						fillCell(8);
						cell = enterCell();
						if(cell == 0) {
							fillCell(5);
							machineWin();
						}
						else if(cell == 5) {
							fillCell(0);
							machineWin();
						}
						else {
							fillCell(0);
							machineWin();
						}
					}
					else if(cell == 3 || cell == 5) {
						fillCell(0);
						cell = enterCell();
						if(cell == 8) {
							fillCell(1);
							machineWin();
						}
						else if(cell == 1) {
							fillCell(8);
							machineWin();
						}
						else {
							fillCell(8);
							machineWin();
						}
					}
					else if(cell == 0) {
						fillCell(3);
						cell = enterCell();
						if(cell == 5) {
							fillCell(1);
							cell = enterCell();
							if(cell == 7) {
								fillCell(8);
								gameTie();
							}
							else {
								fillCell(7);
								machineWin();
							}
						}
						else {
							fillCell(5);
							machineWin();
						}
					}
					else if(cell == 8) {
						fillCell(7);
						cell = enterCell();
						if(cell == 1) {
							fillCell(5);
							cell = enterCell();
							if(cell == 3) {
								fillCell(0);
								gameTie();
							}
							else {
								fillCell(3);
								machineWin();
							}
						}
						else {
							fillCell(1);
							machineWin();
						}
					}
				}
				else if(cell == 8) {
					fillCell(0);
					cell = enterCell();
					if(cell == 1 || cell == 7) {
						fillCell(6);
						cell = enterCell();
						if(cell == 2) {
							fillCell(3);
							machineWin();
						}
						else if(cell == 3) {
							fillCell(2);
							machineWin();
						}
						else {
							fillCell(2);
							machineWin();
						}
					}
					else if(cell == 3 || cell == 5) {
						fillCell(2);
						cell = enterCell();
						if(cell == 6) {
							fillCell(1);
							machineWin();
						}
						else if(cell == 1) {
							fillCell(6);
							machineWin();
						}
						else {
							fillCell(6);
							machineWin();
						}
					}
					else if(cell == 2) {
						fillCell(5);
						cell = enterCell();
						if(cell == 3) {
							fillCell(1);
							cell = enterCell();
							if(cell == 7) {
								fillCell(6);
								gameTie();
							}
							else {
								fillCell(7);
								machineWin();
							}
						}
						else {
							fillCell(3);
							machineWin();
						}
					}
					else if(cell == 6) {
						fillCell(7);
						cell = enterCell();
						if(cell == 1) {
							fillCell(3);
							cell = enterCell();
							if(cell == 5) {
								fillCell(2);
								gameTie();
							}
							else {
								fillCell(5);
								machineWin();
							}
						}
						else {
							fillCell(1);
							machineWin();
						}
					}
				}
			}
		}
	}
	// if human moves first
	else {
		cell = enterCell();
		// center cell, either machine wins or draws
		if(cell == 4) {
			fillCell(0);
			cell = enterCell();
			blockCell = dangerCell();
			if(cell == 8) blockCell[0] = '6';
			while(blockCell[0] != '9') {	
				fillCell(blockCell[0] - '0');
				trapCell = dangerCell();
				cell = enterCell();
				if(cell != (trapCell[0] - '0') && trapCell[0] != '9') {
					fillCell(trapCell[0] - '0');
					machineWin();
					return;
				}
				else if(cell == (trapCell[0] - '0') && trapCell[1] != '9') {
					fillCell(trapCell[1] - '0');
					machineWin();
					return;
				}
				else {
					blockCell = dangerCell();
					if(cell == 8 && blockCell[0] == '9') {
						if(board[2][0] != ' ') break;
						blockCell[0] = '6';
					}
				}
			}
			gameTie();
			return;
		}
		// corner cell
		else if(cell == 0 || cell == 2 || cell == 6 || cell == 8) {
			// machine should occupy center immediately, can win or draw
			fillCell(4);
			prevCell = cell;
			cell = enterCell();
			blockCell = dangerCell();
			if(cell == 8 - prevCell) {
				fillCell(1);
				cell = enterCell();
				if(cell != 7) {
					fillCell(7);
					machineWin();
				}
				else {
					blockCell = dangerCell();
					fillCell(blockCell[0] - '0');
					trapCell = dangerCell();
					cell = enterCell();
					if(cell != trapCell[0] - '0') {
						fillCell(trapCell[0] - '0');
						machineWin();
					}
					else {
						blockCell = dangerCell();
						fillCell(blockCell[0] - '0');
						cell = enterCell();
						gameTie();
					}
				}
			}
			else if(blockCell[0] != '9') {
				while(blockCell[0] != '9') {	
					fillCell(blockCell[0] - '0');
					trapCell = dangerCell();
					cell = enterCell();
					if(cell != (trapCell[0] - '0')) {
						fillCell(trapCell[0] - '0');
						machineWin();
						return;
					}
					blockCell = dangerCell();
				}
				fillCell(8 - prevCell);
				cell = enterCell();
				if(fullBoard()) {
					gameTie();
					return;
				}
				blockCell = dangerCell();
				if(blockCell[0] != '9') {
					fillCell(blockCell[0] - '0');
					cell = enterCell();
					gameTie();
					return;
				}
				fillCell(emptyCell());
				cell = enterCell();
				gameTie();
				return;
			}
			else {
				fillCell(8 - prevCell);
				cell = enterCell();
				blockCell = dangerCell();
				if(blockCell[0] != '9') {
					fillCell(blockCell[0] - '0');
					trapCell = dangerCell();
					cell = enterCell();
					if(trapCell[0] != '9') {
						if(cell != trapCell[0] - '0') {
							fillCell(trapCell[0] - '0');
							machineWin();
							return;
						}
						blockCell = dangerCell();
						if(blockCell[0] == '9') fillCell(emptyCell());
						else fillCell(blockCell[0] - '0');
						cell = enterCell();
						gameTie();
						return;
					}
					blockCell = dangerCell();
					if(blockCell[0] == '9') {
						fillCell(emptyCell());
						cell = enterCell();
						gameTie();
						return;
					}
					fillCell(blockCell[0] - '0');
					cell = enterCell();
					gameTie();
					return;
				}
				fillCell(emptyCell());
				trapCell = dangerCell();
				cell = enterCell();
				if(trapCell[0] != '9') {	
					if(cell != trapCell[0] - '0') {	
						fillCell(trapCell[0] - '0');
						machineWin();
						return;
					}
					blockCell = dangerCell();
					fillCell(blockCell[0] - '0');
					cell = enterCell();
					gameTie();
					return;
				}
				blockCell = dangerCell();
				if(blockCell[0] == '9') fillCell(emptyCell());
				else fillCell(blockCell[0] - '0');
				cell = enterCell();
				gameTie();
				return;			
			}
			
		}
		// edge cell
		else if(cell == 1 || cell == 3 || cell == 5 || cell == 7) {
			// machine should occupy center immediately
			fillCell(4);
			prevCell = cell;
			cell = enterCell();
			// if human gives diametrically opposite cell, machine wins, else either win or draw
			if(cell == 8 - prevCell) {
				fillCell(0);
				trapCell = dangerCell();
				cell = enterCell();
				if(cell == trapCell[0] - '0') {
					blockCell = dangerCell();
					fillCell(blockCell[0] - '0');
					trapCell = dangerCell();
					cell = enterCell();
					if(cell == trapCell[0] - '0') {
						fillCell(trapCell[1] - '0');
						machineWin();
						return;
					}
					else {
						fillCell(trapCell[0] - '0');
						machineWin();
						return;
					}
				}
				else {
					fillCell(trapCell[0] - '0');
					machineWin();
					return;
				}
			}
			else {
				blockCell = dangerCell();
				if(blockCell[0] != '9') {
					while(blockCell[0] != '9') {	
						fillCell(blockCell[0] - '0');
						trapCell = dangerCell();
						cell = enterCell();
						if(cell != (trapCell[0] - '0')) {
							fillCell(trapCell[0] - '0');
							machineWin();
							return;
						}
						blockCell = dangerCell();
					}
					fillCell(8 - prevCell);
					cell = enterCell();
					gameTie();
				}
				else {
					if(prevCell < 4) {
						if(cell == 8) {
							if(prevCell == 1) fillCell(2);
							else if(prevCell == 3) fillCell(6);
						}
						else fillCell(0);
					}
					else {
						if(cell == 0) {
							if(prevCell == 7) fillCell(6);
							else if(prevCell == 5) fillCell(2);
						}
						else fillCell(8);
					}
					trapCell = dangerCell();
					cell = enterCell();
					if(cell != trapCell[0] - '0') {
						fillCell(trapCell[0] - '0');
						machineWin();
						return;
					}
					blockCell = dangerCell();
					if(blockCell[0] != '9') {
						fillCell(blockCell[0] - '0');
						cell = enterCell();
						blockCell = dangerCell();
						if(blockCell[0] != '9') {
							fillCell(blockCell[0] - '0');
							cell = enterCell();
							gameTie();
							return;
						}
						fillCell(emptyCell());
						cell = enterCell();
						gameTie();
						return;
					}
					else {
						fillCell(emptyCell());
						trapCell = dangerCell();
						cell = enterCell();
						if(trapCell[0] != '9') {
							if(cell != trapCell[0] - '0') {
								fillCell(trapCell[0] - '0');
								machineWin();
								return;
							}
							blockCell = dangerCell();
							fillCell(blockCell[0] - '0');
							cell = enterCell();
							gameTie();
							return;
						}
						blockCell = dangerCell();
						if(blockCell[0] != 9) {
							fillCell(blockCell[0] - '0');
							cell = enterCell();
							gameTie();
							return;
						}
						fillCell(emptyCell());
						cell = enterCell();
						gameTie();
						return;
					}
							
				}
			}
		}
	}
} 
int main() { 
	cout << endl << "Hi! Welcome to TicTacToe! Play the game optimally as machine never loses and wins whenever possible!" << endl << endl;
	cout << "Press 'Y' to start the game: ";
	char play;
	cin >> play;
    while(play == 'Y') {
    	cout << endl << "##########################################################################################################################" << endl << endl;
        showInstructions();
        initialise();
        playTicTacToe();
        cout << endl << "Do you want to play another game of Tic-Tac-Toe? Press 'Y' for YES and 'N' for NO: ";
        cin >> play;
    }
    cout << endl << "Thank You for playing! \n" << endl;
}
