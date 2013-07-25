#include "pathFinding.h"
#include <stdlib.h>

List* addNodeInSortedList(Node *node, List *list){
	List *newList = malloc(sizeof (List));
	newList->item = node;
	List *runningThroughList = list;
	int newNodeCost = node->startToNodeCost + node->nodeToEndCost;
	
	//adding Node at the begining
	int currentListCost = list->item->startToNodeCost + list->item->nodeToEndCost;
	if(newNodeCost <= currentListCost){
		newList->nextList = list;
	 	return newList;
	}

	// running through the list
	while(runningThroughList->nextList != NULL){
		Node *nextNode = runningThroughList->nextList->item;
		int nextListCost = nextNode->startToNodeCost + nextNode->nodeToEndCost;
		if(newNodeCost <= nextListCost){
			newList->nextList = runningThroughList->nextList;
			runningThroughList->nextList = newList;
			return list;
		}
		runningThroughList = runningThroughList->nextList;
	}
	
	//adding node at the end
	newList->nextList = NULL;
	runningThroughList->nextList = newList;
	return list;
}

List* newList(Node *firstItem){
	List *newList = malloc(sizeof (List));
	newList->item = firstItem;
	newList->nextList = NULL;
 return newList;
}

Node* newNode(int x, int y){
	Node *newNode = malloc(sizeof (Node));
	newNode->x = x;
	newNode->y = y;
	newNode->startToNodeCost = 0;
	newNode->nodeToEndCost = 0;
 return newNode;
}

/*
void searchPath(Map **map, Position start, Position end){
	Node *startNode = newNode(start.x, start.y);
	Node *endNode = newNode(end.x, end.y);
	List *openList = newList(endNode);
	
	Node *currentNode = endNode;
	int i[] = {0,1,0,-1};
	int j[] = {1,0,-1,0};
	for(int k=0; k<4; k++){
		Position currentLocation = {currentNode->x, currentNode->y};
		if(map[currentLocation.x+i][currentLocation.y+j]->hasTower != 1){ //walkable area
			if(){//not in closed list
				map[currentLocation.x+i][currentLocation.y+j]->parent = currentLocation;
				
				openList = addNodeInSortedList(currentNode, openList);
			}
		}
	}
}
*/

List* popInList(Node *nodeToFind, List **list){
	List *runningThroughList = *list;
	// remove the first element
	if(runningThroughList->item == nodeToFind){
		*list = runningThroughList->nextList;
		runningThroughList->nextList = NULL;
		return runningThroughList;
	}
	
	while(runningThroughList->nextList != NULL){
		if(runningThroughList->nextList->item == nodeToFind){
			List *findList = runningThroughList->nextList;
			runningThroughList->nextList = runningThroughList->nextList->nextList;
			findList->nextList = NULL;
			return findList;
		}
		runningThroughList = runningThroughList->nextList;
	}
 return NULL;
}


