#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adventure.h"
#include "fileIO.h"
#define TRUE 1
#define FALSE 0

static char* read_line(FILE *map)
{
    int pos = 1, ch;
    char *line = NULL;
    ch = fgetc(map);
    while(ch != '\n' && ch != EOF)   /*Exit loop at newline character*/
    {
        pos++;
        ch = fgetc(map);
    }
    if(pos > 1)
    {
        line = (char*)malloc(sizeof(char) * pos + 1);   /*Allocate memory for line*/
        fseek(map, (-1)*pos, SEEK_CUR);  /*Return pointer to beginning of line*/
        fgets(line, pos, map);   /*Fill line with chars from the file*/
        fseek(map, 1, SEEK_CUR); /*Continue to next line*/
    }
    return line;
}

static int validate_dimensions(FILE *map, int cols, int rows)
{
    char c = fgetc(map);
    int valid = TRUE;
    int len = 1, height = 0;
    while(c != EOF && valid)
    {
        height++;
        while(c != '\n' && c != EOF)
        {
            if(c == ',')
                len++;
            c = fgetc(map);
        }
        if(len != cols)
        {
            valid = FALSE;
        }
        len = 1;
        c = fgetc(map);
    }

    if(height != rows)
    {
        valid = FALSE;
    }
    return valid;
}

char*** map_init(char *filename, int *rows, int *cols)
{
    int n, m, i, j, valid = TRUE;
    char ***map_array;
    char *start, *end, *line;
    FILE *map = fopen(filename, "r");
    if(map == NULL)
    {
        perror("Error in file processing: ");
    }
    else
    {
        n = fscanf(map, "%d,", rows);
        m = fscanf(map, "%d", cols);
        if(n == 1 && m == 1)
        {
            fseek(map, 1, SEEK_CUR);
            
            
            if(validate_dimensions(map, *cols, *rows))
            { 
                map_array = (char***)calloc(*rows, sizeof(char**));
                for(i = 0; i < *rows; i++)
                {
                    map_array[i] = (char**)calloc(*cols, sizeof(char*));
                }
                fseek(map, 0, SEEK_SET);
                while(fgetc(map) != '\n');
                line = read_line(map);
                i = 0;
                j = 0;
                start = line; 
                end = strchr(start, ',');
                while(i < *rows)
                {
                    if(end == NULL && strlen(start) > 1)
                    {
                        start = *start == ',' ? start + 1 : start;
                        map_array[i][j] = (char*)calloc((strlen(start) + 1), sizeof(char));
                        strncpy(map_array[i][j], start, strlen(start));
                        map_array[i][j][strlen(start)] = '\0';
                    }
                    if((end - start) > 1)
                    {
                        start = *start == ',' ? start + 1 : start;
                        map_array[i][j] = (char*)calloc((end - start + 1), sizeof(char));
                        strncpy(map_array[i][j], start, end - start);
                        map_array[i][j][end - start] = '\0';
                    }
                    
                    j++;
                    if(j == *cols)
                    {
                        j = 0;
                        i++;
                        free(line);
                        line = read_line(map);
                        start = line;
                        if(start != NULL)
                        {
                            end = strchr(line, ',');
                        }
                    }
                    else
                    {
                        start = end;
                        end = strchr(start + 1, ',');
                    }
                }
                for(i = 0; i < *rows; i++)
                {
                    for(j = 0; j < *cols; j++)
                    {
                        if(map_array[i][j] != NULL)
                        {
                            if(!validate_struct(map_array[i][j]))
                            {
                                valid = FALSE;
                            }
                        }
                    }
                }
            }
            else
            {
               printf("Error: invalid file format at %s!\n", filename); 
            }
            
        }
        else
        {
            printf("Error: invalid file format at %s!\n", filename);
        }
    }
    fclose(map);
    if(!valid)
    {
        free_map(map_array, *rows, *cols);
        map_array = NULL;
        printf("Error: invalid file format!\n");
    }
    return map_array;
}

int validate_struct(char* entry)
{
    int valid = TRUE, value, n = 1, i;
    char c;
    char buffer[128];
    char *temp = strchr(entry, ':');
    while(temp != NULL)
    {
        n++;
        temp = strchr(temp + 1, ':');
    }
    if(n == 1)
    {
        n = sscanf(entry, "%c %d", &c, &value);
        if(n == 2)
        {
            if(c != 'c' && c != 'C')
            {
                valid = FALSE;
            }
            
            if(value < 0)
            {
                valid = FALSE;    
            }
        }
    }
    else if(n == 2)
    {
        n = sscanf(entry, "%c", &c);
        if(n == 1)
        {
            n = sscanf(entry, "%*[m|M^]%[^:]", buffer);
        }
        else
        {
            valid = FALSE;
        }

        if(n == 1)
        {
            n = sscanf(entry, "%*[^:]:%d", &value);
        }
        else
        {
            valid = FALSE;
        }

        if(n != 1)
        {
            valid = FALSE;
        }
        else if(value < 0)
        {
            valid = FALSE;
        }
        
    }
    else if(n == 3)
    {
        n = sscanf(entry, "%c", &c);
        if(n == 1)
        {
            n = sscanf(entry, "%*[g|G^]%[^:]", buffer);
        }
        else
        {
            valid = FALSE;
        }
        
        if(n == 1)
        {
            sscanf(entry, "%*[^:]:%[^:]", buffer);
            for(i = 0; i < strlen(buffer); i++)
            {
                if(buffer[i] >= 97 && buffer[i] <= 122)
                {
                    buffer[i] -= 32;
                }
            }
            n = strstr(buffer, "HANDS") || strstr(buffer, "HEAD") || strstr(buffer, "CHEST") || strstr(buffer, "LEGS");
        }
        else
        {
            valid = FALSE;
        }

        if(n == 1)
        {
            n = sscanf(entry, "%*[^:]:%*[^:]:%d", &value);
        }
        else
        {
            valid = FALSE;
        }
        
        if(n != 1)
        {
            valid = FALSE;
        }
        else if(value < 0)
        {
            valid = FALSE;
        }
    }
    else
    {
        valid = FALSE;
    }

    return valid;
}

void free_map(char*** map_array, int rows, int cols)
{
    int i, j;
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            if(map_array[i][j] != NULL)
            {
                free(map_array[i][j]);
            }
        }
        free(map_array[i]);
    }
    free(map_array);
}

LinkedList* load_movement(char *filename)
{
    LinkedList *movement_list = NULL;
    FILE *movement = fopen(filename, "r");
    int valid = TRUE, mag, n, i;
    char dir;
    char buffer[6]; /*length of "right"*/
    move *m;
    if(movement != NULL)
    {
        movement_list = createList();
        n = fscanf(movement, "%s %d", buffer, &mag);
        if(n != 2)
        {
            valid = FALSE;
        }
        while(n == 2 && valid)
        {
            
            for(i = 0; i < strlen(buffer); i++)
            {
                if(buffer[i] >= 97 && buffer[i] <= 122)
                {
                    buffer[i] -= 32;
                }
            }
            if(strstr(buffer, "LEFT") != NULL)
            {
                dir = 'l';
            }
            else if(strstr(buffer, "RIGHT") != NULL)
            {
                dir = 'r';
            }
            else if(strstr(buffer, "UP") != NULL)
            {
                dir = 'u';
            }
            else if(strstr(buffer, "DOWN") != NULL)
            {
                dir = 'd';
            }
            else
            {
                valid = FALSE;
            }
            
            if(mag < 0)
            {
                valid = FALSE;
            }
            if(valid)
            {
                m = move_init(mag, dir);
                insertLast(movement_list, m);
            }
            
            n = fscanf(movement, "%s %d", buffer, &mag);
        }
        fclose(movement);
    }
    else
    {
        perror("Error in file processing: ");
    }

    if(!valid)
    {
        printf("Invalid file format at %s\n", filename);
        for(i = 0; i < movement_list -> size; i++)
        {
            free((move*)get(movement_list, i));
        }
        freeList(movement_list);
        movement_list = NULL;
    }
    return movement_list;
}

void write_coins(int coins, int x, int y)
{
    char buffer[128];
    sprintf(buffer, "COLLECT<COINS, XLOC: %d, YLOC: %d, VALUE: %d>", x, y, coins);
    write_log(buffer);
}

void write_item(item *i, int x, int y)
{
    char buffer[128];
    sprintf(buffer, "COLLECT<ITEM, XLOC: %d, YLOC: %d, DESCRIPTION:%s, VALUE: %d>", x, y, i -> detail, i -> value);
    write_log(buffer);
}

void write_gear(gear *g, int x, int y, int discard)
{
    char buffer[128];
    char *slot[4] = {"head", "chest", "legs", "hands"};
    if(discard)
    {
        sprintf(buffer, "DISCARD<GEAR, XLOC: %d, XLOC: %d, DESCRIPTION:%s, SLOT: %s, VALUE: %d>", x, y, g -> detail, slot[g -> slot], g -> value);
    }
    else
    {
        sprintf(buffer, "COLLECT<GEAR, XLOC: %d, XLOC: %d, DESCRIPTION:%s, SLOT: %s, VALUE: %d>", x, y, g -> detail, slot[g -> slot], g -> value);
    }
    write_log(buffer);
}

void write_log(char *entry)
{
    FILE *log = NULL;
    log = fopen("adventure.log", "a");
    if(log != NULL)
    {
        fprintf(log, "%s\n", entry);
        #ifdef TreasureHunterLog
        printf("%s\n", entry);
        #endif
    }
    else
    {
        perror("Error in file processing: ");
    }
    fclose(log);
}
