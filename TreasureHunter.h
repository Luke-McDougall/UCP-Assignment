#ifdef TreasureHunter

#define CONDITION movement_list -> size > 0 && s == COMPLETE

#endif

#ifdef TreasureHunterAI

#define CONDITION movement_list -> size > 0 && (s == COMPLETE || s == CORRECTED)

#endif 

void update(explorer*, char*);
