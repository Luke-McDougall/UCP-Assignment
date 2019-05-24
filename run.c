#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "adventure.h"
#include "fileIO.h"
#include "run.h"

int main(int argc, char *argv[])
{
    int rows, cols, i, j, start_x, start_y;
    char*** map;
    LinkedList *movement_list;
    explorer *pc;
    move *m;

    map = map_init(argv[1], &rows, &cols);
    
    movement_list = load_movement(argv[2]);

    pc = explorer_init();

    
    printf("head %d, chest %d, hands %d, legs %d\n", head, chest, hands, legs);
    if(movement_list == NULL)
    {
        printf("this don't make no cents luv\n");
    }
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            if(map[i][j] != NULL)
            {
                printf("%s |", map[i][j]);
            }
            else
            {
                printf("-|");
            }
        }
        printf("\n");
    }
    if(map[0][0] != NULL)
    {
        update(pc, map[pc -> pos_y][pc -> pos_x]);
        free(map[pc -> pos_y][pc -> pos_x]);
        map[pc -> pos_y][pc -> pos_x] = NULL;
    }
 
    do
    {
        m = (move*)removeFirst(movement_list);
        switch(m -> dir)
        {
            case 'l':
            start_x = pc -> pos_x;
            for(i = start_x; i > start_x - m -> mag; i--)
            {
                pc -> pos_x -= 1;
                if(map[pc -> pos_y][pc -> pos_x] != NULL)
                {
                    update(pc, map[pc -> pos_y][pc -> pos_x]);
                    free(map[pc -> pos_y][pc -> pos_x]);
                    map[pc -> pos_y][pc -> pos_x] = NULL;
                }
            }
            break;
            
            case 'r':
            start_x = pc -> pos_x;
            for(i = start_x; i < start_x + m -> mag; i++)
            {
                pc -> pos_x += 1;
                if(map[pc -> pos_y][pc -> pos_x] != NULL)
                {
                    update(pc, map[pc -> pos_y][pc -> pos_x]);
                    free(map[pc -> pos_y][pc -> pos_x]);
                    map[pc -> pos_y][pc -> pos_x] = NULL;
                }
            }
            break;

            case 'u':
            start_y = pc -> pos_y;
            for(i = start_y; i > start_y - m -> mag; i--)
            {
                pc -> pos_y -= 1;
                if(map[pc -> pos_y][pc -> pos_x] != NULL)
                {
                    update(pc, map[pc -> pos_y][pc -> pos_x]);
                    free(map[pc -> pos_y][pc -> pos_x]);
                    map[pc -> pos_y][pc -> pos_x] = NULL;
                }
            }
            break;
    
            case 'd':
            start_y = pc -> pos_y;
            for(i = start_y; i < start_y + m -> mag; i++)
            {
                pc -> pos_y += 1;
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
        sscanf(entry, "%*[c|C]%d", &value);
        pc -> coins += value;
    }
    else if(n == 2)
    {
        sscanf(entry, "%*[m|M^]%[^:]", buffer);
        sscanf(entry, "%*[^:]:%d", &value);
        temp = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
        strncpy(temp, buffer, strlen(buffer) + 1);
        i = item_init(temp, value);
        explorer_add_item(pc, i); 
    }
    else
    {
        sscanf(entry, "%*[g|G^]%[^:]", buffer);
        temp = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
        strncpy(temp, buffer, strlen(buffer) + 1);
        sscanf(entry, "%*[^:]:%[^:]", buffer);
        temp2 = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
        strncpy(temp2, buffer, strlen(buffer) + 1);
        sscanf(entry, "%*[^:]:%*[^:]:%d", &value);
        for(n = 0; n < strlen(temp2); n++)
        {
            if(temp2[n] >= 97 && temp2[n] <= 122)
            {
                temp2[n] -= 32;
            }
        }
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
