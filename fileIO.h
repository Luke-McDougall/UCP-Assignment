char*** map_init(char*, int*, int*);
void free_map(char***, int, int);
void print_map(char***, int, int);
int validate_struct(char*);
LinkedList* load_movement(char*);
void write_coins(int, int, int);
void write_item(item*, int, int);
void write_gear(gear*, int, int, int);
void write_log(char*);
