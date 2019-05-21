#include "adventure.h"
#include "fileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    explorer *dude;
    gear *g, *g2;
    item *t, *t2;
    char *string, *string2, *string3, *string4;
    dude = explorer_init();
    print_explorer(dude);
    string = (char*)malloc(sizeof(char) * 10);
    string2 = (char*)malloc(sizeof(char) * 10);
    string3 = (char*)malloc(sizeof(char) * 10);
    string4 = (char*)malloc(sizeof(char) * 10);
    strcpy(string, "Oi, bruv");
    strcpy(string2, "Init bin");
    strcpy(string3, "AAAAAr");
    strcpy(string4, "BBBBBh");
    g = gear_init(string, head, 140);
    g2 = gear_init(string2, head, 120);
    t = item_init(string3, 230);
    t2 = item_init(string4, 125);
    explorer_add_item(dude, t);
    explorer_add_item(dude, t2);
    if( g2 -> compare(g2, g))
    {
        printf("%s %d\n", g2 -> detail, g2 -> value);
    }
    else
    {
        printf("%s %d\n", g -> detail, g -> value);
    }
    dude -> equipment[head] = g;    
    print_explorer(dude);
    free_explorer(dude);
    map_init("map.csv");
    free_gear(g2);
    return 0;
}
