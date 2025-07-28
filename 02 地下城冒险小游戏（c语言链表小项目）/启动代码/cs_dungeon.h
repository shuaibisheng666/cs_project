<<<<<<< HEAD
#ifndef DUNGEON_H
#define DUNGEON_H

//
// DO NOT CHANGE THIS FILE
//
// You do not submit this file. This file is not marked.
// If you think you need to change this file you have
// misunderstood the assignment - ask in the course forum.
//
// Assignment 2 25T1 DPST1091: CS Dungeon
// cs_dungeon.h
//
// You must not change this file.
//
// Version 1.0.0: Release

////////////////////////////////////////////////////////////////////////////////
//                                 Constants                                  //
////////////////////////////////////////////////////////////////////////////////

#define DEFAULT -1
#define MAX_STR_LEN 32

#define MIN_MONSTERS 1
#define MAX_MONSTERS 10

#define MIN_ITEM_POINT_VALUE 1
#define MAX_ITEM_POINT_VALUE 10

#define MAX_HEALTH 50

// User commands
#define NEXT_DUNGEON '>'
#define PREVIOUS_DUNGEON '<'
#define PHYSICAL_ATTACK '!'
#define MAGICAL_ATTACK '#'

// Return values

// Standard return values
#define VALID 0
#define INVALID 1

// Creating and adding dungeons and items
#define INVALID_NAME 1
#define INVALID_MONSTER 2
#define INVALID_AMOUNT 3
#define INVALID_POSITION 4
#define INVALID_ITEM 1
#define INVALID_DUNGEON 2
#define INVALID_POINTS 3

// Ending the game
#define CONTINUE_GAME 0
#define PLAYER_DEFEATED 1
#define WON_MONSTERS 3
#define WON_BOSS 4

// Fighting final boss
#define NO_BOSS 1
#define NO_ITEM 2

// Provided enums:

// Represents the different types of monsters that can be encountered in the 
// dungeons. 
// The enum value represents both the monster's damage and health points.
enum monster_type {
    SLIME = 1,
    GOBLIN,
    SKELETON,
    WOLF,
};

// Represents the different types of items that can be found in the dungeons.
enum item_type {
    PHYSICAL_WEAPON,
    MAGICAL_TOME,
    ARMOR,
    HEALTH_POTION,
    TREASURE,
};

////////////////////////////////////////////////////////////////////////////////
//                            Struct Definitions                              //
////////////////////////////////////////////////////////////////////////////////

// Stores information about the dungeon map the game is played in.
struct map {
    // the name of the map
    char name[MAX_STR_LEN];

    // the list of dungeons within the map
    struct dungeon *entrance;

    // a pointer to the player who is exploring the map
    struct player *player;
    
    // the number of points required to win the game
    int win_requirement;
};

////////////////////////////////////////////////////////////////////////////////
//                             Stage 1 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Creates a new struct map
//
// Parameters:
//      name            - name of the dungeon map being created
//      win_requirement - amount of points required to win this game
//
// Returns:
//      a pointer to the newly created struct map
//
struct map *create_map(char *name, int win_requirement);

// Creates a new struct player
//
// Parameters:
//      name            - name of the player being created
//      class_type      - class that the player will play as, "Fighter"
//                        or "Wizard"
//
// Returns:
//      a pointer to the newly created struct player
//
struct player *create_player(char *name, char *class_type);

// Adds a new dungeon to the end of the list of dungeons contained within the 
// map
//
// Parameters:
//      map             - pointer to the dungeon map, containing list of  
//                        dungeons, the player, and the points required to win.
//      name            - name of the dungeon being added
//      monster         - type of monster the new dungeon should hold
//      num_monsters    - amount of monsters the dungeon should hold
//
// Returns:
//      INVALID_NAME when the name is already being used by a dungeon in the map
//      INVALID_MONSTER when the monster type is not one of:
//              - SLIME
//              - GOBLIN
//              - SKELETON
//              - WOLF
//      INVALID_AMOUNT when the amount of monsters is too small or too large
//      VALID otherwise (no errors found)
//
int append_dungeon(struct map *map, char *name, enum monster_type monster,
                   int num_monsters);

// Prints the list of dungeons contained within the map
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      nothing
//
void print_map(struct map *map);

// Adds the final boss to the last dungeon in the map
//
// Parameters:
//      map             - pointer to the dungeon map, containing list of  
//                        dungeons, the player, and the points required to win.
//      required_item   - the item the player needs in their inventory to attack
//                        the final boss
//
// Returns:
//      INVALID_ITEM when the item is not one of:
//              - PHYSICAL WEAPON
//              - MAGICAL TOME
//              - ARMOR
//              - HEALTH POTION
//              - TREASURE
//      VALID otherwise (no errors)
//
int final_boss(struct map *map, enum item_type required_item);

// Prints the player's statistics, that is, their name, health points, shield 
// power, damage, magic modifier, points collected, and all items in their
// inventory
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      nothing
//
void player_stats(struct map *map);

////////////////////////////////////////////////////////////////////////////////
//                             Stage 2 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Inserts a new dungeon into a specified position in the dungeon map
//
// Parameters:
//      map             - pointer to the dungeon map, containing list of  
//                        dungeons, the player, and the points required to win.
//      name            - name of the dungeon being added
//      monster         - type of monster the new dungeon should hold
//      num_monsters    - amount of monsters the dungeon should hold
//      position        - the position of the new dungeon, indexed from 1
//
// Returns:
//      INVALID_POSITION when the position is less than 1
//      INVALID_NAME when the name is already being used by a dungeon in the map
//      INVALID_MONSTER when the monster type is not one of:
//              - SLIME
//              - GOBLIN
//              - SKELETON
//              - WOLF
//      INVALID_AMOUNT when the amount of monsters is too small or too large
//      VALID otherwise (no errors found)
//
int insert_dungeon(struct map *map, char *name, enum monster_type monster,
                   int num_monsters, int position);

// Prints the specific details of the dungeon the player is currently in
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      nothing
//
void print_dungeon(struct map *map);

// Moves the player forward or backward in the dungeon map
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//      command     - char indicating whether the player moved forward 
//                    or backward
//                    NEXT_DUNGEON or PREVIOUS_DUNGEON
//
// Returns:
//      INVALID when there is no dungeon to move in to
//      VALID otherwise (no errors)
//
int move_player(struct map *map, char command);
        
// Simulates a fight between the player and the monsters in the current dungeon
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//      command     - char indicating if the player is using a physical or 
//                    magical attack
//                    PHYSICAL_ATTACK or MAGICAL_ATTACK
//
// Returns:
//      INVALID when there are no monsters in the current dungeon
//      VALID otherwise (no errors)
//
int fight(struct map *map, char command);

// Handles any actions that need to occur at the end of a turn;
//      - monster attacks
//      - removing any empty dungeons from the map
//      - boss monster movement and attacks
//      - check if the game is over
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      PLAYER_DEFEATED when the player has run out of health points
//      WON_MONSTERS when the player has won by collecting the win requirement
//          and defeating all monsters
//      WON_BOSS when the player has won by collecting the win requirement
//          and defeating the boss monster
//      CONTINUE_GAME otherwise
//
int end_turn(struct map *map);

// Activates the player's class power
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      INVALID when the player has already used their class power
//      VALID otherwise (no errors)
//
int class_power(struct map *map);

////////////////////////////////////////////////////////////////////////////////
//                             Stage 3 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Creates a new struct item
//
// Parameters:
//      type        - type of item
//      points      - how many points the item is worth when collected and used
//
// Returns:
//      a pointer to the newly created struct item
//
struct item *create_item(enum item_type type, int points);

// Creates and adds an item to the specified dungeon in enum order
//
// Parameters:
//      map             - pointer to the dungeon map, containing list of 
//                        dungeons, the player, and the points required to win.
//      dungeon_number  - dungeon to add the item to (indexed from 1)
//      type            - type of item to add
//      points          - how many points the item is worth
//
// Returns:
//      INVALID_DUNGEON when the dungeon number does not correspond to a dungeon
//          in the map
//      INVALID_ITEM when the item is not a valid type
//      INVALID_POINTS when the item is worth too little or too many points.
//          The #defines MIN_ITEM_POINT_VALUE and MAX_ITEM_POINT_VALUE have
//          been provided for you at the top of cs_dungeon.h.
//      VALID otherwise (no errors)
//
int add_item(struct map *map, int dungeon_number, enum item_type type,
             int points);

// Moves a specified item from the current dungeon to the player's inventory
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//      item_number - index of item in current dungeon to collect (indexed
//                    from 1)
//
// Returns:
//      INVALID when the item number does not correspond to an item in the
//          dungeon
//      VALID otherwise (no errors)
//
int collect_item(struct map *map, int item_number);              

// Uses a specified item in the player's inventory. Once used, the item should
// be freed
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//      item_number - index of item in current dungeon to use (indexed from 1)
//
// Returns:
//      INVALID when the item number does not correspond to an item in the
//          player's inventory
//      VALID otherwise (no errors)
//
int use_item(struct map *map, int item_number);

// Frees all malloc'd memory in the map, and then the map itself
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      nothing
//
void free_map(struct map *map);

////////////////////////////////////////////////////////////////////////////////
//                             Stage 4 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Teleports the player from the current dungeon to the furthest dungeon away
// that has not been visited yet via teleportation. Details outlined in the
// specification.
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      INVALID when there is no dungeon to teleport to
//      VALID otherwise (no errors)
//
int teleport(struct map *map);

// Attempts to have the player fight the boss monster. Details outlined in the
// specification.
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      NO_BOSS when there is no boss in the current dungeon
//      NO_ITEM when the player does not have the required item to fight the
//          boss
//      VALID otherwise (no errors)
//
int boss_fight(struct map *map);

////////////////////////////////////////////////////////////////////////////////
//                              Helper Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Finds the player name so it can be used in main.c
char *get_player_name(struct player *player);

// prints the name of the map
void print_map_name(char *name);

// prints the basic details of a given dungeon in the correct format
void print_basic_dungeon(struct dungeon *dungeon, char *player_name, 
                         int position);

// prints the connecting tunnel between dungeons
void print_connection(void);

// prints the details about the player
// if there are no dungeons yet, NULL should be provided as the dungeon name
void print_player(struct player *player, char *dungeon_name);

// prints the details about a given item
void print_item(struct item *item, int position);

// prints a message saying the player's inventory is empty
void print_no_items(void);

// prints the information of a given dungeon in more detail
void print_detail_dungeon(char *player_name, struct dungeon *dungeon);

// returns the string format of a class_type
char *class_string(struct player *player);

// returns the string format of an item_type
char *item_string(enum item_type item);

// returns the string format of a monster_type
char *monster_string(enum monster_type monster);

// prints a message saying the boss has been defeated
void print_boss_defeat(void);

// prints a message saying there are no dungeons in the map
void print_empty_map(void);

=======
#ifndef DUNGEON_H
#define DUNGEON_H

//
// DO NOT CHANGE THIS FILE
//
// You do not submit this file. This file is not marked.
// If you think you need to change this file you have
// misunderstood the assignment - ask in the course forum.
//
// Assignment 2 25T1 DPST1091: CS Dungeon
// cs_dungeon.h
//
// You must not change this file.
//
// Version 1.0.0: Release

////////////////////////////////////////////////////////////////////////////////
//                                 Constants                                  //
////////////////////////////////////////////////////////////////////////////////

#define DEFAULT -1
#define MAX_STR_LEN 32

#define MIN_MONSTERS 1
#define MAX_MONSTERS 10

#define MIN_ITEM_POINT_VALUE 1
#define MAX_ITEM_POINT_VALUE 10

#define MAX_HEALTH 50

// User commands
#define NEXT_DUNGEON '>'
#define PREVIOUS_DUNGEON '<'
#define PHYSICAL_ATTACK '!'
#define MAGICAL_ATTACK '#'

// Return values

// Standard return values
#define VALID 0
#define INVALID 1

// Creating and adding dungeons and items
#define INVALID_NAME 1
#define INVALID_MONSTER 2
#define INVALID_AMOUNT 3
#define INVALID_POSITION 4
#define INVALID_ITEM 1
#define INVALID_DUNGEON 2
#define INVALID_POINTS 3

// Ending the game
#define CONTINUE_GAME 0
#define PLAYER_DEFEATED 1
#define WON_MONSTERS 3
#define WON_BOSS 4

// Fighting final boss
#define NO_BOSS 1
#define NO_ITEM 2

// Provided enums:

// Represents the different types of monsters that can be encountered in the 
// dungeons. 
// The enum value represents both the monster's damage and health points.
enum monster_type {
    SLIME = 1,
    GOBLIN,
    SKELETON,
    WOLF,
};

// Represents the different types of items that can be found in the dungeons.
enum item_type {
    PHYSICAL_WEAPON,
    MAGICAL_TOME,
    ARMOR,
    HEALTH_POTION,
    TREASURE,
};

////////////////////////////////////////////////////////////////////////////////
//                            Struct Definitions                              //
////////////////////////////////////////////////////////////////////////////////

// Stores information about the dungeon map the game is played in.
struct map {
    // the name of the map
    char name[MAX_STR_LEN];

    // the list of dungeons within the map
    struct dungeon *entrance;

    // a pointer to the player who is exploring the map
    struct player *player;
    
    // the number of points required to win the game
    int win_requirement;
};

////////////////////////////////////////////////////////////////////////////////
//                             Stage 1 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Creates a new struct map
//
// Parameters:
//      name            - name of the dungeon map being created
//      win_requirement - amount of points required to win this game
//
// Returns:
//      a pointer to the newly created struct map
//
struct map *create_map(char *name, int win_requirement);

// Creates a new struct player
//
// Parameters:
//      name            - name of the player being created
//      class_type      - class that the player will play as, "Fighter"
//                        or "Wizard"
//
// Returns:
//      a pointer to the newly created struct player
//
struct player *create_player(char *name, char *class_type);

// Adds a new dungeon to the end of the list of dungeons contained within the 
// map
//
// Parameters:
//      map             - pointer to the dungeon map, containing list of  
//                        dungeons, the player, and the points required to win.
//      name            - name of the dungeon being added
//      monster         - type of monster the new dungeon should hold
//      num_monsters    - amount of monsters the dungeon should hold
//
// Returns:
//      INVALID_NAME when the name is already being used by a dungeon in the map
//      INVALID_MONSTER when the monster type is not one of:
//              - SLIME
//              - GOBLIN
//              - SKELETON
//              - WOLF
//      INVALID_AMOUNT when the amount of monsters is too small or too large
//      VALID otherwise (no errors found)
//
int append_dungeon(struct map *map, char *name, enum monster_type monster,
                   int num_monsters);

// Prints the list of dungeons contained within the map
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      nothing
//
void print_map(struct map *map);

// Adds the final boss to the last dungeon in the map
//
// Parameters:
//      map             - pointer to the dungeon map, containing list of  
//                        dungeons, the player, and the points required to win.
//      required_item   - the item the player needs in their inventory to attack
//                        the final boss
//
// Returns:
//      INVALID_ITEM when the item is not one of:
//              - PHYSICAL WEAPON
//              - MAGICAL TOME
//              - ARMOR
//              - HEALTH POTION
//              - TREASURE
//      VALID otherwise (no errors)
//
int final_boss(struct map *map, enum item_type required_item);

// Prints the player's statistics, that is, their name, health points, shield 
// power, damage, magic modifier, points collected, and all items in their
// inventory
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      nothing
//
void player_stats(struct map *map);

////////////////////////////////////////////////////////////////////////////////
//                             Stage 2 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Inserts a new dungeon into a specified position in the dungeon map
//
// Parameters:
//      map             - pointer to the dungeon map, containing list of  
//                        dungeons, the player, and the points required to win.
//      name            - name of the dungeon being added
//      monster         - type of monster the new dungeon should hold
//      num_monsters    - amount of monsters the dungeon should hold
//      position        - the position of the new dungeon, indexed from 1
//
// Returns:
//      INVALID_POSITION when the position is less than 1
//      INVALID_NAME when the name is already being used by a dungeon in the map
//      INVALID_MONSTER when the monster type is not one of:
//              - SLIME
//              - GOBLIN
//              - SKELETON
//              - WOLF
//      INVALID_AMOUNT when the amount of monsters is too small or too large
//      VALID otherwise (no errors found)
//
int insert_dungeon(struct map *map, char *name, enum monster_type monster,
                   int num_monsters, int position);

// Prints the specific details of the dungeon the player is currently in
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      nothing
//
void print_dungeon(struct map *map);

// Moves the player forward or backward in the dungeon map
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//      command     - char indicating whether the player moved forward 
//                    or backward
//                    NEXT_DUNGEON or PREVIOUS_DUNGEON
//
// Returns:
//      INVALID when there is no dungeon to move in to
//      VALID otherwise (no errors)
//
int move_player(struct map *map, char command);
        
// Simulates a fight between the player and the monsters in the current dungeon
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//      command     - char indicating if the player is using a physical or 
//                    magical attack
//                    PHYSICAL_ATTACK or MAGICAL_ATTACK
//
// Returns:
//      INVALID when there are no monsters in the current dungeon
//      VALID otherwise (no errors)
//
int fight(struct map *map, char command);

// Handles any actions that need to occur at the end of a turn;
//      - monster attacks
//      - removing any empty dungeons from the map
//      - boss monster movement and attacks
//      - check if the game is over
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      PLAYER_DEFEATED when the player has run out of health points
//      WON_MONSTERS when the player has won by collecting the win requirement
//          and defeating all monsters
//      WON_BOSS when the player has won by collecting the win requirement
//          and defeating the boss monster
//      CONTINUE_GAME otherwise
//
int end_turn(struct map *map);

// Activates the player's class power
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      INVALID when the player has already used their class power
//      VALID otherwise (no errors)
//
int class_power(struct map *map);

////////////////////////////////////////////////////////////////////////////////
//                             Stage 3 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Creates a new struct item
//
// Parameters:
//      type        - type of item
//      points      - how many points the item is worth when collected and used
//
// Returns:
//      a pointer to the newly created struct item
//
struct item *create_item(enum item_type type, int points);

// Creates and adds an item to the specified dungeon in enum order
//
// Parameters:
//      map             - pointer to the dungeon map, containing list of 
//                        dungeons, the player, and the points required to win.
//      dungeon_number  - dungeon to add the item to (indexed from 1)
//      type            - type of item to add
//      points          - how many points the item is worth
//
// Returns:
//      INVALID_DUNGEON when the dungeon number does not correspond to a dungeon
//          in the map
//      INVALID_ITEM when the item is not a valid type
//      INVALID_POINTS when the item is worth too little or too many points.
//          The #defines MIN_ITEM_POINT_VALUE and MAX_ITEM_POINT_VALUE have
//          been provided for you at the top of cs_dungeon.h.
//      VALID otherwise (no errors)
//
int add_item(struct map *map, int dungeon_number, enum item_type type,
             int points);

// Moves a specified item from the current dungeon to the player's inventory
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//      item_number - index of item in current dungeon to collect (indexed
//                    from 1)
//
// Returns:
//      INVALID when the item number does not correspond to an item in the
//          dungeon
//      VALID otherwise (no errors)
//
int collect_item(struct map *map, int item_number);              

// Uses a specified item in the player's inventory. Once used, the item should
// be freed
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//      item_number - index of item in current dungeon to use (indexed from 1)
//
// Returns:
//      INVALID when the item number does not correspond to an item in the
//          player's inventory
//      VALID otherwise (no errors)
//
int use_item(struct map *map, int item_number);

// Frees all malloc'd memory in the map, and then the map itself
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      nothing
//
void free_map(struct map *map);

////////////////////////////////////////////////////////////////////////////////
//                             Stage 4 Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Teleports the player from the current dungeon to the furthest dungeon away
// that has not been visited yet via teleportation. Details outlined in the
// specification.
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      INVALID when there is no dungeon to teleport to
//      VALID otherwise (no errors)
//
int teleport(struct map *map);

// Attempts to have the player fight the boss monster. Details outlined in the
// specification.
//
// Parameters:
//      map         - pointer to the dungeon map, containing list of dungeons, 
//                    the player, and the points required to win.
//
// Returns:
//      NO_BOSS when there is no boss in the current dungeon
//      NO_ITEM when the player does not have the required item to fight the
//          boss
//      VALID otherwise (no errors)
//
int boss_fight(struct map *map);

////////////////////////////////////////////////////////////////////////////////
//                              Helper Functions                              //
////////////////////////////////////////////////////////////////////////////////

// Finds the player name so it can be used in main.c
char *get_player_name(struct player *player);

// prints the name of the map
void print_map_name(char *name);

// prints the basic details of a given dungeon in the correct format
void print_basic_dungeon(struct dungeon *dungeon, char *player_name, 
                         int position);

// prints the connecting tunnel between dungeons
void print_connection(void);

// prints the details about the player
// if there are no dungeons yet, NULL should be provided as the dungeon name
void print_player(struct player *player, char *dungeon_name);

// prints the details about a given item
void print_item(struct item *item, int position);

// prints a message saying the player's inventory is empty
void print_no_items(void);

// prints the information of a given dungeon in more detail
void print_detail_dungeon(char *player_name, struct dungeon *dungeon);

// returns the string format of a class_type
char *class_string(struct player *player);

// returns the string format of an item_type
char *item_string(enum item_type item);

// returns the string format of a monster_type
char *monster_string(enum monster_type monster);

// prints a message saying the boss has been defeated
void print_boss_defeat(void);

// prints a message saying there are no dungeons in the map
void print_empty_map(void);

>>>>>>> cs_project/main
#endif