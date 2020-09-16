#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//const variables
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NONE = 'N';

//function creations
void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int compMove(vector<char> board, char comp);
void announceWinner(char winner, char computer, char human);

//main function
int main() {
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);

	instructions();
	char human = humanPiece();
	char comp = opponent(human);
	char turn = X;
	displayBoard(board);

	while (winner(board) == NONE)
	{
		if (turn == human)
		{
			move = humanMove(board, human);
			board[move] = human;
		}
		else
		{
			move = compMove(board, comp);
			board[move] = comp;
		}
		displayBoard(board);	//displays board after every move
		turn = opponent(turn);	//switches turn
	}

	announceWinner(winner(board), comp, human);

	return 0;
}

void instructions() {
	cout << "Welcome to the greatest game of Tic-Tac-Toe you will ever play.\n";
	cout << "Where your puny human brain will go against the greatest mind you will never comprehend.\n\n";

	cout << "Make your move by entering a number 0-8.The number corresponds to a position on the board as shown below.\n\n";

	cout << " 0 | 1 | 2\n";
	cout << " ----------\n";
	cout << " 3 | 4 | 5\n";
	cout << " ----------\n";
	cout << " 6 | 7 | 8\n\n";

	cout << "Prepare your mind human, for it will be blown like my circuits. Wait.\n";
	cout << "Stop laughing, prepare the battleground!\n\n";
}

char askYesNo(string question) {
	char response;
	do {
		cout << question << "y/n: ";
		cin >> response;
	} while (response != 'y' && response != 'n');

	return response;
}

int askNumber(string question, int high, int low) {
	int number;
	do {
		cout << question << " (" << low << " - " << high << "): ";
		cin >> number;
	} while (number > high || number < low);

	return number;
}

char humanPiece() {
	char goFirst = askYesNo("Does the poor human desire the first move? ");
	if (goFirst == 'y') {
		cout << "\nThen take the first move. We all know you need it.\n";
		return X;
	}
	else {
		cout << "\nHow brave. I will commend you for being so dumb. I will go first.\n";
		return O;
	}
}

char opponent(char piece) {
	if (piece == X)
		return O;
	else
		return X;
}

void displayBoard(const vector<char>& board) {
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t----------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t----------";
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\n";
}

char winner(const vector<char>& board) {
	//possible winning rows
	const int WinningRows[8][3] = {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{0, 3, 6},
		{1, 4, 7},
		{2, 5, 8},
		{0, 4, 8},
		{2, 4, 6}
	};

	const int TotalWinningRows = 8;

	//if any row has values matching the WinningRows array and it's not empty, then there is a winner
	for (int i = 0; i < TotalWinningRows; i++) {
		if ((board[WinningRows[i][0]] != EMPTY) &&
			(board[WinningRows[i][0]] == board[WinningRows[i][1]]) &&
			(board[WinningRows[i][1]] == board[WinningRows[i][2]]))
		{
			return board[WinningRows[i][0]];
		};
	}

	//if nobody has won, then check for a tie
	//this uses the count() function in algorithm library
	if (count(board.begin(), board.end(), EMPTY) == 0)
		return TIE;

	//since no one has won, the the game isn't over, return NONE
	return NONE;
}

inline bool isLegal(const vector<char>& board, int move) {
	return (board[move] == EMPTY);
}

int humanMove(const vector<char>& board, char human) {
	int move = askNumber("Where will you move?", (board.size() - 1));
	while (!isLegal(board, move)) {
		cout << "\nThat square is occupied foolish human.\n";
		move = askNumber("Where will you move?", (board.size() - 1));
	}

	cout << "Fine...\n";

	return move;
}

int compMove(vector<char> board, char comp)
{
	unsigned int move = O;
	bool found = false;

	//If computer can win on next move, then make that move
	while (!found && move < board.size()) {
		if (isLegal(board, move)) {
			board[move] = comp;
			found = winner(board) == comp;
			board[move] = EMPTY;
		}

		if (!found)
			move++;
	}

	//If human can win on next move, block that move
	if (!found) {
		move = O;
		char human = opponent(comp);

		while (!found && move < board.size()) {
			if (isLegal(board, move)) {
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}

			if (!found)
				move++;
		}
	}

	//Otherwise move to the next best open square
	if (!found) {
		move = O;
		unsigned int i = 0;

		const int bestMoves[] = { 4,0,2,6,8,1,3,5,7 };
		//pick next best open square
		while (!found && i < board.size()) {
			move = bestMoves[i];
			if (isLegal(board, move))
				found = true;
			i++;
		}
	}

	cout << "I shall take square number " << move << endl << endl;
	return move;
}

void announceWinner(char winner, char comp, char human) {
	if (winner == comp) {
		cout << winner << "'s won!\n";
		cout << "As I predicted human, your tiny brain cannot handle my computer genius!\n";
	}
	else if (winner == human) {
		cout << winner << "'s won!\n";
		cout << "It cannot be! You cheated puny human. But this will never happen again!\n";
	}
	else {
		cout << "It's a tie.\n";
		cout << "Heh. We tied. You were very lucky human. Cherish this moment for you will never be better than me.\n";
	}
}