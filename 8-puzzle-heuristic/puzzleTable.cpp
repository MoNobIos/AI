#include "puzzleTable.h"
#include <conio.h>
PuzzleTable::PuzzleTable(){
	int temp[COLS][ROWS] = {
		{1,2,3},
		{4,5,6},
		{7,8,0}
	};
	copyArray(temp,goal);
	root = NULL;
}

void PuzzleTable::initTable(int source[COLS][ROWS]){
	root = createNode(source);
	root->depth = 0;
	root->from = stateFrom::ROOT;
	alread_has.push_back(root);
	list_leaves = new std::vector<node*>();
	list_leaves->push_back(root);
}

void PuzzleTable::copyArray(int source[COLS][ROWS],int dest[COLS][ROWS]){
	for(int i=0 ; i<COLS ; i++){
		for(int j=0 ; j<ROWS ; j++){
			dest[i][j] = source[i][j];
		}
	}
}

node* PuzzleTable::moveLeft(int source[COLS][ROWS]){
	node *temp = NULL;
	int *index = indexOfBlank(source);
	int x = index[0];
	int y = index[1];
	if(x-1>=0){
		temp = createNode(source);
		temp->table[y][x] = temp->table[y][x-1];
		temp->table[y][x-1] = 0;
		temp->from = stateFrom::LEFT;
	}
	return temp;
}

node* PuzzleTable::moveRight(int source[COLS][ROWS]){
	node *temp = NULL;
	int *index = indexOfBlank(source);
	int x = index[0];
	int y = index[1];
	if(x+1<ROWS){
		temp = createNode(source);
		temp->table[y][x] = temp->table[y][x+1];
		temp->table[y][x+1] = 0;
		temp->from = stateFrom::RIGHT;
	}
	return temp;
}

node* PuzzleTable::moveTop(int source[COLS][ROWS]){
	node *temp = NULL;
	int *index = indexOfBlank(source);
	int x = index[0];
	int y = index[1];
	if(y-1>=0){
		temp = createNode(source);
		temp->table[y][x] = temp->table[y-1][x];
		temp->table[y-1][x] = 0;
		temp->from = stateFrom::TOP;
	}
	return temp;
}

node* PuzzleTable::moveBottom(int source[COLS][ROWS]){
	node *temp = NULL;
	int *index = indexOfBlank(source);
	int x = index[0];
	int y = index[1];
	if(y+1<COLS){
		temp = createNode(source);
		temp->table[y][x] = temp->table[y+1][x];
		temp->table[y+1][x] = 0;
		temp->from = stateFrom::BOTTOM;
	}
	return temp;
}

node* PuzzleTable::createNode(int source[COLS][ROWS]){
	node *temp = (node*) malloc( sizeof(node)); ;
	copyArray(source,temp->table);
	temp->nextLeft = NULL;
	temp->nextRight = NULL;
	temp->nextTop = NULL;
	temp->nextBottom = NULL;
	return temp;
}

int* PuzzleTable::indexOfBlank(int source[COLS][ROWS]){
	int index[2];
	//x y
	for(int i=0 ; i<COLS ; i++){
		for(int j=0 ; j<ROWS ; j++){
			if(source[i][j]==0){
				index[0] = j;
				index[1] = i;
			}
		}
	}
	return index;
}

bool PuzzleTable::isGoal(int table[COLS][ROWS]){
	int result = true;
	for(int i=0 ; i<COLS ; i++){
		for(int j=0 ; j<ROWS ; j++){
			if(table[i][j] != goal[i][j]){
				result = false;
				break;
			}
		}
		if(!result) break;
	}
	return result;
}

bool PuzzleTable::isAlreadHas(node *n){
	bool result = false;
	for(int i=0 ; i<alread_has.size() ; i++){
		int r = true;
		for(int j=0 ; j<COLS ; j++){
			for(int k=0 ; k<ROWS ; k++){
				if(n->table[j][k] != alread_has[i]->table[j][k]){
					r = false;
					break;
				}
			}
			if(!r) break;
		}
		if(r) result = true;
	}
	return result;
}

void PuzzleTable::printArrayInNode(node *n){
	std::cout << "depth : " << n->depth << std::endl;
	for(int i=0 ; i<COLS ; i++){
		printf("%d %d %d\n",n->table[i][0],n->table[i][1],n->table[i][2]);
	}
	printf("\n");
}

//heuristic 1
int PuzzleTable::getManhattanDistance(const node* n){
	int sum = 0;
	int temp = n->table[0][0];
	if(temp==1) sum += 0;
	else if(temp==2) sum += 1;
	else if(temp==3) sum += 2;
	else if(temp==4) sum += 1;
	else if(temp==5) sum += 2;
	else if(temp==6) sum += 3;
	else if(temp==7) sum += 2;
	else if(temp==8) sum += 3;


	temp = n->table[0][1];
	if(temp==1) sum += 1;
	else if(temp==2) sum += 0;
	else if(temp==3) sum += 1;
	else if(temp==4) sum += 2;
	else if(temp==5) sum += 1;
	else if(temp==6) sum += 2;
	else if(temp==7) sum += 3;
	else if(temp==8) sum += 2;


	temp = n->table[0][2];
	if(temp==1) sum += 2;
	else if(temp==2) sum += 1;
	else if(temp==3) sum += 0;
	else if(temp==4) sum += 3;
	else if(temp==5) sum += 2;
	else if(temp==6) sum += 1;
	else if(temp==7) sum += 4;
	else if(temp==8) sum += 3;


	temp = n->table[1][0];
	if(temp==1) sum += 1;
	else if(temp==2) sum += 2;
	else if(temp==3) sum += 3;
	else if(temp==4) sum += 0;
	else if(temp==5) sum += 1;
	else if(temp==6) sum += 2;
	else if(temp==7) sum += 1;
	else if(temp==8) sum += 2;


	temp = n->table[1][1];
	if(temp==1) sum += 2;
	else if(temp==2) sum += 1;
	else if(temp==3) sum += 2;
	else if(temp==4) sum += 1;
	else if(temp==5) sum += 0;
	else if(temp==6) sum += 1;
	else if(temp==7) sum += 2;
	else if(temp==8) sum += 1;


	temp = n->table[1][2];
	if(temp==1) sum += 3;
	else if(temp==2) sum += 2;
	else if(temp==3) sum += 1;
	else if(temp==4) sum += 2;
	else if(temp==5) sum += 1;
	else if(temp==6) sum += 0;
	else if(temp==7) sum += 3;
	else if(temp==8) sum += 2;


	temp = n->table[2][0];
	if(temp==1) sum += 2;
	else if(temp==2) sum += 3;
	else if(temp==3) sum += 4;
	else if(temp==4) sum += 1;
	else if(temp==5) sum += 2;
	else if(temp==6) sum += 3;
	else if(temp==7) sum += 0;
	else if(temp==8) sum += 1;


	temp = n->table[2][1];
	if(temp==1) sum += 3;
	else if(temp==2) sum += 2;
	else if(temp==3) sum += 3;
	else if(temp==4) sum += 2;
	else if(temp==5) sum += 1;
	else if(temp==6) sum += 2;
	else if(temp==7) sum += 1;
	else if(temp==8) sum += 0;


	temp = n->table[2][2];
	if(temp==1) sum += 4;
	else if(temp==2) sum += 3;
	else if(temp==3) sum += 2;
	else if(temp==4) sum += 3;
	else if(temp==5) sum += 2;
	else if(temp==6) sum += 1;
	else if(temp==7) sum += 2;
	else if(temp==8) sum += 1;

	return sum;
}

void PuzzleTable::expandNode(node* n){
	int cur_d = n->depth+1;
	if(n->nextLeft == NULL && n->from != stateFrom::RIGHT){
			node *temp = moveLeft(n->table);
			if(temp != NULL){
				if(isAlreadHas(temp) != true){
					temp->depth = cur_d;
					temp->h1 = getManhattanDistance(temp);
					temp->h2 = getTilesOutOfRowAndColumn(temp);
					n->nextLeft = temp;
					
#ifdef DEBUG_EXPAND
					printArrayInNode((*list)[0]->nextLeft );
#endif
				}
				else{
					n->nextLeft = NULL;
					free(temp);
				}
			}
		}
		

		if(n->nextRight == NULL && n->from != stateFrom::LEFT){
			node *temp = moveRight(n->table);
			if(temp != NULL){
				if(isAlreadHas(temp) != true){
					temp->depth = cur_d;
					temp->h1 = getManhattanDistance(temp);
					temp->h2 = getTilesOutOfRowAndColumn(temp);
					n->nextRight = temp;
#ifdef DEBUG_EXPAND
					printArrayInNode((*list)[0]->nextRight );
#endif
				}
				else{
					n->nextRight = NULL;
					free(temp);
				}
			}
		}

		if(n->nextTop == NULL && n->from != stateFrom::BOTTOM){
			node *temp = moveTop(n->table);
			if(temp != NULL){
				if(isAlreadHas(temp) != true){
					temp->depth = cur_d;
					temp->h1 = getManhattanDistance(temp);
					temp->h2 = getTilesOutOfRowAndColumn(temp);
					n->nextTop = temp;
					
#ifdef DEBUG_EXPAND
					printArrayInNode((*list)[0]->nextTop );
#endif
				}
				else{
					n->nextTop = NULL;
					free(temp);
				}
			}
		}

		if(n->nextBottom == NULL && n->from != stateFrom::TOP){
			node *temp = moveBottom(n->table);
			if(temp != NULL){
				if(isAlreadHas(temp) != true){
					temp->depth = cur_d;
					temp->h1 = getManhattanDistance(temp);
					temp->h2 = getTilesOutOfRowAndColumn(temp);
					n->nextBottom = temp;
					
#ifdef DEBUG_EXPAND
					printArrayInNode((*list)[0]->nextBottom );
#endif
				}
				else{
					n->nextBottom = NULL;
					free(temp);
				}
			}
		}
}

//heuristic 2
int PuzzleTable::getTilesOutOfRowAndColumn(const node* n){
	int sum = 0;
	int temp = n->table[0][0];
	if(temp==1) sum += 0;
	else if(temp==2) sum += 1;
	else if(temp==3) sum += 1;
	else if(temp==4) sum += 1;
	else if(temp==5) sum += 2;
	else if(temp==6) sum += 2;
	else if(temp==7) sum += 1;
	else if(temp==8) sum += 2;


	temp = n->table[0][1];
	if(temp==1) sum += 1;
	else if(temp==2) sum += 0;
	else if(temp==3) sum += 1;
	else if(temp==4) sum += 2;
	else if(temp==5) sum += 1;
	else if(temp==6) sum += 2;
	else if(temp==7) sum += 2;
	else if(temp==8) sum += 1;


	temp = n->table[0][2];
	if(temp==1) sum += 1;
	else if(temp==2) sum += 1;
	else if(temp==3) sum += 0;
	else if(temp==4) sum += 2;
	else if(temp==5) sum += 2;
	else if(temp==6) sum += 1;
	else if(temp==7) sum += 2;
	else if(temp==8) sum += 2;


	temp = n->table[1][0];
	if(temp==1) sum += 1;
	else if(temp==2) sum += 2;
	else if(temp==3) sum += 2;
	else if(temp==4) sum += 0;
	else if(temp==5) sum += 1;
	else if(temp==6) sum += 1;
	else if(temp==7) sum += 1;
	else if(temp==8) sum += 2;


	temp = n->table[1][1];
	if(temp==1) sum += 2;
	else if(temp==2) sum += 1;
	else if(temp==3) sum += 2;
	else if(temp==4) sum += 1;
	else if(temp==5) sum += 0;
	else if(temp==6) sum += 1;
	else if(temp==7) sum += 2;
	else if(temp==8) sum += 1;


	temp = n->table[1][2];
	if(temp==1) sum += 2;
	else if(temp==2) sum += 2;
	else if(temp==3) sum += 1;
	else if(temp==4) sum += 1;
	else if(temp==5) sum += 1;
	else if(temp==6) sum += 0;
	else if(temp==7) sum += 2;
	else if(temp==8) sum += 2;


	temp = n->table[2][0];
	if(temp==1) sum += 1;
	else if(temp==2) sum += 2;
	else if(temp==3) sum += 2;
	else if(temp==4) sum += 1;
	else if(temp==5) sum += 2;
	else if(temp==6) sum += 2;
	else if(temp==7) sum += 0;
	else if(temp==8) sum += 1;


	temp = n->table[2][1];
	if(temp==1) sum += 2;
	else if(temp==2) sum += 1;
	else if(temp==3) sum += 2;
	else if(temp==4) sum += 2;
	else if(temp==5) sum += 1;
	else if(temp==6) sum += 2;
	else if(temp==7) sum += 1;
	else if(temp==8) sum += 0;


	temp = n->table[2][2];
	if(temp==1) sum += 2;
	else if(temp==2) sum += 2;
	else if(temp==3) sum += 1;
	else if(temp==4) sum += 2;
	else if(temp==5) sum += 2;
	else if(temp==6) sum += 1;
	else if(temp==7) sum += 1;
	else if(temp==8) sum += 1;

	return sum;
}

bool sortByH(const void* a,const void* b){
	node *left = (node*)a;
	node *right = (node*)b;
	
	if((left->depth + left->h1) == ((right->depth + right->h1))) 
		return (left->h2) < (right->h2);
	else 
	return ((left->depth + left->h1) < (right->depth + right->h1));
	
	//return ((left->depth + left->h1) < (right->depth + right->h1));
}

bool PuzzleTable::getPathBeforeSearch(node *cur,std::vector<node*> *step){
	//dfs
	bool found = false;
	if(cur==NULL) return false;
	if(isGoal(cur->table) == true){
		printf("found!!\n");
		//printArrayInNode(cur);
		step->push_back(cur);
		return true;
	}
	else{
		if(found==false){
			found = getPathBeforeSearch(cur->nextLeft,step);
		}
		if(found==false){
			found = getPathBeforeSearch(cur->nextRight,step);
		}
		if(found==false){
			found = getPathBeforeSearch(cur->nextTop,step);
		}
		if(found==false){
			found = getPathBeforeSearch(cur->nextBottom,step);
		}
	}
	if(found){
		//printArrayInNode(cur);
		step->push_back(cur);
	}
	return found;
}

void PuzzleTable::a_star_search(){
	/* isGoal? -> (if goal then stop),(else) -> expand from first order -> 
	*  enqueue ->  dequeue first order -> 
	*  sort (arrange by ascending order) -> isGoal?
	*/
	std::vector<node*> q;
	q.push_back(root);
	while(isGoal(q[0]->table) != true){
		expandNode(q[0]);
		if(q[0]->nextLeft != NULL){
			if((q[0]->nextLeft->depth + q[0]->nextLeft->h1 + q[0]->nextLeft->h2)<40){
				q.push_back(q[0]->nextLeft);
			}
		}
		if(q[0]->nextRight != NULL){
			if((q[0]->nextRight->depth + q[0]->nextRight->h1 + q[0]->nextRight->h2)<40){
				q.push_back(q[0]->nextRight);
			}
		}
		if(q[0]->nextTop != NULL){
			if((q[0]->nextTop->depth + q[0]->nextTop->h1 + q[0]->nextTop->h2)<40){
				q.push_back(q[0]->nextTop);
			}
		}
		if(q[0]->nextBottom != NULL){
			if((q[0]->nextBottom->depth + q[0]->nextBottom->h1 + q[0]->nextBottom->h2)<40){
				q.push_back(q[0]->nextBottom);
			}
		}

		q.erase(q.begin());
		std::sort(q.begin(),q.end(),sortByH);
		
		//std::cout << "* " << q[0]->h1+q[0]->h2 << std::endl;
		
	}
			
	printArrayInNode(q[0]);
	std::cout << "d = " << q[0]->depth << std::endl;
	std::cout << "ok" << std::endl;
}