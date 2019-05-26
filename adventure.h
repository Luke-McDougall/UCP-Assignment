/* *
 * Luke McDougall
 *
 * Header file for adventure.c. Defines types and functions used to store and manipulate
 * data for the TreasureHunter program.
 *
 * Last updated 25/05/2019
 * */


#include "linked_list.h"
#ifndef ADVENTURE
#define ADVENTURE
/* gear_slot is used to indicate the SLOT of a gear struct. Using an enum
 * allows me to avoid storing a string and worrying about memory allocation.
 * Another convenience is that the integer values for head, chest, legs and hands
 * match up with the indices gear of that slot will be stored in in the explorers
 * equipment array.
 */
enum gear_slot {head, chest, legs, hands};
struct gear;

/* compare pointer is a function pointer to a compare function that compares
 * the values of two gear structs. Each type of gear has a different function
 * pointer to a compare function for that type specifically.
 */
typedef char (*compare_pointer)(struct gear*, struct gear*);

/* gear is a struct use to store data about a piece of gear. */
typedef struct gear
        {
            char* detail;
            enum gear_slot slot;
            int value;
            compare_pointer compare;
        } gear;

/* item is a struct that stores data about an item. Items do not have a slot variable
 * and no compare function pointer
 */
typedef struct
        {
            char* detail;
            int value;
        } item;


/* explorer struct is used to store data about the explorer in TreasureHunter.
 * The x and y position of the explorer, the number of coins she's collected,
 * an array of pointers to gear structs call equipment is used to store the
 * gear collected. It is an array because there is a fixed upper limit to how 
 * many pieces of gear the explorer can have at any one time. A generic linked list
 * is used to store pointers to item structs because there is no limit to how
 * many items the explorer can pick up
 */
typedef struct 
        {
            int coins;
            int pos_x;
            int pos_y;
            gear **equipment; 
            LinkedList* items;
        } explorer;

/* the move struct is used to store the direction and magnitude of a particular 
 * movement. Storing the data this way makes it easier to read than a string.
 */
typedef struct
        {
            int mag;
            char dir;
        } move;
#endif


/* Function: explorer_init
 * Input: None
 * Output: explorer*
 * Allocates memory for an explorer struct and initialises it with default values.
 * Returns a pointer to this struct.
 */
explorer* explorer_init(void);

/* Function: print_explorer
 * Import: explorer*
 * Export: None
 * Prints the total number of coins collected, the total value of all items
 * and the total value of all gear stored in the passed struct to the console.
 */
void print_explorer(explorer*);

/* Function: compare_head/compare_chest/compare_legs/compare_hands
 * Import: gear*, gear*
 * Export: char
 * Compares the values of the passed gear structs and returns 1 if the first
 * struct is greater than the second. Returns 0 otherwise.
 */
char compare_head(gear*, gear*);
char compare_chest(gear*, gear*);
char compare_legs(gear*, gear*);
char compare_hands(gear*, gear*);

/* Function: gear_init
 * Import: char*, enum gear_slot, int
 * Export: gear*
 * Allocates memory for a gear struct and initializes it with the passed values.
 * Returns a pointer to this struct.
 */
gear* gear_init(char*, enum gear_slot, int);

/* Function: item_init
 * Import: char*, int
 * Export: item*
 * Allocates memory for a item struct and initializes it with the passed values.
 * Returns a pointer to this struct.
 */
item* item_init(char*, int);

/* Function: move_init
 * Import: int, char
 * Export: move*
 * Allocates memory for a move struct and initializes it with the passed values.
 * Returns a pointer to this struct.
 */
move* move_init(int, char);

/* Function: free_explorer
 * Import: explorer*
 * Export: None
 * Frees the memory allocated for the explorer struct and all the structs that 
 * the explorer contains pointers to. The other structs are freed by calling the
 * appropriate free function. After that the explorer struct is freed.
 */
void free_explorer(explorer*);

/* Function: free_gear
 * Import: gear*
 * Export: None
 * Frees the memory allocated for a gear struct, including the memory allocated
 * for it's detail field.
 */
void free_gear(gear*);

/* Function: free_item
 * Import: item*
 * Export: None
 * Frees the memory allocated for a item struct, including the memory allocated
 * for it's detail field.
 */
void free_item(item*);

/* Function: explorer_add_item
 * Import: explorer*, item*
 * Export: None
 * Inserts the passed item pointer into the passed explorers equipment linked list
 */
void explorer_add_item(explorer*, item*);

/* Function: explorer_gear_compare
 * Import: explorer*, gear*
 * Export: None
 * If the explorer has no gear struct stored in the corresponding slot to the 
 * slot of the passed gear struct the passed gear struct is stored in the explorer.
 * Otherwise the appropriate compare function is called from the passed gear structs
 * compare function pointer. The struct with the greater value is stored and the other
 * is freed.
 */
void explorer_gear_compare(explorer*, gear*);
