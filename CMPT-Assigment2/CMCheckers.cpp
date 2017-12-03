#include <iostream>
#include <iomanip>
#include <math.h>
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

struct CoordinatePair { int columns; int rows; };

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

CoordinatePair convertSquareNumToArrayPos(int numRowsInBoard, int squareNum);

bool isEven(int value);
int checkerBelongsToPlayer(int checkerValue);
int getWrappedCoordinate(int locX, int numRowsInBoard);
bool isArrayEmpty(int myArray[], int numRowsInBoard);
bool isInArray(int locXArray[], int locYArray[], int maxPieces, int locX, int locY);

int main() {

	int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { 0 };

	int xIndicesMove[MAX_PIECES] = { 0 };
	int xIndicesJump[MAX_PIECES] = { 0 };
	int yIndicesMove[MAX_PIECES] = { 0 };
	int yIndicesJump[MAX_PIECES] = { 0 };

	const int MAX_BOARDSIZE_TRIES = 3;

	int numRowsInBoard = 0;
	int squareNumber = -1;
	int squareNumber2 = -1;
	bool whiteTurn = true;
	bool correctInput = false;
	bool gameEnded = false;
	bool jumped = false;

	CoordinatePair moveFrom;
	CoordinatePair moveTo;

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
			} else if (!isEven(numRowsInBoard)) {
				cout << "ERROR: Board size odd.\n";
			} else if (numRowsInBoard > MAX_ARRAY_SIZE) {
				cout << "ERROR:  Board size too large\n";
			} else {
				break;
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

	while (!gameEnded)
	{
		if (whiteTurn) {
			if (CountJumps(myCMCheckersBoard, numRowsInBoard, 1, xIndicesJump, yIndicesJump) <= 0 &&
				CountMove1Squares(myCMCheckersBoard, numRowsInBoard, 1, xIndicesMove, yIndicesMove) <= 0) {
				// No moves
				cout << "\nWhite is unable to move.";
				cout << "\nGAME OVER, Red has won.";
				cout << "\nEnter any character to close the game.";
				// PUT CIN STATEMENT HERE
				return 0;			
			}
		}
		else {
			if (CountJumps(myCMCheckersBoard, numRowsInBoard, 1, xIndicesJump, yIndicesJump) <= 0 
				&& CountMove1Squares(myCMCheckersBoard, numRowsInBoard, 1, xIndicesMove, yIndicesMove) <= 0) {
				// No moves
				cout << "\nRed is unable to move.";
				cout << "\nGAME OVER, White has won.";
				cout << "\nEnter any character to close the game.";
				// PUT CIN STATEMENT HERE
				return 0;
			}
		}

		
		if (whiteTurn) {
			cout << "\nWhite takes a turn.";
		}
		else {
			cout << "\nRed takes a turn.";
		}
		

		while (!correctInput)
		{
			cout << "\nEnter the square number of the checker you want to move\n";

			if (!(cin >> squareNumber)) {
				squareNumber = -1;
				cin.clear();
				cin.ignore();
				cout << "\nERROR: You did not enter an integer";
				cout << "\nTry again";
				continue;
			}
			else {

				moveFrom = convertSquareNumToArrayPos(numRowsInBoard, squareNumber);

				if (squareNumber > (numRowsInBoard * numRowsInBoard) - 1 || squareNumber < 0) {
					cout << "ERROR: That square is not on the board.";
					cout << "\nTry again";
					continue;
				}
				else if (((checkerBelongsToPlayer(myCMCheckersBoard[moveFrom.rows][moveFrom.columns]) == 2 && whiteTurn)) ||
					((checkerBelongsToPlayer(myCMCheckersBoard[moveFrom.rows][moveFrom.columns]) == 1 && !whiteTurn))) {
					cout << "ERROR: That square contains an opponent's checker.";
					cout << "\nTry again";
					continue;
				}
				else if (checkerBelongsToPlayer(myCMCheckersBoard[moveFrom.rows][moveFrom.columns]) == -1) {
					cout << "ERROR: That square is empty.";
					cout << "\nTry again";
					continue;
				}
				else if (!isArrayEmpty(xIndicesJump, numRowsInBoard) && !CheckList(xIndicesJump, yIndicesJump,
					moveFrom.columns, moveFrom.rows)) {

					cout << "ERROR: You can jump with another checker, you may not move your chosen checker.";
					cout << "\nYou can jump using checkers on the following squares: ";

					for (int i = 0; i < numRowsInBoard; i++)
					{
						if (xIndicesJump[i] != -1 && yIndicesJump[i] != -1) {
							cout << (i * numRowsInBoard) + xIndicesJump[i] << " ";
						}
					}

					cout << "\nTry again";
					continue;
				} else if ((!CheckList(xIndicesJump, yIndicesJump, moveFrom.columns, moveFrom.rows)) &&
					(!CheckList(xIndicesMove, yIndicesMove, moveFrom.columns, moveFrom.rows))) {
					cout << "ERROR: There is no legal move for this checker.";
					cout << "\nTry again";
					// DEBUG
					continue;
				}
				
			}
			correctInput = true;
		}

		correctInput = false;
		while (!correctInput)
		{
			cout << "\nEnter the square number of the square you want to move your checker to\n";

			if (!(cin >> squareNumber2)) {
				squareNumber2 = -1;
				cin.clear();
				cin.ignore();
				cout << "\nERROR: You did not enter an integer";
				cout << "\nTry again";
				continue;
			} else {

				moveTo = convertSquareNumToArrayPos(numRowsInBoard, squareNumber2);

				if (squareNumber2 > (numRowsInBoard * numRowsInBoard) - 1 || squareNumber2 < 0) {
					cout << "ERROR: It is not possible to move to a square that is not on the board";
					cout << "\nTry again";
					continue;
				}
				else if (!(checkerBelongsToPlayer(myCMCheckersBoard[moveTo.rows][moveTo.columns]) == -1)) {
					cout << "ERROR: It is not possible to move to a square that is already occupied.";
					cout << "\nTry again";
					continue;
				}
				else if (abs(squareNumber - squareNumber2) == (numRowsInBoard - 1) || abs(squareNumber - squareNumber2) == (numRowsInBoard + 1)) {
					
					if (CheckList(xIndicesJump, yIndicesJump, moveTo.columns, moveTo.rows)) {
						cout << "ERROR: You can jump with this checker, you must jump not move 1 space.";
						cout << "\nTry again";
						continue;
					}
					
				}
			
				if ((!(MakeMove(myCMCheckersBoard, numRowsInBoard, 1, squareNumber, squareNumber2, jumped)) && whiteTurn) ||
					(!(MakeMove(myCMCheckersBoard, numRowsInBoard, 2, squareNumber, squareNumber2, jumped)) && !whiteTurn)) {
					cout << "\nERROR: Moving to that square is not legal, Try again.";
					continue;
				}

			}
			correctInput = true;
		}
		correctInput = false;


		if ((!(MakeMove(myCMCheckersBoard, numRowsInBoard, 1, squareNumber, squareNumber2, jumped)) && whiteTurn) || 
			(!(MakeMove(myCMCheckersBoard, numRowsInBoard, 2, squareNumber, squareNumber2, jumped)) && !whiteTurn)) {
			cout << "\nERROR: Moving to that square is not legal, Try again.";
			continue;
		}
		else {
			DisplayBoard(myCMCheckersBoard, numRowsInBoard);

			while (jumped) // EDITED THIS
			{
				if ((whiteTurn && IsJump(myCMCheckersBoard, numRowsInBoard, 1, moveTo.columns, moveTo.rows)) ||
					(!whiteTurn && IsJump(myCMCheckersBoard, numRowsInBoard, 2, moveTo.columns, moveTo.rows))) {
					// MOVE COMPLETED
					break;
				}
				else {
					moveFrom = moveTo;

					while (!correctInput)
					{
						cout << "\nYou can jump again,  Please enter the next square you wish to move your checker to";

						if (!(cin >> squareNumber)) {
							squareNumber2 = -1;
							cin.clear();
							cin.ignore();
							cout << "\nERROR: You did not enter an integer";
							cout << "\nTry again";
							continue;
						}
						else {
							if (squareNumber2 > (numRowsInBoard * numRowsInBoard) - 1 || squareNumber2 < 0) {
								cout << "\nERROR: It is not possible to move to a square that is not on the board";
								cout << "\nTry again";
								continue;
							}
							else if (!(checkerBelongsToPlayer(myCMCheckersBoard[moveFrom.rows][moveFrom.columns]) == -1)) {
								cout << "ERROR: It is not possible to move to a square that is already occupied.";
								cout << "\nTry again";
								continue;
							}
							else if (abs(squareNumber - squareNumber2) == (numRowsInBoard - 1) || abs(squareNumber - squareNumber2) == (numRowsInBoard + 1)) {
								cout << "\nERROR: You can jump with this checker, you must jump not move 1 space.";
								cout << "\nTry again";
								continue;
							}

						}
						correctInput = true;
					}

					if ((!MakeMove(myCMCheckersBoard, numRowsInBoard, 1, squareNumber, squareNumber2, jumped) && whiteTurn) || 
						(!MakeMove(myCMCheckersBoard, numRowsInBoard, 2, squareNumber, squareNumber2, jumped) && !whiteTurn)) {
						cout << "\nERROR: Moving to that square is not legal, Try again.";
						continue;
					}
					else {
						DisplayBoard(myCMCheckersBoard, numRowsInBoard);
					}

				}
				
			}

		}

		// BROKEN OUT
		if (CheckWin(myCMCheckersBoard, numRowsInBoard)) {
			cout << "\nEnter any character to terminate the game then press the enter key";
			gameEnded = true;
		}
		else {
			DisplayBoard(myCMCheckersBoard, numRowsInBoard);
			squareNumber = -1;
			squareNumber2 = -1;
			correctInput = false;
			jumped = false;
			whiteTurn = whiteTurn == true ? false : true;
			continue;
		}
	}

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

// IMPLEMENTED: Ryan
// This method collects coordinates for all checkers that can jump, belonging to the player.
// Returns amount of checkers that can jump.
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	int JumpCounter = 0;
	for (int i = 0; i < MAX_PIECES; i++)
	{
		xLocArray[i] = -1;
		yLocArray[i] = -1;
	}
	for (int i = 0; i < numRowsInBoard; i++)
	{
		for (int j = 0; j < numRowsInBoard; j++)
		{
			if (checkerBelongsToPlayer(CMCheckersBoard[i][j])==player)
			{
				if (IsJump(CMCheckersBoard, numRowsInBoard, player, j, i))
				{	
					xLocArray[JumpCounter] = j;
					yLocArray[JumpCounter] = i;
					cout << "Checker: " << j << "," << i;
					JumpCounter++;
				}
			}
		}

	}
	return JumpCounter;
}

// TOBEIMPLEMENTED: Jason
bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex)
{
	for (int i = 0; i < MAX_PIECES; i++)
	{
		if (xIndex == inArray1[i])
		{
			if (yIndex == inArray2[i]) {
				return true;
			}
		}
	}
	
	return false;
}
// IMPLEMENTED: Max
// This method returns the amount of checkers that can move one space without jumping, from a particular player.
//		NOTE: Although assigment requires we have xLocArray, and yLocArray, since those arrays are never passed
//            by reference, there isn't a point in putting anything in them, since they'll get erased.
//		NOT-TESTED: Needs IsMove1Square method to work.
int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{ 
	int singleMoveCounter = 0;

	for (int i = 0; i < MAX_PIECES; i++)
	{
		xLocArray[i] = -1;
		yLocArray[i] = -1;
	}

	for (int i = 0; i < numRowsInBoard; i++)
	{
		for (int j = 0; j <= numRowsInBoard; j++)
		{
			// We've got our player's checker
			if (checkerBelongsToPlayer(CMCheckersBoard[i][j]) == player) {
				if (IsMove1Square(CMCheckersBoard, numRowsInBoard, player, j, i)) {

					xLocArray[singleMoveCounter] = j;
					yLocArray[singleMoveCounter] = i;
					//cout << "\nxLoc: " << j;
					//cout << "\nyLoc: " << i;
					singleMoveCounter++;
					//cout << "\nCOUNTER++";
				}
			}
		}

	}

	return singleMoveCounter;
}

// Implemented Jason
bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
		if (checkerBelongsToPlayer(CMCheckersBoard[yLoc][xLoc]) == player) {

			if (player == 1) { // WHITE PLAYER

				if (yLoc + 1 <= numRowsInBoard - 1) {

					if (checkerBelongsToPlayer(CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc - 1, numRowsInBoard)]) == -1) {
						//cout << "\n\tWRAPPED COORDS: " << yLoc + 1 << ","<< getWrappedCoordinate(xLoc - 1, numRowsInBoard);
						//cout << "\n\tCAN_MOVE_1_SQUARE: " << "[" << yLoc << "," << xLoc << "]";
						//cout << "\n\tVALUE: " << CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc - 1, numRowsInBoard)];
						return true;
					} else if (checkerBelongsToPlayer(CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc + 1, numRowsInBoard)]) == -1) {
						//cout << "\nCHECKED RIGHT DIAG";
						return true;
					}

				}
				else {

					if (CMCheckersBoard[xLoc][yLoc] == 3) {
						if (yLoc - 1 >= 0) {
							if (checkerBelongsToPlayer(CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc - 1, numRowsInBoard)]) == -1) {
								cout << "\nCAN_MOVE_1_SQUARE: " << "[" << xLoc << "," << yLoc << "]";
								return true;
							}
							else if (checkerBelongsToPlayer(CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc + 1, numRowsInBoard)]) == -1) {
								cout << "\nCAN_MOVE_1_SQUARE: " << "[" << xLoc << "," << yLoc << "]";
								return true;
							}
						}
					}

				}


			}
			else { // RED PLAYER

				if (yLoc - 1 >= 0) {
					// DIAG. RIGHT
					if (checkerBelongsToPlayer(CMCheckersBoard[yLoc - 1][getWrappedCoordinate(xLoc + 1, numRowsInBoard)]) == -1) {
						cout << "\nCAN_MOVE_1_SQUARE: " << "[" << xLoc << "," << yLoc << "]";
						return true;
					}
					else if (checkerBelongsToPlayer(CMCheckersBoard[yLoc - 1][getWrappedCoordinate(xLoc - 1, numRowsInBoard)]) == -1) {
						cout << "\nCAN_MOVE_1_SQUARE: " << "[" << xLoc << "," << yLoc << "]";
						return true;
					}
				}
				else {

					if (CMCheckersBoard[xLoc][yLoc] == 6) {
						if (yLoc + 1 <= numRowsInBoard - 1) {
							if (checkerBelongsToPlayer(CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc - 1, numRowsInBoard)]) == -1) {
								cout << "\nCAN_MOVE_1_SQUARE: " << "[" << xLoc << "," << yLoc << "]";
								return true;
							}
							else if (checkerBelongsToPlayer(CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc + 1, numRowsInBoard)]) == -1) {
								cout << "\nCAN_MOVE_1_SQUARE: " << "[" << xLoc << "," << yLoc << "]";
								return true;
							}
						}
					}

				}
			}
		}

		return false;
}

// IMPLEMENTED: Max
// This method checks to see if a particular peice can jump, takes into account impossible off-board moves.
//	NOTE: Note NOT tested due to other methods not being completed. Also there is a lot of repetion which should
//        Be moved into it's own method, do that later, will cut down on checks needed.
bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	if (checkerBelongsToPlayer(CMCheckersBoard[yLoc][xLoc]) == player) {
		// The checker indeed belongs to the player.
		if (player == 1) { // WHITE PLAYER
			
			if (yLoc + 1 <= numRowsInBoard - 1) {
				// DIAG. RIGHT
				if (checkerBelongsToPlayer(CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc - 1, numRowsInBoard)]) == 2
					&& CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc - 2, numRowsInBoard)] == 0) {
					cout << "DIAG RIGHT";
					return true;
				} else if (checkerBelongsToPlayer(CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc + 1, numRowsInBoard)]) == 2
					&& CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc + 2, numRowsInBoard)] == 0) {
					cout << "DIAG RIGHT";
					return true;
				}

			}
			else {
				// IF OUR PEICE IS A KING, CHECK THE BACKSIDE
				if (CMCheckersBoard[xLoc][yLoc] == 3) {
					if (yLoc - 1 >= 0) {
						if (checkerBelongsToPlayer(CMCheckersBoard[yLoc - 1][getWrappedCoordinate(xLoc + 1, numRowsInBoard)]) == 2
							&& CMCheckersBoard[yLoc - 1][getWrappedCoordinate(xLoc + 2, numRowsInBoard)] == 0) {
							cout << "DIAG RIGHT";
							return true;
						}
						else if (checkerBelongsToPlayer(CMCheckersBoard[yLoc - 1][getWrappedCoordinate(xLoc - 1, numRowsInBoard)]) == 2
							&& CMCheckersBoard[yLoc - 1][getWrappedCoordinate(xLoc - 2, numRowsInBoard)] == 0) {
							cout << "DIAG RIGHT";
							return true;
						}
					}
				}

			}

			// That check didn't work, maybe they're a king and have an option of moving?
		}
		else { // RED PLAYER
			
			if (yLoc - 1 >= 0) {
				// DIAG. RIGHT
				if (checkerBelongsToPlayer(CMCheckersBoard[yLoc - 1][getWrappedCoordinate(xLoc + 1, numRowsInBoard)]) == 1
					&& CMCheckersBoard[yLoc - 1][getWrappedCoordinate(xLoc + 2, numRowsInBoard)] == 0) {
					cout << "DIAG RIGHT";
					return true;
				} else if (checkerBelongsToPlayer(CMCheckersBoard[yLoc - 1][getWrappedCoordinate(xLoc - 1, numRowsInBoard)]) == 1
					&& CMCheckersBoard[yLoc - 1][getWrappedCoordinate(xLoc - 2, numRowsInBoard)] == 0) {
					cout << "DIAG RIGHT";
					return true;
				}
			} else {
				// IF OUR PEICE IS A KING, CHECK THE BACKSIDE
				if (CMCheckersBoard[xLoc][yLoc] == 6) {
					if (yLoc + 1 <= numRowsInBoard - 1) {
						if (checkerBelongsToPlayer(CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc - 1, numRowsInBoard)]) == 1
							&& CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc - 2, numRowsInBoard)] == 0) {
							cout << "DIAG RIGHT";
							return true;
						}
						else if (checkerBelongsToPlayer(CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc + 1, numRowsInBoard)]) == 1
							&& CMCheckersBoard[yLoc + 1][getWrappedCoordinate(xLoc + 2, numRowsInBoard)] == 0) {
							cout << "DIAG RIGHT";
							return true;
						}
					}
				}

			}
		}
	}

	return false;
}

// TOBEIMPLEMENTED: Max
// This method moves a checker, it makes sure double jumps are accurate, and makes sure to remove peices.
// This should also handle single jumps.
bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool & jumped)
{
	int squareDifference = abs(fromSquareNum - toSquareNum);
	CoordinatePair pair = convertSquareNumToArrayPos(numRowsInBoard, fromSquareNum);
	int ogPeice = CMCheckersBoard[pair.rows][pair.columns];

	if (squareDifference == (numRowsInBoard - 1) || squareDifference == (numRowsInBoard + 1)
		|| squareDifference == ((2 * numRowsInBoard) - 1)) {
		// Made a single jump
		CMCheckersBoard[pair.rows][pair.columns] = 0;
		pair = convertSquareNumToArrayPos(numRowsInBoard, toSquareNum);
		CMCheckersBoard[pair.rows][pair.columns] = ogPeice;
		return true;

	} else if (squareDifference == ( (2 * numRowsInBoard) - 2) || squareDifference == ((2 * numRowsInBoard) + 2)
		|| squareDifference == ((3 * numRowsInBoard) - 2)) {
		// Made a double jump

		// Check if the checker is moving in the right direction
		if (checkerBelongsToPlayer(CMCheckersBoard[pair.rows][pair.columns]) == 1) {
			if (!(CMCheckersBoard[pair.rows][pair.columns] == 3) && fromSquareNum > toSquareNum) {
				// Moving the wrong way
				cout << "\nERROR: Illegal move.";
				return false;
			}
		}
		else if (checkerBelongsToPlayer(CMCheckersBoard[pair.rows][pair.columns]) == 2) {
			if (!(CMCheckersBoard[pair.rows][pair.columns] == 6 && fromSquareNum < toSquareNum)) {
				// Moving the wrong way
				cout << "\nERROR: Illegal move.";
				return false;
			}
		}
		CMCheckersBoard[pair.rows][pair.columns] = 0;
		pair.columns = getWrappedCoordinate(pair.columns + 1, numRowsInBoard);
		pair.rows = fromSquareNum > toSquareNum ? pair.rows - 1 : pair.rows + 1;

		if (player == 1) {
			// White Player
			if (!(checkerBelongsToPlayer(CMCheckersBoard[pair.rows][pair.columns]) == 2)) {
				pair = convertSquareNumToArrayPos(numRowsInBoard, fromSquareNum);
				CMCheckersBoard[pair.rows][pair.columns] = ogPeice;
				cout << "\nERROR: Illegal move.";
				return false;
			}
		} else {
			if (!(checkerBelongsToPlayer(CMCheckersBoard[pair.rows][pair.columns]) == 1)) {
				pair = convertSquareNumToArrayPos(numRowsInBoard, fromSquareNum);
				CMCheckersBoard[pair.rows][pair.columns] = ogPeice;
				cout << "\nERROR: Illegal move.";
				return false;
			}
		}
		// Move checker and replace.
		CMCheckersBoard[pair.rows][pair.columns] = 0;
		pair = convertSquareNumToArrayPos(numRowsInBoard, toSquareNum);
		CMCheckersBoard[pair.rows][pair.columns] = ogPeice;
		cout << "\nMoved Og Piece to : " << pair.rows << "," << pair.columns;
		
	} else {
		// Can't have more than a double jump in one go, therefore this is an invalid move.
		cout << "\nError;  illegal move";
		return false;
	}

	// Check in general whether the peice is at the king promotion spot.
	if (pair.rows == 0) {
		if (checkerBelongsToPlayer(CMCheckersBoard[pair.rows][pair.columns]) == 2) {
			// WE need to promot it to a red king
			CMCheckersBoard[pair.rows][pair.columns] = 6;
		}
	} else if (pair.rows == (numRowsInBoard - 1)) {
		if (checkerBelongsToPlayer(CMCheckersBoard[pair.rows][pair.columns]) == 1) {
			// WE need to promot it to a white king
			CMCheckersBoard[pair.rows][pair.columns] = 3;
		}
	}

	// Checking for a game win
	if (player == 1 && ogPeice == 2 && pair.rows == (numRowsInBoard - 1)) {
		// MULE WENT TO KING
		cout << "\nWhite has created a Mule King, Red wins the game";
		return true;
	}
	else if (player == 2 && ogPeice == 5 && pair.rows == 0) {
		// MULE WENT TO KING
		cout << "\nRed has created a Mule King,  White wins the game";
		return true;
	}

	if (!jumped) {
		jumped = true;
	}

	return true;
}

// Implemented Max
// Checks if a player has one.
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int redMules = 0;
	int whiteMules = 0;
	int redSoliders = 0;
	int whiteSoliders = 0;
	int redKings = 0;
	int whiteKings = 0;
	int currentPeice = 0;

	for (int i = 0; i < numRowsInBoard; i++)
	{
		for (int j = 0; i < numRowsInBoard; i++)
		{
			currentPeice = CMCheckersBoard[i][j];

			switch (currentPeice)
			{
				 case 1: {
					whiteSoliders++;
					continue;
				} case 2: {
					 whiteMules++;
					continue;
				} case 3: {
					whiteKings++;
					continue;
				} case 4: {
					redSoliders++;
					continue;
				} case 5: {
					redMules++;
					continue;
				} case 6: {
					redKings++;
					continue;
				} default:
					break;
			}
		}
	}

	if (redMules == 0) {
		cout << "\nThe Red Player has won the game by losing all of the Red Mules";
		return true;
	} else if (whiteMules == 0) {
		cout << "\nThe White Player has won the game by losing all of the White Mules";
		return true;
	} else if (whiteSoliders == 0 && whiteKings == 0) {
		cout << "\nThe White Player has won by capturing all of the red players soldiers and kings";
		return true;
	} else if (redSoliders == 0 && redKings == 0) {
		cout << "\nThe Red Player has won by capturing all of the white players soldiers and kings";
		return true;
	}

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

// Checks which player a checker belongs to, if it's blank, returns -1.
int checkerBelongsToPlayer(int checkerValue) {

	if (checkerValue >= 1 && checkerValue <= 3) {
		// WHITE PLAYER
		return 1;
	}
	else if (checkerValue >= 4 && checkerValue <= 6) {
		// RED PLAYER
		return 2;
	}
	else {
		return -1;
	}
}

// Our board is really a cylinder. This is because we can "go off the board"
//	Then come back on the other side. We need to make sure that we get the correct
//	coordinates every time we jump "off the board".
//  NOTE: This does not check whether a jump is valid or not, just manipulates the X
//       to wrap around the board.		 
int getWrappedCoordinate(int locX, int numRowsInBoard) {
	
	if (locX >(numRowsInBoard - 1)) {
		return locX % numRowsInBoard;
	}
	else if (locX < 0) {
		return (locX % numRowsInBoard) + numRowsInBoard;;
	}
	else {
		return locX;
	}
}

bool isArrayEmpty(int myArray[], int numRowsInBoard)
{
	for (int i = 0; i < numRowsInBoard; i++)
	{
		if (myArray[i] != -1) {
			return false;
		}
	}
	return true;
}

bool isInArray(int locXArray[], int locYArray[], int maxPieces, int locX, int locY)
{
	for (int i = 0; i < maxPieces; i++)
	{
		if (locYArray[i] == locY == locXArray[i] == locX) {
			return true;
		}
	}

	return false;
}
// This method takes a board square number, and returns a Coordinate pair of the,
//	coordinates inside the array.
CoordinatePair convertSquareNumToArrayPos(int numRowsInBoard, int squareNum) {

	CoordinatePair arrayCoordinates;
	int counter = 0;

	while (squareNum >= numRowsInBoard)
	{
		squareNum -= numRowsInBoard;
		counter++;
	}

	arrayCoordinates.columns = squareNum;
	arrayCoordinates.rows = counter;

	return arrayCoordinates;
}