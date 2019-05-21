/* *
 * Luke McDougall
 *
 * File containing functions for creating and managing a linked list
 *
 * Last updated 18/04/2019
 * */

#include "adventure.h"
#include <stdlib.h>
#include <stdio.h>
static void freeRecurse(ListNode *currNode);

/* function: createList
 * Import: None
 * Export: LinkedList* list;
 * Allocates memory for an empty linked list, initialises the fields and 
 * returns a pointer to it.
 */
LinkedList* createList(void)
{
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    list -> head = NULL;
    list -> size = 0;
    return list;
}

/* function: insertFirst
 * Import: LinkedList *list, void *j
 * Export: none
 * Allocates memory for a new list node and inserts it to the front of the 
 * passed linked list
 */
void insertFirst(LinkedList *list, void *j)
{
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    if(list -> head == NULL)
    {
        newNode -> value = j;
        newNode -> next = NULL;
    }
    else
    {
        newNode -> value = j;
        newNode -> next = list -> head;
    }
    list -> head = newNode;
    list -> size += 1;
}

/* function: insertLast
 * Import: LinkedList *list, void* j
 * Export: none
 * Iterates through the passed linked list and insert an element at the end
 */

void insertLast(LinkedList *list, void *j)
{
    ListNode *currNode = list -> head;
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode -> next = NULL;
    newNode -> value = j;
    if(currNode == NULL)
    {
        list -> head = newNode; 
    }
    else
    {
        while(currNode -> next != NULL)
        {
            currNode = currNode -> next;
        }
        currNode -> next = newNode;
    }
}

/* function: removeFirst
 * Import: LinkedList *list
 * Export: LinkedList *list
 * Removes the first element of the passed linked list. Returns NULL if list
 * is empty
 */
LinkedList* removeFirst(LinkedList* list)
{
    LinkedList *newList;
    ListNode *temp;
    if(list -> head == NULL)
    {
        newList = NULL;
    }
    else
    {
        free(list -> head -> value);
        temp = list -> head;
        list -> head = list -> head -> next;
        free(temp);
    }
    return newList;
}

/* function: get
 * Import: LinkedList *list, int i
 * Export: void *j
 * Iterates through linked list until ith element found and returns value
 * of that element. Returns NULL if element does not exist.
 */
void* get(LinkedList *list, int i)
{
    int k = 0;
    ListNode *currNode = list -> head;
    void *j = NULL;
    while(k <= i && currNode != NULL)
    {
        j = currNode -> value;
        currNode = currNode -> next;
        k++;
        
    }
    return j;
}

/* function: printList
 * Import: LinkedList *list
 * Export: none
 * Iterates over a linked list and prints the values of each node
 */
/*void printList(LinkedList *list)
{
    ListNode *currNode = list -> head;
    void *j;
    while(currNode != NULL)
    {
        j = currNode -> value;
        printf("%hd-%02hd-%02hd: %s\n", j -> year, j -> month, j -> day, j -> entry);
        currNode = currNode -> next;
    }
}*/

/* function: freeList
 * Import: LinkedList *list
 * Export: none
 * Front end for recursive freeList algorithm. Passes head of list to recursive
 * algorithm.
 */
void freeList(LinkedList *list)
{
    ListNode *currNode = list -> head;
    freeRecurse(currNode);
    free(list);
}

/* function: freeRecurse
 * Import: ListNode *currNode
 * Export: none
 * Recursively iterates through the list until currNode == NULL then frees
 * all nodes as recursion unwinds.
 */
static void freeRecurse(ListNode *currNode)
{
    if(currNode != NULL)
    {
        freeRecurse(currNode -> next);
        free(currNode);
    }
}
