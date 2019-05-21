#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "adventure.h"
#define TRUE 1
#define FALSE 0

static char* read_line(FILE *map)
{
    int pos = 1, ch;
    char *line = NULL;
    ch = fgetc(map);
    while(ch != '\n')   /*Exit loop at newline character*/
    {
        pos++;
        ch = fgetc(map);
    }
    line = (char*)malloc(sizeof(char) * pos + 1);   /*Allocate memory for line*/
    fseek(map, (-1)*pos, SEEK_CUR);  /*Return pointer to beginning of line*/
    fgets(line, pos, map);   /*Fill line with chars from the file*/
    fseek(map, 1, SEEK_CUR); /*Continue to next line*/
    return line;
}

static char validate_line(FILE *map, int cols)
{
    char *line = NULL, *temp, *temp2;
    char valid = TRUE, id;
    int len = 1, val;
    line = read_line(map);
    
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
    
    temp = strtok(line, ",");
    while(temp != NULL)
    {
        temp2 = strtok(temp, ":");
        if(temp2 != NULL)
        {
            
        }
        else
        {
            if(!(sscanf(temp2, "%c %d", &id, &val) && (id == 'C' || id == 'c')))
            {
                valid = FALSE;
            }
        }
    } 
    free(line);
}

void validate_map(char *filename)
{
    int rows, cols, n, m;
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
            validate_line(map, cols);
            /*void ***map_array = (void***)malloc(sizeof(void**) * rows);
            for(i = 0; i < cols; i++)
            {
                map_array[i] = (void**)malloc(sizeof(void*) * cols);
            }*/
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

