/*Alan Singleton
William Watson
CSC 425
11/26/2015
*/

#ifndef _BOARD_H
#define _BOARD_H

#include <iostream> // used for input and output
#include <string> // used for string functions
#include <ctime> // used to seed rand()
#include <algorithm> // used for the sort
#include <vector> // used for the vectors
using namespace std;

class Board {
public:
	Board() : _board("") {} // constructor

	bool processGuess(string, string); // processes the guess, and determines if it is correct
	void printBoard(); // prints out the answers
	string getPlayerGuess(); // takes the player's guess
	int getP(); // gets the number of correct positions
	int getC(); // gets the number of correct colors in the incorrect positions
	void incP(); // increments the number of correct positions
	void incC(); // increments the number of correct colors in the incorrect positions
	void eraseP(); // resets the number of correct positions
	void eraseC(); // resets the number of incorrect positions
private:
	string _board; // the board for strings
	int _colorsInRightSpot; // int variable for correct position
	int _colorsInWrongSpot; // int variable for colors in incorrect position
};

#endif