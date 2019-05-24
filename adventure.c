/* Functions for adventure.h*/
#include <stdlib.h>
#include <stdio.h>
#include "adventure.h"
#define NUM_GEAR 4

explorer* explorer_init(void)
{
    int i;
    explorer *pc;
    pc = (explorer*)malloc(sizeof(explorer));
    pc -> coins = 0;
    pc -> pos_x = 0;
    pc -> pos_y = 0;
    pc -> equipment = (gear**)malloc(sizeof(gear*) * NUM_GEAR);
    for(i = 0; i < NUM_GEAR; i++)
    {
        pc -> equipment[i] = NULL;    
    }
    pc -> items = createList();
    return pc;
}

void explorer_add_item(explorer *pc, item* t)
{
    void *v = t;
    insertFirst(pc -> items, v);
}

void free_explorer(explorer *pc)
{
    int i, num_item = pc -> items -> size;
    for(i = 0; i < NUM_GEAR; i++)
    {
        if(pc -> equipment[i] != NULL)
        {
            free_gear(pc -> equipment[i]);
        }
    }
    for(i = 0; i < num_item; i++)
    {
        void *v = get(pc -> items, i);
        free_item((item*)v);
    }
    free(pc -> equipment);
    freeList(pc -> items);
    free(pc);
}

void print_explorer(explorer* pc)
{
    int i;
    int c = pc -> coins;
    int pos1 = pc -> pos_x;
    int pos2 = pc -> pos_y;
    int item_num = pc -> items -> size;
    printf("coins %d, x pos %d, y pos %d\n", c, pos1, pos2);
    for(i = 0; i < NUM_GEAR; i++)
    {
        if(pc -> equipment[i] != NULL)
        {
            printf("%s, value: %d\n", pc -> equipment[i] -> detail, pc -> equipment[i] -> value);
        }
        else
        {
            printf("Empty\n");
        }
    }

    for(i = 0; i < item_num; i++)
    {
        item *t = (item*)get(pc -> items, i);
        printf("%s, value: %d\n", t -> detail, t -> value);
    }
}

gear* gear_init(char* d, enum gear_slot s, int v)
{
    gear *g = (gear*)malloc(sizeof(gear));
    g -> detail = d;
    g -> slot = s;
    g -> value = v;
    switch(s)
    {
        case head:
            g -> compare = compare_head;
        break;

        case chest:
            g -> compare = compare_chest;
        break;

        case legs:
            g -> compare = compare_legs;
        break;

        case hands:
            g -> compare = compare_hands;
        break;
    }
    return g;
}

void free_gear(gear *g)
{
    free(g -> detail);
    free(g);
}

item* item_init(char *d, int v)
{
    item *t = (item*)malloc(sizeof(item));
    t -> detail = d;
    t -> value = v;
    return t;
}

void free_item(item *t)
{
    free(t -> detail);
    free(t);
}

move* move_init(int mag, char dir)
{
    move *m = (move*)malloc(sizeof(move));
    m -> mag = mag;
    m -> dir = dir;
    return m;
}

char compare_head(gear *hat, gear *hat2)
{
    return (hat -> value > hat2 -> value);
}

char compare_chest(gear *shirt, gear *shirt2)
{
    return (shirt -> value > shirt2 -> value);
}

char compare_legs(gear *pants, gear *pants2)
{
    return (pants -> value > pants2 -> value);
}

char compare_hands(gear *glove, gear *glove2)
{
    return (glove -> value > glove2 -> value);
}
