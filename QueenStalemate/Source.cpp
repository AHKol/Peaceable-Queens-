#include <iostream>
#include <cstdlib>
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
	for (int i = 0; i < size * size; i++) {
		//print new rows
		if (!(i % size))
			cout << '\n';
		if (grid[i] == 0)
			cout << "X ";
		else
			cout << grid[i] << " ";
	}
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

int main(int argc, char *argv[]) {
	//no size fail
	if (argc == 1) {
		return -1;
	}

	int size = atoi(argv[1]);
	int *grid = new int[size * size];
	memset(grid, 0, sizeof(int) * (size * size) );

	//queen pair loop
	int j = 0;
	int i = 0;
	for (; i < size*size / 2; i++) {
		//white position loop
		bool wPlaced = false;
		bool bPlaced = false;
		for ( ; j < size*size && !wPlaced; j++) {
			if (testPlace(1, j, size, grid)) {
				grid[j] = 1;
				//black position loop
				for (int k = j; k < size*size && !bPlaced; k++) {
					if (testPlace(2, k, size, grid)) {
						grid[k] = 2;
						bPlaced = true;
					}
				}
				if (!bPlaced) {
					grid[j] = 0;
					break;
				}
				else{ 
					wPlaced = true; 
				}
					
			}
		}
		if (!wPlaced) {
			break;
		}

	}
	cout << "Pair Count: " << i;

	printGrid(size, grid);

	return size;
}