#include "pathFinding.h"
#include "map.h"
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

void searchPath(Map **map, Position start, Position end){
	Node *startNode = newNode(start.x, start.y);
	Node *endNode = newNode(end.x, end.y);
	openList = newList(endNode);
	closedList = NULL;
	
	int i[] = {0,1,0,-1};
	int j[] = {1,0,-1,0};
	do{
		Node *currentNode = popFirstInList(&openList);
		closedList = addNodeInSortedList(currentNode, closedList);
		for(int k=0; k<4; k++){
			Position currentLocation = {currentNode->x, currentNode->y};
			Node *adjacentNode = newNode(currentNode->x + i[k], currentNode->y + j[k]);
			int newPathCost = currentNode->startToNodeCost + 1;
/*			adjacentNode->startToNodeCost = newPathCost;*/
			if(!dontComputeNode(map,adjacentNode)){ //walkable area and non computed node
				if(isInOpenList(adjacentNode)){
					Node *inOpenListNode = popInList(adjacentNode, &openList)->item;
					if(newPathCost < adjacentNode->startToNodeCost){ //using new path is better
						adjacentNode->nodeToEndCost = inOpenListNode->nodeToEndCost;
						map[adjacentNode->x][adjacentNode->y].parent = currentLocation;
						openList = addNodeInSortedList(adjacentNode, openList);
					}else{ // we put the note where we took from
						openList = addNodeInSortedList(inOpenListNode, openList);
					}
				}else{
					adjacentNode->nodeToEndCost = estimatedPathCost(adjacentNode, startNode);
					openList = addNodeInSortedList(adjacentNode, openList);
					map[adjacentNode->x][adjacentNode->y].parent = currentLocation;
				}
			}
		}
	}while(!(isInOpenList(startNode) || openList == NULL));
}

int dontComputeNode(Map **map, Node *node){
	int walkable = map[node->x][node->y].hasTower != 1;
	int alreadyComputed = isInClosedList(node) == 1;
	int alreadyComputedInAnotherLoop = map[node->x][node->y].x != node->x
											  && map[node->x][node->y].y != node->y;
 return !walkable || alreadyComputed || alreadyComputedInAnotherLoop;
}

Node* popFirstInList(List **list){
	return popInList((*list)->item, list)->item;
}

int estimatedPathCost(Node *adjacentNode, Node *endNode){
	// manathan path cost
/*	int cost = abs(endNode->x - adjacentNode->x) + abs(endNode->y - adjacentNode->y);*/
	// square bird fly 
	int cost = ((endNode->x - adjacentNode->x)*(endNode->x - adjacentNode->x)) + ((endNode->y - adjacentNode->y)*(endNode->y - adjacentNode->y));
 return cost;
}

int isInList(Node *node, List *list){
	SearchResult *result = searchNodeByXY(node, list);
 return result->foundNode != NULL;
}

int isInOpenList(Node *node){
	return isInList(node, openList);
}

int isInClosedList(Node *node){
	return isInList(node, closedList);
}

SearchResult* searchNodeByXY(Node *nodeToFind, List *list){
	SearchResult *result = malloc(sizeof (SearchResult));
	
	//check for empty list
	if(list == NULL){
		result->previous = NULL;
		result->foundNode = NULL;
		result->next = NULL;
		return result;
	}
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
}

