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
	for (int i = 0; i < numY; i++) {
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
		color = toupper(color);

		if (color != 'G' && color != 'Y' && color != 'O') {
			cout << "invalid color. Try again" << endl;
		}
		if ((color == 'G' && numG <=0 ) || (color == 'Y' && numY <=0 ) || (color == 'O' && numO <=0 )) {
			cout << "invalid color. No pieces left of that color. Try again" << endl;
		}
		else {
			selectingColor = false;
		}
	}

	while (selectingNum){
		cout << "enter number of pieces" << endl;
		cin >> num;
		if ((num <= 0) || (color == 'G' && num > numG) || (color == 'Y' && num > numY) || (color == 'O' && num > numO)) {
				cout << "invalid amount. Range is [1,number available of color]. Try again" << endl;
		}
		else {
			selectingNum = false ;
		}
	} // end while(selectingNum)
	cout << "Player " << color << " " << num << endl;
	return updateBoard(color, num);
}

int randAmount(int max){
	//return (rand() % (max + 1 - 1))+1;
	return rand() % max +1; // [1,max]
}

/* Checks to see if win is possible, if yes picks the move to win, if not picks randomly
 *  Returns True if CPU made a winning move. False otherwise
 */
bool cpuTurn(){
	bool winPossible;
	char color;
	int num;

	winPossible = false;
	/*
	int xorResult = numG ^ numY ^ numO;
	if (xorResult == 0){
		winPossible == false;
	}
	else {
		winPossible = true;
	}
	*/

	if (winPossible){
		// TODO IMPLEMENT follow strategy and find on that results in xor == 0
	}

	else { //random    //TODO FIX 1, g3, gets stuck in an infinite while loop, picks 2 for the color Yellow
		bool pickingColor = true;

		while (pickingColor){ // pick random color, if pieces available picks random number of them
			int randNumColor = randAmount(3); // randomly pick 1,2,or 3
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
		} // end while()
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
	//srand(time(0)); changes the seed, which means different set of random numbers every time program is run, commented for testing purposes

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
	}
	return 0;
}
