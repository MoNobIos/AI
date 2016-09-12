#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>

//#define DEBUG_EXPAND
#define ROWS 3
#define COLS 3

enum stateFrom{ROOT,LEFT,RIGHT,TOP,BOTTOM};

typedef struct node{
	int table[COLS][ROWS];
	int depth;
	int h1;
	int h2;
	stateFrom from;
	struct node *nextLeft;
	struct node *nextRight;
	struct node *nextTop;
	struct node *nextBottom;
};

class PuzzleTable{
public:
	PuzzleTable();
	bool isGoal(int table[COLS][ROWS]);
	void initTable(int source[COLS][ROWS]);
	void copyArray(int source[COLS][ROWS],int dest[COLS][ROWS]);
	node* createNode(int source[COLS][ROWS]);
	node* moveLeft(int source[COLS][ROWS]);
	node* moveRight(int source[COLS][ROWS]);
	node* moveTop(int source[COLS][ROWS]);
	node* moveBottom(int source[COLS][ROWS]);
	bool isAlreadHas(node *n);
	
	void printArrayInNode(node *n);
	int getManhattanDistance(const node* n);
	int getTilesOutOfRowAndColumn(const node* n);
	void a_star_search();
	void expandNode(node* n);
	bool getPathBeforeSearch(node *cur,std::vector<node*> *step);

	node *root;

private:
	int goal[COLS][ROWS];
	std::vector<node*> alread_has;
	std::vector<node*> *list_leaves;
	int* PuzzleTable::indexOfBlank(int source[COLS][ROWS]);
};