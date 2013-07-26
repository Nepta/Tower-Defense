#ifndef __pathFinding_H__
#define __pathFinding_H__

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


SearchResult* searchNode(List *list);
List* addNodeInSortedList(Node *node, List *list);
List* newList(Node *firstItem);
List* popInList(Node *nodeToFind, List **list);
SearchResult* searchNodeByXY(Node *nodeToFind, List *list);

int estimatedPathCost(Node *adjacentNode, Node *endNode);
int isInList(Node *node, List *list);
int isInOpenList(Node *node);
int isInClosedList(Node *node);

#endif /* __pathFinding_H__ */

