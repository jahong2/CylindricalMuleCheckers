#include <iostream>
#include <iomanip>
#include <string>

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
const int TABLESPACING = 4;

const string WHITESOLIDER_DISPLAY = "WS";
const string WHITEMULE_DISPLAY = "WM";
const string WHITEKING_DISPLAY = "WK";
const string REDSOLIDER_DISPLAY = "RS";
const string REDMULE_DISPLAY = "RM";
const string REDKING_DISPLAY = "RK";

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

bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

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

	InitializeBoard(myCMCheckersBoard, numRowsInBoard);
	DisplayBoard(myCMCheckersBoard, numRowsInBoard);

	return 0;
}

// IMPLEMENTED: MAX
// This method puts the checkers on the board, initializes it by checking some basic properties of the location.
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{

	int currentRow = 1;
	int noPeicesPositionInitial = (numRowsInBoard / 2);

	for (int i = 0; i < numRowsInBoard; i++)
	{
		for (int j = 0; j < numRowsInBoard; j++)
		{
			
			if (!isEven(currentRow) && isEven(j + (i * 10))) {
				CMCheckersBoard[i][j] = 0;
				continue;
			} else if (isEven(currentRow) && !isEven(j + (i * 10))) {
				CMCheckersBoard[i][j] = 0;
				continue;
			}

			// Since it's gotten to this point, clearly we need to place a checker, let's determine which one.
			//	Unless of course we're in no man's land.

			if (currentRow == 1) { // White mule
				CMCheckersBoard[i][j] = 2;
			}
			else if (currentRow == numRowsInBoard) { // Red Mule
				CMCheckersBoard[i][j] = 5;
			}
			else if (currentRow == noPeicesPositionInitial || currentRow == noPeicesPositionInitial + 1) {
				// Blank rows here.
				CMCheckersBoard[i][j] = 0;
			}
			else if (currentRow < noPeicesPositionInitial) {
				// Place white soldier
				CMCheckersBoard[i][j] = 1;
			}
			else {
				// place red soldier
				CMCheckersBoard[i][j] = 4;
			}


		}
		currentRow++;
	}

}

// IMPLEMENTED: MAX
// This method displays the board, generated by the InitializeBoard method.
void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	for (int i = 0; i < numRowsInBoard; i++)
	{
		for (int j = 0; j <= numRowsInBoard; j++)
		{
			if (j == numRowsInBoard) {
				cout << endl;
				break;
			}

			switch (CMCheckersBoard[i][j])
			{
				case 0: {
					cout << setw(TABLESPACING) << j + (i * numRowsInBoard);
					continue;
				} case 1: {
					cout << setw(TABLESPACING) << WHITESOLIDER_DISPLAY;
					continue;
				} case 2: {
					cout << setw(TABLESPACING) << WHITEMULE_DISPLAY;
					continue;
				} case 3: {
					cout << setw(TABLESPACING) << WHITEKING_DISPLAY;
					continue;
				} case 4: {
					cout << setw(TABLESPACING) << REDSOLIDER_DISPLAY;
					continue;
				} case 5: {
					cout << setw(TABLESPACING) << REDMULE_DISPLAY;
					continue;
				} case 6: {
					cout << setw(TABLESPACING) << REDKING_DISPLAY;
					continue;
				} default:
					break;
			}

		}
	}
}

// TOBEIMPLEMENTED: Ryan
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	return 0;
}

// TOBEIMPLEMENTED: Jason
bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex)
{
	return false;
}
// TOBEIMPLEMENTED: Max
int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	return 0;
}

// TOBEIMPLEMENTED: Jason
bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	return false;
}

// TOBEIMPLEMENTED: Max
bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	return false;
}

// TOBEIMPLEMENTED: Ryan
bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool & jumped)
{
	return false;
}

// TOBEIMPLEMENTED: Max
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
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