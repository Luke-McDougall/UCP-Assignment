/* *
 * Luke McDougall
 *
 * Header file for file I/O function declarations
 *
 * Last updated 25/05/2019
 * */

/* Function: map_init
 * Import: char*, int*, int*
 * Export: char***(2d array of strings)
 * Reads and validates data from a map file. If the file is successfully validated
 * a 2d array of strings containing the data in the file will be returned. The
 * dimensions of the array are stored at the memory addresses of the two passed
 * int pointers.
 */
char*** map_init(char*, int*, int*);

/* Function: free_map
 * Import: char***, int, int
 * Export: None
 * Frees all strings stored in the array and frees the array itself. The two int
 * parameters are the dimensions of the array.
 */
void free_map(char***, int, int);

/* Function: validate_struct
 * Import: char*
 * Export: int
 * Parses the passed string to determine if it can be stored as a struct. If it
 * can this function returns 1. Otherwise returns 0.
 */
int validate_struct(char*);

/* Function: load_movement
 * Import: char*
 * Export: LinkedList*
 * Parses the data in a file specifiied by the passed string and validates it.
 * If any of the lines in the file are invalid the function will return NULL.
 * Otherwise all of the lines will be stored as move struct pointers in a generic
 * linked list and the function returns the linked list.
 */
LinkedList* load_movement(char*);

/* Function: write_coins
 * Import: int, int, int
 * Export: None
 * Formats a string with the passed integer values to be sent to the write_log
 * function to be written to the log file.
 */
void write_coins(int, int, int);

/* Function: write_item
 * Import: int, int, int
 * Export: None
 * Formats a string with the passed item struct and integer values to be sent to the write_log
 * function to be written to the log file.
 */
void write_item(item*, int, int);

/* Function: write_gear
 * Import: int, int, int
 * Export: None
 * Formats a string with the passed gear struct and integer values to be sent to the write_log
 * function to be written to the log file.
 */
void write_gear(gear*, int, int, int);

/* Function: write_log
 * Import: char* 
 * Export: None
 * Writes the passed string to the log file.
 */
void write_log(char*);
