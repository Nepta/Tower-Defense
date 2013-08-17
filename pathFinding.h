#ifndef __pathFinding_H__
#define __pathFinding_H__
#include "map.h"

/**
 * a node represent a step in the pathfinding algorithm,
 * in a 2D map it is a cell of the map
 */
typedef struct{
	int x,y;					//!< x position of the node //!< y position of the node
	int startToNodeCost;	//!< computed cost to go to this node starting from the start
	int nodeToEndCost;	//!< estimated cost to go to the end from this node
}Node;

/**
 * \brief linked list implementation
 * list without header, there are a container that link to the next an contain a node
 */
typedef struct list{
	Node *item;					//!< a item of the list
	struct list *nextList;	//!< the next element linked in the list
}List;

/**
 * struct that facilitate the search in a list by memorizing element near the
 * one which is tested
 */
typedef struct{
	List *previous, *foundNode, *next; //!< previous element of the list //!< current looking at element //!< next element of the list
}SearchResult;

/**
 * \brief A* algorithm implementation
 * the algorithm search through a map the best way to go through it and mark the path directly on the map
 * \param map a map to find a path
 * \param start the start position of the algorithm
 * \param end the end position of the algorithm
 */
void searchPath(Map **map, Position start, Position end);


/**
 * search a node in a list comparing its coordinate
 * \param nodeToFind a node to find in the list
 * \param list the list to search the node
 * \return the node and it's neighbor if found, NULL otherwise
 */
SearchResult* searchNodeByXY(Node *nodeToFind, List *list);

/**
 * add a node in a list keeping it sorted (by node cost)
 * \param node the node to be added in the list
 * \param list a list to add an item
 * \return the new head of the list
 */
List* addNodeInSortedList(Node *node, List *list);

/**
 * create a new list with a first element
 * \param firstItem first item to be inserted in the new list
 * \return the new list
 */
List* newList(Node *firstItem);

/**
 * remove an item from the list matching similar node with (x,y) coordinate
 * \param nodeToFind a node to find (other similar node)
 * \param list a list to search into
 * return the removed node of the list
 */
List* popInList(Node *nodeToFind, List **list);

/**
 * remove the first element of a list
 * \param the list to remove the element
 * \return the element removed
 */
Node* popFirstInList(List **list);


/**
 * computed the heuristic cost for pathfinding algorithm
 * \param adjacentNode the node that need an heuristic estimation
 * \param endNode the ending node for heuristic estimation
 *\ return the heuristic cost
 */
int estimatedPathCost(Node *adjacentNode, Node *endNode);

/**
 * search if a node is in a list (according it's (x,y) coordinate
 * \param node the node to search
 * \param list the list to search
 * \return 0 if node not found
 */
int isInList(Node *node, List *list);

/**
 * wrapper to search if a node is in the openList
 * \param node the node to search
 * \return 0 if node not found
 */
int isInOpenList(Node *node);

/**
 * wrapper to search if a node is in the closedList
 * \param node the node to search
 * \return 0 if node not found
 */
int isInClosedList(Node *node);

/**
 * tell if a node have to be computed or not
 * \param map the map where pathFinding is calculated
 * \param node a node to test
 * \return 0 if node as to be set aside
 */
int dontComputeNode(Map **map, Node *node);

#endif /* __pathFinding_H__ */

