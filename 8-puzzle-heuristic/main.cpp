#include "main.h"

int table[ROWS][COLS] = {
	{ 8,6,7 },
	{ 2,5,4 },
	{ 3,0,1 }
};

int getInvCount(int arr[])
{
    int inv_count = 0;
    for (int i = 0; i < 9 - 1; i++)
        for (int j = i+1; j < 9; j++)
             // Value 0 is used for empty space
             if (arr[j] && arr[i] &&  arr[i] > arr[j])
                  inv_count++;
    return inv_count;
}

bool isSolvable(int puzzle[3][3])
{
    // Count inversions in given 8 puzzle
    int invCount = getInvCount((int *)puzzle);
 
    // return true if inversion count is even.
    return (invCount%2 == 0);
}

int main(){
	
	isSolvable(table)? cout << "Solvable" << std::endl:
                      cout << "Not Solvable" << std::endl;
	

	PuzzleTable puzzle;

	puzzle.initTable(table);
	bool x;
	std::vector<node*> sol;
	int i=0;
	std::vector<node*> *step = new std::vector<node*>();
	printf("Searching...");
	puzzle.a_star_search();
	std::cout << "Found!" << std::endl;
	//.getPathBeforeSearch(puzzle.root,step)

	//for(int i=step->size()-1 ; i>=0 ; i--){
		//puzzle.printArrayInNode((*step)[i]);
	//}
	
	std::cout << "Time : " << clock()/1000.0 << " sec" << std::endl;
	return 0;
}

void randomTable(void) {

	int goal[ROWS][COLS] = {
		{1,2,3},
		{4,5,6},
		{7,8,0}
	};
	srand(time(0));
	int move, i_row = 2, i_col = 2;
	for (int i = 0; i < 50; ) {
		move = rand() % 4;
		cout << move << endl;
		int temp;
		if (move == 0) {
			//right
			if (i_col != 2) {
				temp = goal[i_row][i_col];
				goal[i_row][i_col] = goal[i_row][i_col + 1];
				goal[i_row][i_col + 1] = temp;
				i++;
			}
		}
		else if (move == 1) {
			//left
			if (i_col != 0) {
				temp = goal[i_row][i_col];
				goal[i_row][i_col] = goal[i_row][i_col - 1];
				goal[i_row][i_col - 1] = temp;
				i++;
			}
		}
		else if (move == 2) {
			//down
			if (i_row != 2) {
				temp = goal[i_row][i_col];
				goal[i_row][i_col] = goal[i_row+1][i_col];
				goal[i_row+1][i_col] = temp;
				i++;
			}
		}
		else {
			//up
			if (i_row != 0) {
				temp = goal[i_row][i_col];
				goal[i_row][i_col] = goal[i_row - 1][i_col];
				goal[i_row - 1][i_col] = temp;
				i++;
			}
		}
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			table[i][j] = goal[i][j];
			cout << table[i][j] << " ";
		}
		cout << endl;
	}

	
}
