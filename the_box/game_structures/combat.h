

int combat_status = 0 ; // default won

int attack = 0 ; // default auto

int attack_range = 1; // 

Character *active_character; // F

/* size of combat area */

#define COMBAT_WIDTH  38
#define COMBAT_HEIGHT 16

/* center of combat area */

#define COMBAT_C_X    19
#define COMBAT_C_Y     8


int combat_area[COMBAT_WIDTH][COMBAT_HEIGHT];
int combat_stack[COMBAT_WIDTH * COMBAT_HEIGHT][2];
int combat_stack_start;
int combat_stack_size;

int combat_x, combat_y;
int combat_leader_x;
int combat_leader_y;