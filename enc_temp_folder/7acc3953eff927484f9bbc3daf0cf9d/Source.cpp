#include <iostream>
#include <cstdlib>
#include "Header.h"
/*
grid of queens
equal ammounts black and white
arranged in a way that that they can't attack eachother
find largest arangement
blank = 0, white = 1, black = 2
*/
/*
performance consepts
black and white can be mirrored
nothing needs to be placed behind first call because it is already done by previous calls
*/
using namespace std;

int QUEENCOUNT = 0;
int NEWMAX = -1;

bool testHorisontal(int color, int pos, int size, int *grid) {
	int row = pos / size;
	row *= size;
	for (int i = row; i < row + size; i++) {
		if (grid[i] != 0 && grid[i] != color) {
			return false;
		}
	}
	return true;
}

bool testVertical(int color, int pos, int size, int *grid) {
	//test vertical
	int col = pos % size;
	for (int i = col; i < size * size; i += size) {
		if (grid[i] != 0 && grid[i] != color) {
			return false;
		}
	}
	return true;
}

bool testNW(int color, int pos, int size, int *grid) {
	//search back
	for (int i = pos; i >= 0 && i % size >= 0; i -= (size + 1)) {
		if (grid[i] != 0 && grid[i] != color) {
			return false;
		}
	}
	//search forward
	for (int i = pos; i < size*size && i % size < size; i += (size + 1)) {
		if (grid[i] != 0 && grid[i] != color) {
			return false;
		}
	}
	return true;
}

bool testNE(int color, int pos, int size, int *grid) {
	//search back
	for (int i = pos; i >= 0 && i % size <= (size - 1); i -= (size - 1)) {
		if (grid[i] != 0 && grid[i] != color) {
			return false;
		}
	}
	//search forward
	for (int i = pos; i < size*size && i % size >= 0; i += (size - 1)) {
		if (grid[i] != 0 && grid[i] != color) {
			return false;
		}
	}
	return true;
}

void printGrid(int size, int *grid) {
	//print grid
	cout << "Size is: " << QUEENCOUNT << '\n';
	for (int i = 0; i < size * size; i++) {
		//print new rows
		if (!(i % size))
			cout << '\n';
		if (grid[i] == 0)
			cout << "X ";
		else
			cout << grid[i] << " ";
	}

	cout << '\n' << '\n' ;
}

bool testPlace(int color, int pos, int size, int *grid) {
	//test overlap
	if (grid[pos] != 0) {
		return false;
	}
	if (!testHorisontal(color, pos, size, grid))
		return false;
	if (!testVertical(color, pos, size, grid))
		return false;
	if (!testNW(color, pos, size, grid))
		return false;
	if (!testNE(color, pos, size, grid))
		return false;
	return true;
}

int placeWhite(int pos, int size, int *grid) {
	//white position loop
	for (int i = pos; i < size*size; i++) {
		if (testPlace(1, i, size, grid)) {
			grid[i] = 1;
			return i;
		}
	}
	return -1;
}

int placeBlack(int pos, int size, int *grid) {
	//black position loop
	for (int i = pos; i < size*size; i++) {
		if (testPlace(2, i, size, grid)) {
			grid[i] = 2;
			return i;
		}
	}
	return 0;
}

//pos is current position
//lastpos is the position of the last white queen
void placeW(int pos, int lastPos, int size, int *grid) {
	//base case
	if (!testPlace(1, pos, size, grid)) {
		return;
	}
	grid[pos] = 1;

	//Place next Black queen
	for (int i = lastPos; i < size*size; i++) {
		placeB(i, lastPos, size, grid);
	}

	grid[pos] = 0;
	return;
}
void placeB(int pos, int lastPos, int size, int *grid) {
	//base case
	if (!testPlace(2, pos, size, grid)) {
		//printGrid(size, grid);
		return;
	}
	grid[pos] = 2;
	QUEENCOUNT++;

	if (QUEENCOUNT > NEWMAX) {
		NEWMAX = QUEENCOUNT;
		printGrid(size, grid);
	}

	//Place next white queen
	for (int i = lastPos; i < size*size; i++) {
		placeW(i, lastPos, size, grid);
	}
	QUEENCOUNT--;
	grid[pos] = 0;
	return;
}

//in white
	//recursive place black
	//recursive place next black
	//until end

//recursive black places white if possible, if not posible it prints arangement to file and undoes what it printed

int main(int argc, char *argv[]) {
	//no size fail
	if (argc == 1) {
		return -1;
	}

	//Define grid size
	int size = atoi(argv[1]);
	int *grid = new int[size * size];
	memset(grid, 0, sizeof(int) * (size * size) );
	

	for (int i = 1; i < size*size; i++) {
		placeW(i, i, size, grid);
	}

	//int lastPos = 0;
	//int nextPos = 0;
	//while (nextPos < size * size) {
	//	//Place Next White, starting at previous+1
	//	lastPos = placeWhite(nextPos, size, grid);
	//	if (lastPos == -1) {
	//		nextPos++;
	//	}
	//	else {
	//		//place next black
	//		//if no black can be placed: remove last white and continue white+1
	//		if (!placeBlack(0, size, grid)) {
	//			grid[lastPos] = 0;
	//			nextPos++;
	//		}
	//	}
	//}

	return size;
}