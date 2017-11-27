#include <iostream>

using namespace std;

const int MAX_ARRAY_SIZE = 18;
const int MIN_ARRAY_SIZE = 8;
const int MAX_PIECES = 72;
const int NOPLAYER = 0;
const int WHITEWINS = 1;
const int REDWINS = 2;
const int NOONEWINS = 0;
const int WHITESOLDIER = 1;
const int WHITEMULE = 2;
const int WHITEKING = 3;
const int REDSOLDIER = 4;
const int REDMULE = 5;
const int REDKING = 6;
const int WHITEPLAYER = 1;
const int REDPLAYER = 2;

void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard);

void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard);

int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex);

int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLoc, int yLoc);

bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int xLoc, int yLoc);

bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
	int numRowsInBoard, int player, int fromSquareNum,
	int toSquareNum, bool &jumped);

bool isEven(int value);

int main() {

	int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { 0 };

	int xIndicesMove[MAX_PIECES] = { 0 };
	int xIndicesJump[MAX_PIECES] = { 0 };
	int yIndicesMove[MAX_PIECES] = { 0 };
	int yIndicesJump[MAX_PIECES] = { 0 };

	const int MAX_BOARDSIZE_TRIES = 3;

	int numRowsInBoard = 0;

	for (int i = 0; i < MAX_BOARDSIZE_TRIES; i++)
	{

		cout << "Enter the number of squares along each edge of board\n";
		
		if (!(cin >> numRowsInBoard)) {
			numRowsInBoard = 0;
			cin.clear();
			cin.ignore();
			cout << "ERROR:  Board size is not an integer\n";
		} else {
			if (numRowsInBoard < MIN_ARRAY_SIZE) {
				cout << "ERROR:  Board size too small\n";
			} else if (numRowsInBoard > MAX_ARRAY_SIZE) {
				cout << "ERROR:  Board size too large\n";
			} else {
				if (isEven(numRowsInBoard)) {
					break;
				}
				else {
					cout << "ERROR:  Board size odd\n";
				}
			}
		}

		cout << MIN_ARRAY_SIZE << " <= number of squares <= " << MAX_ARRAY_SIZE << endl;

		if (i == MAX_BOARDSIZE_TRIES - 1) {
			cout << "ERROR:  Too many errors entering the size of the board";

			return -1;
		}

	}


	return 0;
}

void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{

}

void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{

}

int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	return 0;
}

bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex)
{
	return false;
}

int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	return 0;
}

bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	return false;
}

bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	return false;
}

bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool & jumped)
{
	return false;
}

// Checks if the value provided is even, if so returns true, else returns false.
bool isEven(int value) {
	if (value % 2 == 0) {
		return true;
	}
	else {
		return false;
	}
}