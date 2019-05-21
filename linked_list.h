#ifndef LINKED_LIST
#define LINKED_LIST
typedef struct ListNode
        {
            void *value;
            struct ListNode *next;
        } ListNode;

typedef struct
        {
            ListNode *head;
            int size;
        } LinkedList;
#endif
LinkedList* createList(void);
void insertFirst(LinkedList*, void*);
void printList(LinkedList*);
LinkedList* removeFirst(LinkedList*);
void* get(LinkedList*, int);
void freeList(LinkedList*);
void insertLast(LinkedList*, void*);
