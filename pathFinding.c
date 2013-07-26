#include "pathFinding.h"
#include <stdlib.h>

List* addNodeInSortedList(Node *node, List *list){
	List *newList = malloc(sizeof (List));
	newList->item = node;
	newList->nextList = NULL;
	List *runningThroughList = list;
	// Case of an empty List
	if(runningThroughList == NULL){
		return newList;
	}

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

static List *openList;
static List *closedList;

/*void searchPath(Map **map, Position start, Position end){*/
/*	Node *startNode = newNode(start.x, start.y);*/
/*	Node *endNode = newNode(end.x, end.y);*/
/*	openList = newList(endNode);*/
/*	closedList = NULL;*/
/*	*/
/*	Node *currentNode = endNode;*/
/*	int i[] = {0,1,0,-1};*/
/*	int j[] = {1,0,-1,0};*/
/*	for(int k=0; k<4; k++){*/
/*		Position currentLocation = {currentNode->x, currentNode->y};*/
/*		Node *adjacentNode = */
/*		if(map[currentLocation.x+i[k]][currentLocation.y+j[k]]->hasTower != 1){ //walkable area*/
/*			if(1){//not in closed list*/
/*				if(inOpenList(currentNode)){*/
/*					int currentPathCose = currentNode->startToNodeCost;*/
/*					int newPathCost = */
/*				}else{*/
/*					List *isInOpenList = popInList(currentNode, &openList);*/
/*					map[currentLocation.x+i][currentLocation.y+j]->parent = currentLocation;*/

/*					openList = addNodeInSortedList(currentNode, openList);*/
/*				}*/
/*			}*/
/*		}*/
/*	}*/
/*}*/



int isInList(Node *node, List *list){
	List *fundElement = popInList(node,&list);
	if(fundElement){
		addNodeInSortedList(node, list);
		return 1;
	}else{
		return 0;
	}
}

int isInOpenList(Node *node){
	return isInList(node, openList);
}

int isInClosedList(Node *node){
	return isInList(node, closedList);
}

SearchResult* searchNodeByXY(Node *nodeToFind, List *list){
	SearchResult *result = malloc(sizeof (SearchResult));
	result->previous = NULL;
	result->foundNode = list;
	result->next = list->nextList;
	
	// check the first item
	if(result->foundNode->item->x == nodeToFind->x && result->foundNode->item->y == nodeToFind->y){
		return result;
	}
	
	while(result->next != NULL){
		result->previous = result->foundNode;
		result->foundNode = result->next;
		result->next = result->next->nextList;
		if(result->foundNode->item->x == nodeToFind->x && result->foundNode->item->y == nodeToFind->y){
			return result;
		}
	}
	result->previous = NULL;
	result->foundNode = NULL;
 return result;
}

List* popInList(Node *nodeToFind, List **list){
	SearchResult *result = searchNodeByXY(nodeToFind, *list);
	// no found node
	if(result->foundNode == NULL){
		return NULL;
	}else{
		result->foundNode->nextList = NULL;
		// first node
		if(result->previous == NULL){
			*list = result->next;
		}else{
			result->previous->nextList = result->next;
		}
		return result->foundNode;
	}
 return NULL;
}

