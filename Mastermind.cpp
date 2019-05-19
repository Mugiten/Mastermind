#include "Board.h"

void player(int &); // player function, used for the player
void computer(int &); // computer function, used for the computer
void game(); // game function, used for the game
string generateCode(); // generates the code at random
void initPop(vector<string> &); // initializes the population
string crossover(string, string); // crossover function, takes two parent codes from parents and creates a new child
string mutate(string); // mutate function, takes a child and mutates code.
string inversion(string); // takes two positions, and flips the code.


int main() {
	srand(time(NULL)); // create the seed for the rand function
	game(); // game function
	system("PAUSE"); // pauses the system
	return 0;
}

void game() {
	int cmoves, pmoves; // intialize the computer moves, and the player moves.
	computer(cmoves); // calls the player function
	player(pmoves); // calls the computer function
	cout << "The computer guessed correctly in " << cmoves << " moves" << endl; // prints out the number of moves the computer used
	cout << "The player guessed correctly in " << pmoves << " moves" << endl; // prints out the number of moves the player used
}

void player(int &moves) {
	Board board; // creates a board object
	string code = generateCode(); // generates the solution
	bool gameover = false; // gameover is initialized as false
	moves = 0; // moves initialized to 0
	string guess = ""; // guess initialized to blank
	cout << "Available colors: R, Y, B, G, O, V" << endl;
	while (!gameover) { // while gameover is false, keep going.
		guess = board.getPlayerGuess(); // get the player's guess
		moves++; // increment the move
		gameover = board.processGuess(guess, code); // test to see if guess is correct
		board.printBoard(); // prints out the board
	} 
}

void computer(int &moves) {
	Board board, board2; // creates 2 board objects
	moves = 1; // initializes moves to 1.
	int p = 0, c = 0, p2 = 0, c2 = 0, num = 0; // intializes ints to be used for the getP and getC method
	string code = generateCode(); // generate the code.
	string root = "RRBY"; // create a root guess
	bool gameover = board.processGuess(root, code); // check if the root guess is correct
	p = board.getP(); // getP
	c = board.getC(); // getC
	vector <pair<int, string>> child, forb; // initialize the child vectors and the forbidden vector
	vector <string> pop; // intialize the population vector
	initPop(pop); // generates the initial population
	while (!gameover) { // while gameover is false, continue.
		string cts = "", cts2 = "", cts3 = ""; // intializes the computer temp strings
		bool elig = true, used = false; // initiliazes the elig and used bool varirables
		child.clear(); // clears the child vector
		for (int x = 0; x < 100; x++) { // for loop goes to a hundred times minimum to add to child vector
			num = rand() % pop.size(); // gets a random number from the population vector
			cts = pop.at(num); // gets a string from the population vector.
			cts3 = crossover(root, cts); // crossover with the root and the population vector.
			cts2 = mutate(cts3); // has a 3% chance to mutate
			cts = inversion(cts2); // has a 3% chance to inverse
			board2.processGuess(cts, root); // since we do cannot guess the code, we do the next best thing and take our guess and compare it.
			p2 = board2.getP(); // we take the P from the our guess of the guess.
			c2 = board2.getC(); // we take the C from the the guess of our guess.
			int fit = (p + c) - (c2 + p2); // we calculate the fitness function, which must proportional to the P and C value of our guess from the real code.
			if (child.size() != 0) { // if child size is not equal to 0.
				for (int x = 0; x < child.size(); x++) { // then go in a for loop and
					if (child.at(x).second == cts) { // check to see if the cts is in the child
						elig = false; // if it is then eligible is false.
					}
				}
			}
			if (forb.size() != 0) { // if forbidden is not zero
				for (int x = 0; x < forb.size(); x++) { // then go in a for loop through the forbidden vector
					if (forb.at(x).second == cts) { // check to see if cts is in the forbidden vector
						used = true; //  if it is, then used is true.
					}
				}
			}
			if (elig == true && used == false && fit == 0) { // to enter into child, the string must be true of three things, it must be eligible, it must not have been used, and the fit funciton must be 0.
				child.push_back(make_pair(fit, cts));
			}
		}
		if (child.size() != 0) { // if child size is not 0, then do
			num = rand() % child.size(); // get a random number within the size of the child vector. Each has a proportional chance of being picked, because they were proportional to the P and C's of the original root guess.
			gameover = board.processGuess(child.at(num).second, code); //  process the guess chosen.
			p = board.getP(); // get the new P
			c = board.getC(); // get the new C
			forb.push_back(make_pair(p + c, child.at(num).second)); // add it to the forbidden vector, so it will not be used again.
			sort(forb.begin(), forb.end()); // sort the forbidden vector.
			root = forb.at(forb.size() - 1).second; // the value with the highest P and C value will be the root.
			board.printBoard(); // print out the board
			moves += 1; // increment the moves done.
		}
	}
}

string generateCode() { // generates the code randomly
	int num = 0; // num to be used for a random number
	string colors[6] = { "R", "Y", "B", "G", "O", "V" }; // array of colors available.
	string code = ""; // initliaze the string code.
	for (int x = 0; x < 4; x++) { // for loop goes through 4 times and randomly selects the colors.
		num = rand() % 6; // randomly selects a number propotional to the size of the color array
		code = code + colors[num]; // selects a color and adds it the code string.
	}
	return code; // returns the code
}

void initPop(vector<string> &pop) { // initializes the population
	string init = ""; // initializes the string
	bool uniq; // create a bool variable.
	for (int x = 0; x < 150; x++) { 
		uniq = true; // uniq is put as false
		init = generateCode(); // generate a code
		for (int y = 0; y < pop.size(); y++) { // if the init is in pop, then the bool unique is false;
			if (init == pop.at(y))
				uniq = false;
		}
		if (uniq == true) // if the string init is uniq, then it is put in the population.
			pop.push_back(init);
	}
}

string crossover(string str, string str2) { // takes two strings and crosses the code into an new string.
	string str3 = ""; // initializing a new string
	int prob = rand() % 100; // take a random number between 0-100
	if (prob < 33) { // if prob is below 33 then
		str3 = str2.substr(0, 2); // the str3 takes the first two colors
		str.replace(0, 2, str3); // replaces the first two from the first string
		return str; // and returns it
	}
	else if (prob > 33 && prob < 66) { // if the prob is between 33 and 66
		str3 = str2.substr(1, 2); // then str takes the second and third colors
		str.replace(1, 2, str3); // replaces it in the same position
		return str; // and return it.
	}
	else { // else
		str3 = str2.substr(2, 2); // str3 takes the last two colros
		str.replace(2, 2, str3); // replaces it in the string in the same position
		return str; // and returns it.
	}
}

string mutate(string str) {// mutates the string
	string mut = ""; // initializes the string mut
	int prob = rand() & 100; // get a random number between 0-100
	if (prob < 3) { // if the prob is 3 or less than
		string colors[6] = { "R", "Y", "B", "G", "O", "V" };
		string mut = colors[rand() % 6]; // get a random number from the color array, and 
		str.replace(rand() % 4, 1, mut); // replace it randomly in the 4 colors
	}
	return str; // return the string
}

string inversion(string str) { // takes a position and inverses the string
	int prob = rand() % 100; // initialize the probability int, and gets a number between 0-100
	if (prob < 3) { // if the prob is 3 or less then
		string flip = "", sstr = ""; // create two strings, flip and sstr
		int prob2 = rand() % 100; //get another probability
		if (prob2 < 16) { // if the probability is less than 16
			for (int x = str.size() - 1; x >= 0; x--) { // then do a for loop and flip the string
				flip = flip + str.at(x);
			}
			str = flip; // str is then equal to flip.
		}
		else if (prob2 > 16 && prob2 < 33) { // else if the prob is between 16 and 33
			sstr = str.substr(0, 3); // create a substring between 0-3
			for (int x = sstr.size() - 1; x >= 0; x--) { // for the size of the sstr string
				flip = flip + sstr.at(x); // flip the sstr 
			}
			str.replace(0, 3, flip); // replace the string
		}
		else if (prob2 > 33 && prob2 < 50) { // else if the prob is between 33 - 50
			sstr = str.substr(0, 2); // take the substring between 0 - 2 
			for (int x = sstr.size() - 1; x >= 0; x--) { // for the size of the sstr string
				flip = flip + sstr.at(x); // flip it
			}
			str.replace(0, 2, flip); // replace it in the string
		}
		else if (prob2 > 50 && prob2 < 67) { // else if the prob is between 50 - 67
			sstr = str.substr(1, 3); // take the substring between 1-4
			for (int x = sstr.size() - 1; x >= 0; x--) { // for the size of the sstr string
				flip = flip + sstr.at(x); // flip the string
			}
			str.replace(1, 3, flip); // replace it
		}
		else if (prob2 > 67 && prob2 < 84) { // else if the prob is between 67 - 84
			sstr = str.substr(1, 2); // get the string between 1 - 2
			for (int x = sstr.size() - 1; x >= 0; x--) { // for the size of the sstr
				flip = flip + sstr.at(x); // flip the string
			}
			str.replace(1, 2, flip); // replace the string with the flip string
		}
		else { // else
			sstr = str.substr(2, 2);  // get a substring between 2-4
			for (int x = sstr.size() - 1; x >= 0; x--) { // for the size of the sstr
				flip = flip + sstr.at(x); // flip it
			}
			str.replace(2, 2, flip); // and replace the string in that position with flip
		}
	}
	return str; // return the string
}