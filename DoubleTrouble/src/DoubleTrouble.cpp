/* Maylee Gagnon
 * CS 2223 HW1 Double Trouble
 * 10.24.2019
 * C/C++ project, C++ managed build, Hello world C++ project (template)
 */

#include <iostream>
#include <cctype>
using namespace std;

int numG;
int numY;
int numO;
int numLeft;
bool isCPUturn;

void printBoard(){
	for (int i = 0; i < numG; i ++) {
		cout << "G ";
	}
	cout << endl;
	for (int i = 0; i < numY; i ++) {
		cout << "Y ";
	}
	cout << endl;
	for (int i = 0; i < numO; i ++) {
		cout << "O ";
	}
	cout << endl;
}

/** Takes away the appropriate pieces, prints the updated board, checks if winner
 *  @param color Which color group to take from G Y, O
 *  @param num How many pieces from the group to take away [1,numAvailable]
 *  return True if the last piece removed aka there's a winner. False otherwise
 */
bool updateBoard(char color, int num){
	if (color == 'G'){
		numG = numG - num;
	}
	else if (color == 'Y'){
		numY = numY - num;
	}
	else {
		numO = numO - num;
	}

	printBoard();

	if (numG == 0 && numY == 0 && numO == 0){
		return true;
	}
	return false;
}

/*
 * return True if player made a winning move. False otherwise
 */
bool playerTurn() {
	bool selectingColor = true;
	bool selectingNum = true;
	char color;
	int num;
	while (selectingColor){
		cout << "enter color (G, Y, O)" << endl;
		cin >> color;
		color = toupper(color);

		if (color != 'G' && color != 'Y' && color != 'O') {
			cout << "invalid color. Try again" << endl;
		}
		else {
			selectingColor = false;
		}
	}

	while (selectingNum){
		cout << "enter number of pieces" << endl;
		cin >> num;
		if (color == 'G') {
			if (num <= numG && num > 0) {
				selectingNum = false;
			}
			else {
				cout << "invalid amount. Must be >=1 and <= number available. Try again" << endl;
			}
		}
		else if (color == 'Y'){
			if (num <= numY && num > 0) {
				selectingNum = false;
			}
			else {
				cout << "invalid amount. Must be >=1 and <= number available. Try again" << endl;
			}
		}
		else {
			if (num <= numO && num > 0) {
				selectingNum = false;
			}
			else {
				cout << "invalid amount. Must be >=1 and <= number available. Try again" << endl;
			}
		}
	}
	//cout << "color: " << color << " num: " << num;
	return updateBoard(color, num);
}

bool cpuTurn(){
	return false;
	//take away piece(s)
	//return updateBoard(color, num);
}

int main() {
	cout << "main" << endl;

	cout << "enter '1' for player first and '2' for cpu first" << endl;
	int first;
	cin >> first;
	if (first != 1 && first != 2) {
		cout << "invalid input exiting" << endl;
		return 0;
	}
	if (first == 1){
		isCPUturn = false;
	}
	else {
		isCPUturn = true;
	}
	numG = 3;
	numY = 7;
	numO = 5;
	numLeft = 15; // when numLeft = 0 then all of the pieces have been taken, whose ever turn it happening when this happens wins
	printBoard();
	bool stillPlaying = true;

	while (stillPlaying){
		if (isCPUturn){
			//cout << "cpu turn" << endl;
			if (cpuTurn()){
				stillPlaying = false;
				cout << "CPU Won!" << endl;
			}
			else {
				isCPUturn = false;
			}
		}
		else {
			//cout << "player turn" << endl;
			if (playerTurn()) {
				stillPlaying = false;
				cout << "Player Won!" << endl;
			}
			else {
				isCPUturn = true;
			}
		}
	}
	return 0;
}
