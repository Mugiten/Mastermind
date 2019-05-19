#include "Board.h"

// takes the computer or player's guess and compares it to the code to see if it is correct.
bool Board::processGuess(string guess, string code){
	eraseC(); // resets the colors in the wrong position
	eraseP(); // resets the colors in the right position
	string result = ""; // initialize the string result
	string gcopy = guess; // creates a copy of the guess
	string ccopy = code; // creates a copy of the code solution 
	for (int x = 0; x < 4; x++) { // for loop that will go through the guess and compare it to code. 
		if (guess.at(x) == code.at(x)) { // checks to see if the same color is in the same position
			result = result + "P"; // if it is, P is added to results
			incP(); // increments the number in the correct place
			code = code.substr(0, x) + "X" + code.substr(x + 1); // changes the code to not be used again
			guess = guess.substr(0, x) + "X" + guess.substr(x + 1); // changes the guess not to be used again
		}
	}
	for (int x = 0; x < 4; x++) { // for loop to go through guess to see if there is a color in the wrong position.
		int location = code.find(guess.at(x)); // finds the location of the color
		if (location != -1 && (guess.at(x) != 'X')) { // as long as the location is not -1 and guess is not X, then go ahead.
			result = result + "C"; // adds C to the result
			incC(); // increments the colors in the wrong position
			code = code.substr(0, location) + "X" + code.substr(location + 1); // adds X to the code to not be used again.
		}
		else if (guess.at(x) != 'X') { // else if the code is not in the correct or incorrect position, add a blank in results.
			result = result + " ";
		}
	}
	_board = gcopy + " " + result; // put the copy of guess to the board
	if (result == "PPPP") { // if the result is equal to 4 Ps, then it is correct, and will return true.
		return true;
	}
	else { // else, it returns false.
		return false;
	}
}
 // prints out the board.
void Board::printBoard(){
	cout << _board << endl;
}

// takes the player's guess, and returns it.
string Board::getPlayerGuess(){
	string input = "";
	cout << "Please enter your guess: " << endl;
	cin >> input;
	return input;
}

// returns the colors in the correct position
int Board::getP(){
	return _colorsInRightSpot;
}

// returns the colors in the incorrect position
int Board::getC(){
	return _colorsInWrongSpot;
}

// increments colors in the correct position
void Board::incP(){
	_colorsInRightSpot += 1;
}

// increments colors in the incorrect position
void Board::incC(){
	_colorsInWrongSpot += 1;
}

// erases colors in the correct position
void Board::eraseP(){
	_colorsInRightSpot = 0;
}

// erases colors in the incorrect position
void Board::eraseC(){
	_colorsInWrongSpot = 0;
}