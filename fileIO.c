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

static int validate_line(FILE *map, int cols, int rows)
{
    char *line = NULL, *temp;
    int valid = TRUE;
    int len = 1, height = 0;
    line = read_line(map);
    while(line != NULL && valid)
    {
        height++;
        temp = strchr(line, ',');
        while(temp != NULL)
        {   
            len++;
            temp = strchr(temp + 1, ',');
        }
        
        if(len != cols)
        {
            valid = FALSE;
        }
        len = 1;
        free(line);
        line = read_line(map);
    }

    if(height != rows)
    {
        valid = FALSE;
    }
    return valid;
}

void validate_map(char *filename)
{
    int rows, cols, n, m, i, j;
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
                        
            
            if(validate_line(map, cols, rows))
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
                        map_array[i][j] = (char*)calloc((end - start + 1), sizeof(char));
                        strncpy(map_array[i][j], *start == ',' ? start + 1 : start, end - start);
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
                print_map(map_array, rows, cols);
            }
            else
            {
               printf("Invalid file\n"); 
            }
            
        }
        else if(errno != 0)
        {
            perror("fscanf");
        }
        else
        {
            fprintf(stderr, "Error: invalid file format!\n");
        }
    }
    fclose(map);
}

void print_map(char*** map_array, int rows, int cols)
{
    int i, j; 
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            if(map_array[i][j] != NULL)
            {
                printf("%s x = %d, y = %d\n", map_array[i][j], j, i);
            }
        }
    }
    free_map(map_array, rows, cols);
}

/*int validate_struct(char* entry)
{
    int valid = TRUE;
    char c;
    char *start = entry;
    char *end = strchr(start, ':');
    if(end == NULL)
    {
        
    }
}*/

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

