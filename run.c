#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "adventure.h"
#include "fileIO.h"
#include "run.h"

int main(int argc, char *argv[])
{
    int rows, cols, i;
    char*** map;
    LinkedList *movement_list;
    explorer *pc;
    move *m;

    map = map_init(argv[1], &rows, &cols);
    
    movement_list = load_movement(argv[2]);

    pc = explorer_init();
    
    do
    {
        m = (move*)removeFirst(movement_list);
        switch(m -> dir)
        {
            case 'l':
            for(i = pc -> pos_x; i >= pc -> pos_x - m -> mag; i--)
            {
                if(map[pc -> pos_y][pc -> pos_x] != NULL)
                {
                    update(pc, map[pc -> pos_y][pc -> pos_x]);
                    free(map[pc -> pos_y][pc -> pos_x]);
                    map[pc -> pos_y][pc -> pos_x] = NULL;
                }
            }
            break;
            
            case 'r':
            for(i = pc -> pos_x; i <= pc -> pos_x + m -> mag; i++)
            {
                if(map[pc -> pos_y][pc -> pos_x] != NULL)
                {
                    update(pc, map[pc -> pos_y][pc -> pos_x]);
                    free(map[pc -> pos_y][pc -> pos_x]);
                    map[pc -> pos_y][pc -> pos_x] = NULL;
                }
            }
            break;

            case 'u':
            for(i = pc -> pos_y; i >= pc -> pos_y - m -> mag; i--)
            {
                if(map[pc -> pos_y][pc -> pos_x] != NULL)
                {
                    update(pc, map[pc -> pos_y][pc -> pos_x]);
                    free(map[pc -> pos_y][pc -> pos_x]);
                    map[pc -> pos_y][pc -> pos_x] = NULL;
                }
            }
            break;
    
            case 'd':
            for(i = pc -> pos_y; i <= pc -> pos_y + m -> mag; i++)
            {
                if(map[pc -> pos_y][pc -> pos_x] != NULL)
                {
                    update(pc, map[pc -> pos_y][pc -> pos_x]);
                    free(map[pc -> pos_y][pc -> pos_x]);
                    map[pc -> pos_y][pc -> pos_x] = NULL;
                }
            }
            break;
        }
        free(m);
    }while(movement_list -> size > 0);
    
    free_map(map, rows, cols);
    
    freeList(movement_list);
    
    print_explorer(pc);

    free_explorer(pc);  

    return 0;
}

void update(explorer *pc, char* entry)
{
    int value, n = 1;
    enum gear_slot s;
    char buffer[128];
    char *temp = strchr(entry, ':'), *temp2;
    item *i = NULL;
    gear *g = NULL;
    while(temp != NULL)
    {
        n++;
        temp = strchr(temp + 1, ':');
    }

    if(n == 1)
    {
        sscanf(entry, "%d", &value);
        pc -> coins += value;
    }
    else if(n == 2)
    {
        sscanf(entry, "%*[m|M^]%[^:]", buffer);
        sscanf(entry, "%*[^:]:%d", &value);
        temp = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
        i = item_init(temp, value);
        explorer_add_item(pc, i); 
    }
    else
    {
        sscanf(entry, "%*[g|G^]%[^:]", buffer);
        temp = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
        sscanf(entry, "%*[^:]:%[^:]", buffer);
        temp2 = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
        sscanf(entry, "%*[^:]:%*[^:]:%d", &value);
        if(strstr(temp2, "HANDS") != NULL)
        {
            s = hands;
        }
        else if(strstr(temp2, "HEAD") != NULL)
        {
            s = head;
        }
        else if(strstr(temp2, "CHEST") != NULL)
        {
            s = chest;
        }
        else
        {
            s = legs;
        }
        
        g = gear_init(temp, s, value);

        explorer_gear_compare(pc, g);
        free(temp2);
    }
}