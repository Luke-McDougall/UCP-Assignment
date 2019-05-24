/*adventure stuff*/


#ifndef ADVENTURE
#define ADVENTURE
enum gear_slot {head, chest, legs, hands};
struct gear;
typedef char (*compare_pointer)(struct gear*, struct gear*);
typedef struct gear
        {
            char* detail;
            enum gear_slot slot;
            int value;
            compare_pointer compare;
        } gear;

typedef struct
        {
            char* detail;
            int value;
        } item;

#include "linked_list.h"

typedef struct 
        {
            int coins;
            int pos_x;
            int pos_y;
            gear **equipment; 
            LinkedList* items;
        } explorer;

typedef struct
        {
            int mag;
            char dir;
        } move;
#endif


explorer* explorer_init(void);
void print_explorer(explorer*);
char compare_head(gear*, gear*);
char compare_chest(gear*, gear*);
char compare_legs(gear*, gear*);
char compare_hands(gear*, gear*);
gear* gear_init(char*, enum gear_slot, int);
item* item_init(char*, int);
move* move_init(int, char);
void free_explorer(explorer*);
void free_gear(gear*);
void free_item(item*);
void explorer_add_item(explorer*, item*);
