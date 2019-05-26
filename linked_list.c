/* *
 * Luke McDougall
 *
 * File containing functions for creating and managing a linked list
 *
 * Last updated 18/04/2019
 * */

#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"
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
    list -> size += 1;
}

/* function: removeFirst
 * Import: LinkedList *list
 * Export: void *value
 * Removes the first element of the passed linked list and returns the value. Returns NULL if list
 * is empty
 */
void* removeFirst(LinkedList* list)
{
    void *value = NULL;
    ListNode *temp;
    if(list -> head != NULL)
    {
        value = list -> head -> value;
        temp = list -> head;
        list -> head = list -> head -> next;
        free(temp);
        list -> size -= 1;
    }
    return value;
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
