#ifndef __pathFinding_H__
#define __pathFinding_H__
#include "map.h"

typedef struct{
	int x,y;
	int startToNodeCost;
	int nodeToEndCost;
}Node;

typedef struct list{
	Node *item;
	struct list *nextList;
}List;

typedef struct{
	List *previous, *foundNode, *next;
}SearchResult;

void searchPath(Map **map, Position start, Position end);

SearchResult* searchNodeByXY(Node *nodeToFind, List *list);
List* addNodeInSortedList(Node *node, List *list);
List* newList(Node *firstItem);
List* popInList(Node *nodeToFind, List **list);
Node* popFirstInList(List **list);

int estimatedPathCost(Node *adjacentNode, Node *endNode);
int isInList(Node *node, List *list);
int isInOpenList(Node *node);
int isInClosedList(Node *node);

#endif /* __pathFinding_H__ */

