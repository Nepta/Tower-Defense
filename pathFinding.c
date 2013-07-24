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
	 	goto newNode;
	}

	// running through the list
	while(runningThroughList->nextList != NULL){
		Node *nextNode = runningThroughList->nextList->item;
		int nextListCost = nextNode->startToNodeCost + nextNode->nodeToEndCost;
		if(newNodeCost <= nextListCost){
			newList->nextList = runningThroughList->nextList;
			runningThroughList->nextList = runningThroughList;
			goto newNode;
		}
		runningThroughList = runningThroughList->nextList;
	}
	
	//adding node at the end
	newList->nextList = NULL;
	runningThroughList->nextList = newList;
	newNode:
	return newList;
}

