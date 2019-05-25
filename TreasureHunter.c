#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "adventure.h"
#include "fileIO.h"
#include "TreasureHunter.h"

int main(int argc, char *argv[])
{
    enum status {COMPLETE, CORRECTED, FAILED, ABORTED};
    char *str_status[4] = {"COMPLETE", "CORRECTED", "FAILED", "ABORTED"};
    enum status s = COMPLETE;
    int rows, cols, i, start_x, start_y, end_x, end_y;
    char*** map = NULL;
    LinkedList *movement_list = NULL;
    explorer *pc = NULL;
    move *m;

    map = map_init(argv[1], &rows, &cols);
    if(map != NULL)
    {
        movement_list = load_movement(argv[2]);
        if(movement_list != NULL)
        {
            pc = explorer_init();
            write_log("---");
            if(map[0][0] != NULL)
            {
                update(pc, map[pc -> pos_y][pc -> pos_x]);
                free(map[pc -> pos_y][pc -> pos_x]);
                map[pc -> pos_y][pc -> pos_x] = NULL;
            }
        }
        else
        {
            s = ABORTED;
        }
    }
    else
    {
        s = ABORTED;
    }
     
    if(s == COMPLETE)
    {
        do
        {
            m = (move*)removeFirst(movement_list);
            switch(m -> dir)
            {
                case 'l':
                start_x = pc -> pos_x;
                end_x = start_x - m -> mag;
                #ifdef TreasureHunter
                if(end_x < 0)
                {
                    s = FAILED;
                }
                #endif
                #ifdef TreasureHunterAI
                if(end_x < 0)
                {
                    end_x = 0;
                    s = CORRECTED;
                }
                #endif
                if(s != FAILED)
                {
                    for(i = start_x; i > end_x; i--)
                    {
                        pc -> pos_x -= 1;
                        if(map[pc -> pos_y][pc -> pos_x] != NULL)
                        {
                            update(pc, map[pc -> pos_y][pc -> pos_x]);
                            free(map[pc -> pos_y][pc -> pos_x]);
                            map[pc -> pos_y][pc -> pos_x] = NULL;
                        }
                    }
                }
                break;
                
                case 'r':
                start_x = pc -> pos_x;
                end_x = start_x + m -> mag;
                #ifdef TreasureHunter
                if(end_x > cols - 1)
                {
                    s = FAILED;
                }
                #endif
                #ifdef TreasureHunterAI
                if(end_x > cols - 1)
                {
                    end_x = cols - 1;
                    s = CORRECTED;
                }
                #endif
                if(s != FAILED)
                {
                    for(i = start_x; i < end_x; i++)
                    {
                        pc -> pos_x += 1;
                        if(map[pc -> pos_y][pc -> pos_x] != NULL)
                        {
                            update(pc, map[pc -> pos_y][pc -> pos_x]);
                            free(map[pc -> pos_y][pc -> pos_x]);
                            map[pc -> pos_y][pc -> pos_x] = NULL;
                        }
                    }
                }
                break;

                case 'u':
                start_y = pc -> pos_y;
                end_y = start_y - m -> mag;
                #ifdef TreasureHunter
                if(end_y < 0)
                {
                    s = FAILED;
                }
                #endif
                #ifdef TreasureHunterAI
                if(end_y < 0)
                {
                    end_y = 0;
                    s = CORRECTED;
                }
                #endif
                if(s != FAILED)
                {
                    for(i = start_y; i > end_y; i--)
                    {
                        pc -> pos_y -= 1;
                        if(map[pc -> pos_y][pc -> pos_x] != NULL)
                        {
                            update(pc, map[pc -> pos_y][pc -> pos_x]);
                            free(map[pc -> pos_y][pc -> pos_x]);
                            map[pc -> pos_y][pc -> pos_x] = NULL;
                        }
                    }
                }
                break;
        
                case 'd':
                start_y = pc -> pos_y;
                end_y = start_y + m -> mag;
                #ifdef TreasureHunter
                if(end_y > rows - 1)
                {
                    s = FAILED;
                }
                #endif
                #ifdef TreasureHunterAI
                if(end_y > rows - 1)
                {
                    end_y = rows - 1;
                    s = CORRECTED;
                }
                #endif
                if(s != FAILED)
                {
                    for(i = start_y; i < end_y; i++)
                    {
                        pc -> pos_y += 1;
                        if(map[pc -> pos_y][pc -> pos_x] != NULL)
                        {
                            update(pc, map[pc -> pos_y][pc -> pos_x]);
                            free(map[pc -> pos_y][pc -> pos_x]);
                            map[pc -> pos_y][pc -> pos_x] = NULL;
                        }
                    }
                }
                break;
            }
            free(m);
        }while(CONDITION);
    }    
    if(map != NULL)
    {
        free_map(map, rows, cols);
    }

    if(movement_list != NULL)
    {
        freeList(movement_list);
    }

    #ifdef TreasureHunter
    if(s == COMPLETE)
    {
        printf("%s\n", str_status[s]);
        print_explorer(pc);
        free_explorer(pc);  
    }
    else if(pc != NULL)
    {
        printf("%s\n", str_status[s]);
        free_explorer(pc);
    }
    #endif
    #ifdef TreasureHunterAI
    if(s == COMPLETE || s == CORRECTED)
    {
        printf("%s\n", str_status[s]);
        print_explorer(pc);
        free_explorer(pc);  
    }
    else if(pc != NULL)
    {
        printf("%s\n", str_status[s]);
        free_explorer(pc);
    }
    #endif
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
        write_coins(value, pc -> pos_x, pc -> pos_y);
    }
    else if(n == 2)
    {
        sscanf(entry, "%*[m|M^]%[^:]", buffer);
        sscanf(entry, "%*[^:]:%d", &value);
        temp = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
        strncpy(temp, buffer, strlen(buffer) + 1);
        i = item_init(temp, value);
        explorer_add_item(pc, i);
        write_item(i, pc -> pos_x, pc -> pos_y); 
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
