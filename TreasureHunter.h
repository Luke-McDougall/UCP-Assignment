#ifdef TreasureHunter

#define CONDITION movement_list -> size > 0 && s == COMPLETE

#endif

#ifdef TreasureHunterAI

#define CONDITION movement_list -> size > 0 && (s == COMPLETE || s == CORRECTED)

#endif 

/* Function: update
 * Import: explorer*, char*
 * Export: None
 * Parses the passed string and passes the appropriate values to the appropiate
 * init function. Then passes the explorer and the struct to either explorer_add_item
 * or explorer_compare_gear
 */
void update(explorer*, char*);

/* Function: print_map
 * Import: char***, int, int
 * Export: None
 * Prints the content of the passed 2d array to the console. The two int parameters
 * are the arrays length and height. Only used for debugging.
 */
void print_map(char***, int, int);
