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

List* addNodeInSortedList(Node *node, List *list);

#endif /* __pathFinding_H__ */

