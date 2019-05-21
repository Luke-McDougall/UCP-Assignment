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
            unsigned short value;
            compare_pointer compare;
        } gear;

typedef struct
        {
            char* detail;
            unsigned short value;
        } item;

#include "linked_list.h"

typedef struct 
        {
            unsigned short coins;
            unsigned short pos_x;
            unsigned short pos_y;
            gear **equipment; 
            LinkedList* items;
        } explorer;
#endif


explorer* explorer_init(void);
void print_explorer(explorer*);
char compare_head(gear*, gear*);
char compare_chest(gear*, gear*);
char compare_legs(gear*, gear*);
char compare_hands(gear*, gear*);
gear* gear_init(char*, enum gear_slot, unsigned short);
item* item_init(char*, unsigned short);
void free_explorer(explorer*);
void free_gear(gear*);
void free_item(item*);
void explorer_add_item(explorer*, item*);
