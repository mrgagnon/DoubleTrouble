/* Maylee Gagnon
 * CS 2223 HW1 Double Trouble
 * 10.24.2019
 * C/C++ project, C++ managed build, Hello world C++ project (template)
 */

#include <iostream>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
using namespace std;

int numG;
int numY;
int numO;
bool isCPUturn;


void printBoard(){
	for (int i = 0; i < numG; i++) {
		cout << "G ";
	}
	cout << endl;
	//cout << "(" << numG << ")" << endl;
	for (int i = 0; i < numY; i++) {
		cout << "Y ";
	}
	cout << endl;
	//cout << "(" << numY << ")" << endl;
	for (int i = 0; i < numO; i ++) {
		cout << "O ";
	}
	cout << endl;
	//cout << "(" << numO << ")" << endl;
}

/** Takes away the appropriate pieces, prints the updated board, checks if winner
 *  @param color Which color group to take from G Y, O
 *  @param num How many pieces from the group to take away [1,numAvailable]
 *  @return True if the last piece removed aka there's a winner. False otherwise
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

/* Prompts the player to make color and number of pieces for their turn. calls updateBoard
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
		if (cin.good()){
			color = toupper(color);
			if (color != 'G' && color != 'Y' && color != 'O') {
				cout << "invalid color. Try again" << endl;
			}
			else if ((color == 'G' && numG <=0 ) || (color == 'Y' && numY <=0 ) || (color == 'O' && numO <=0 )) {
				cout << "invalid color. No pieces left of that color. Try again" << endl;
			}
			else {
				selectingColor = false;
			}
		}
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "invalid input. Try again" << endl;
		}
	} // end while selecting color

	while (selectingNum){
		cout << "enter number of pieces" << endl;
		cin >> num;
		if (cin.good()){
			if ((num <= 0) || (color == 'G' && num > numG) || (color == 'Y' && num > numY) || (color == 'O' && num > numO)) { //check num in range
				cout << "invalid amount. Range is [1,number available of color]. Try again" << endl;
			}
			else {
				selectingNum = false;
			}
		}
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "invalid input. Try again" << endl;
		}
	} // end while (selectingNum)
	cout << "Player " << color << " " << num << endl;
	return updateBoard(color, num);
}

int randAmount(int max){
	return rand() % max +1; // [1,max]
}

/* @param int i int j int k, the three values to be XORed
 * return false if no move toward a win available. return true if this is a move
 */
bool checkXOR(int i, int j, int k){
	int xorResult = i^j^k;
	if (xorResult == 0){
		return false;
	}
	else {
		return true;
	}
}

/* Checks to see if win is possible, if yes picks the move to win, if not picks randomly.
 * Randomly: picks a random color, if pieces available picks random amount of them else pieces another color
 * @ return True if CPU made a winning move. False otherwise
 */
bool cpuTurn(){
	bool winPossible;
	char color;
	int num;

	winPossible = checkXOR(numG, numY, numO);

	if (winPossible){
		int tempNumG = numG;
		int tempNumY = numY;
		int tempNumO = numO;
		for (int i = 1; i <= numG; i++){
			tempNumG--;
			if (!checkXOR(tempNumG, tempNumY, tempNumO)){ // want board == 0, check XOR returns false is = 0, so !false = true so board = 0
				cout << "CPU G " << i << endl;
				return updateBoard('G',i);
			}
		}
		tempNumG = numG;
		for (int i = 1; i <= numY; i++){
			tempNumY--;
			if (!checkXOR(tempNumG, tempNumY, tempNumO)){
				cout << "CPU Y " << i << endl;
				return updateBoard('Y',i);
			}
		}
		tempNumY = numY;
		for (int i = 1; i <= numO; i++){
			tempNumO--;
			if (!checkXOR(tempNumG, tempNumY, tempNumO)){
				cout << "CPU O " << i << endl;
				return updateBoard('O',i);
			}
		}

	} // end if - strategy possible

	else { // picking randomly
		bool pickingColor = true;

		while (pickingColor){
			int randNumColor = randAmount(3);
			if (randNumColor == 1){
				if (numG >= 1){
					color = 'G';
					pickingColor = false;
					num = randAmount(numG);
				}
			}
			if (randNumColor == 2){
				if (numY >= 1){
					color = 'Y';
					pickingColor = false;
					num = randAmount(numY);
				}
			}
			if (randNumColor == 3){
				if (numO >= 1){
					color = 'O';
					pickingColor = false;
					num = randAmount(numO);
				}
			}
		} // end while(pickingColor)
		cout << "CPU " << color << " " << num << endl;
	} //end else

	return updateBoard(color, num);
}

int main() {
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
	printBoard();
	bool stillPlaying = true;
	srand(time(0)); //changes the seed/changes the random numbers

	while (stillPlaying){
		if (isCPUturn){
			cout << "CPU turn" << endl;
			if (cpuTurn()){
				stillPlaying = false;
				cout << "CPU Won!" << endl;
			}
			else {
				isCPUturn = false;
			}
		}
		else {
			cout << "Player turn" << endl;
			if (playerTurn()) {
				stillPlaying = false;
				cout << "Player Won!" << endl;
			}
			else {
				isCPUturn = true;
			}
		}
	}// end while(stillPlaying)
	return 0;
}
