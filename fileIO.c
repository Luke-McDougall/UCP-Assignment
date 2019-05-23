#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "fileIO.h"
#include "adventure.h"
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

char*** map_init(char *filename)
{
    int rows, cols, n, m, i, j, valid = TRUE;
    char ***map_array;
    char *start, *end, *line;
    FILE *map = fopen(filename, "r");
    if(map == NULL)
    {
        perror("Error in file processing: ");
    }
    else
    {
        errno = 0;
        n = fscanf(map, "%d,", &rows);
        m = fscanf(map, "%d", &cols);
        if(n == 1 && m == 1)
        {
            printf("rows %d, cols %d\n", rows, cols);
            fseek(map, 1, SEEK_CUR);
            
            
            fseek(map, 0, SEEK_SET);
            free(read_line(map));
                        
            
            if(validate_dimensions(map, cols, rows))
            { 
                map_array = (char***)calloc(rows, sizeof(char**));
                for(i = 0; i < rows; i++)
                {
                    map_array[i] = (char**)calloc(cols, sizeof(char*));
                }
                fseek(map, 0, SEEK_SET);
                while(fgetc(map) != '\n');
                line = read_line(map);
                i = 0;
                j = 0;
                start = line; 
                end = strchr(start, ',');
                while(i < rows)
                {
                    if((end - start) > 1)
                    {
                        start = *start == ',' ? start + 1 : start;
                        map_array[i][j] = (char*)calloc((end - start + 1), sizeof(char));
                        strncpy(map_array[i][j], start, end - start);
                        map_array[i][j][end - start] = '\0';
                    }
                    
                    j++;
                    if(j == cols)
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
                        if(end == NULL)
                        {
                            end = strchr(start, '\n');
                        }
                    }
                }
                for(i = 0; i < rows; i++)
                {
                    for(j = 0; j < cols; j++)
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
               printf("Error: invalid file format!\n"); 
            }
            
        }
        else if(errno != 0)
        {
            perror("fscanf");
        }
        else
        {
            printf("Error: invalid file format!\n");
        }
    }
    fclose(map);
    if(!valid)
    {
        free_map(map_array, rows, cols);
        map_array = NULL;
        printf("Error: invalid file format!\n");
    }
    return map_array;
}

/*void print_map(char*** map_array, int rows, int cols)
{
    int i, j; 
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            if(map_array[i][j] != NULL)
            {
                validate_struct(map_array[i][j]);
                printf("%s x = %d, y = %d\n", map_array[i][j], j, i);
            }
        }
    }
    free_map(map_array, rows, cols);
}*/

int validate_struct(char* entry)
{
    int valid = TRUE, value, n = 1;
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
        if(n != 2)
        {
            if(c != 'c' && c != 'C')
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
            printf("%s\n", buffer);
            n = sscanf(entry, "%*[^:]:%[^:]", buffer);
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

