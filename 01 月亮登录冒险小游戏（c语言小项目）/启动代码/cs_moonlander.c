// cs_moonlander.c
// Written by YOUR-NAME (YOUR-ZID),
// on TODAYS-DATE
// TODO: Program Description

#include <stdio.h>

// Provided Constant Definitions
#define BOARD_LEN 10
#define BOARD_MAX_LEVELS 32
#define BASE_OXY_RATE 1.0
#define MAX_PORTALS 16
#define TITLE_STR_LEN 25
#define INVALID_INDEX -1
#define COMMAND_QUIT 'q'

// TODO: Your #defines go here

// Provided Enum Definitions
enum entity {
    EMPTY,
    CHEESE,
    ROCK,
    LANDER,
    HOLE_DOWN,
    HOLE_UP,
    PORTAL
};

// TODO: Your enums go here

// Provided Struct Definitions
struct tile {
    enum entity entity;
};

// TODO: Your structs go here

// Provided Function Prototypes
void init_board(
    struct tile board[BOARD_LEN][BOARD_LEN]
);
void print_board(
    struct tile board[BOARD_LEN][BOARD_LEN],
    int player_row,
    int player_col,
    int cheese_held,
    int cheese_lander,
    double oxy_capacity,
    double oxy_level,
    double oxy_rate
);
void print_board_header(void);
void print_player_stats(
    int cheese_held,
    int cheese_lander,
    double oxy_capacity,
    double oxy_level,
    double oxy_rate
);

// TODO: Your function prototypes go here
void input_lander(int *row, int *col);
int input_ches_rock(char *che_rock, int *row, int *col);
void insert_ches_rock(struct tile board[BOARD_LEN][BOARD_LEN], char che_rock, int row, int col);
int is_valid_position(int row, int col);
int is_tile_empty(struct tile board[BOARD_LEN][BOARD_LEN], int row, int col);
int add_large_rock(struct tile board[BOARD_LEN][BOARD_LEN], 
                  int start_row, int start_col, 
                  int end_row, int end_col);

int main(void) {
    // TODO: add your code (and remove this todo)
    int row, col;
    char ches_rock;
    // prints the board with no player
    // you may decide to delete or move this later...
    struct tile board[BOARD_LEN][BOARD_LEN];
    init_board(board);
    input_lander(&row, &col);
    board[row][col].entity = LANDER;
    print_board(board, INVALID_INDEX, INVALID_INDEX, 0.0, 0.0, 0.0, 0.0,
    BASE_OXY_RATE);

    printf("Please enter cheese and rock locations:\n");
    while(1){
        if(input_ches_rock(&ches_rock, &row, &col) == EOF){
            break;
        }
        else{
            insert_ches_rock(board, ches_rock, row, col);
        }
    }
    print_board(board, INVALID_INDEX, INVALID_INDEX, 0.0, 0.0, 0.0, 0.0,
    BASE_OXY_RATE);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Your function implementations go here
void input_lander(int *row, int *col){
    printf("Please enter the [row] [col] of the lander: ");
    scanf("%d %d", row, col);
    if(*row < 0 || *row >= BOARD_LEN || *col < 0 || *col >= BOARD_LEN){
        *row = 4;
        *col = 4;  
    }

}

int input_ches_rock(char *che_rock, int *row, int *col){
    return scanf("%c %d %d", che_rock, row, col);
}

void insert_ches_rock(struct tile board[BOARD_LEN][BOARD_LEN], char che_rock, int row, int col) {
    if (che_rock == 'R') {
        // read the end position
        int end_row, end_col;
        scanf("%d %d", &end_row, &end_col);
        add_large_rock(board, row, col, end_row, end_col);
        return;
    }

    // check if the position is valid and empty
    if (!is_valid_position(row, col) || 
        !is_tile_empty(board, row, col)) {
        if (che_rock == 'c') {
            printf("That is not a valid cheese placement!\n");
        } else if (che_rock == 'r') {
            printf("That is not a valid rock placement!\n");
        }
        return;
    }

    if (che_rock == 'r') {
        board[row][col].entity = ROCK;
    } else if (che_rock == 'c') {
        board[row][col].entity = CHEESE;
    }
}
// check if the position is in the board
int is_valid_position(int row, int col) {
    return row >= 0 && row < BOARD_LEN && 
           col >= 0 && col < BOARD_LEN;
}

// check if the tile is empty
int is_tile_empty(struct tile board[BOARD_LEN][BOARD_LEN], 
                 int row, int col) {
    return board[row][col].entity == EMPTY;
}

// add large rock
int add_large_rock(struct tile board[BOARD_LEN][BOARD_LEN], 
                  int start_row, int start_col, 
                  int end_row, int end_col) {
    // check if the start and end position is in the board
    if (!is_valid_position(start_row, start_col) || 
        !is_valid_position(end_row, end_col)) {
        printf("That is not a valid rock placement!\n");
        return 0;
    }
    
    // check if the start position is greater than the end position
    if (start_row > end_row || start_col > end_col) {
        printf("That is not a valid rock placement!\n");
        return 0;
    }

    // check if all positions are valid and empty
    for (int i = start_row; i <= end_row; i++) {
        for (int j = start_col; j <= end_col; j++) {
            if (!is_valid_position(i, j) || 
                !is_tile_empty(board, i, j)) {
                printf("That is not a valid rock placement!\n");
                return 0;
            }
        }
    }

    // place the large rock
    for (int i = start_row; i <= end_row; i++) {
        for (int j = start_col; j <= end_col; j++) {
            board[i][j].entity = ROCK;
        }
    }
    return 1;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROVIDED FUNCTIONS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Initialises the board to EMPTY for each tile
void init_board(struct tile board[BOARD_LEN][BOARD_LEN]) {
    for (int row = 0; row < BOARD_LEN; row++) {
        for (int col = 0; col < BOARD_LEN; col++) {
            board[row][col].entity = EMPTY;
        }
    }
    return;
}

// Prints a line commonly used when printing the board, line length scales with
// the BOARD_LEN constant
void print_board_line(void) {
    printf("+");
    for (int col = 0; col < BOARD_LEN; col++) {
        printf("---+");
    }
    printf("\n");
    return;
}

// Prints the header of the cs_moonlander board
void print_board_header(void) {
    char title_str[TITLE_STR_LEN + 1] = "C S   M O O N L A N D E R";

    printf("|");
    for (int i = (4 * BOARD_LEN - TITLE_STR_LEN) / 2; i > 0; i--) {
        printf(" ");
    }

    printf("%s", title_str);

    for (int i = (4 * BOARD_LEN - TITLE_STR_LEN) / 2; i > 0; i--) {
        printf(" ");
    }
    printf("|\n");

    return;
}

// Prints the player stats when requested by the user
void print_player_stats(
    int cheese_held,
    int cheese_lander,
    double oxy_capacity,
    double oxy_level,
    double oxy_rate
) {
    printf("Player Cheese: %d     Lander Cheese: %d\n",
            cheese_held, cheese_lander);
    printf("Oxy: %.2lf / %.2lf  @  %.6lf / move\n", oxy_level,
            oxy_capacity, oxy_rate);
    return;
}

// Prints the cs_moonlander board
void print_board(
    struct tile board[BOARD_LEN][BOARD_LEN],
    int player_row,
    int player_col,
    int cheese_held,
    int cheese_lander,
    double oxy_capacity,
    double oxy_level,
    double oxy_rate) {

    print_board_line();
    print_board_header();
    print_board_line();
    for (int row = 0; row < BOARD_LEN; row++) {
        for (int col = 0; col < BOARD_LEN; col++) {
            printf("|");
            if (row == player_row && col == player_col) {
                printf("0.0");
            } else if (board[row][col].entity == ROCK) {
                printf("^^^");
            } else if (board[row][col].entity == LANDER) {
                printf("/|\\");
            } else if (board[row][col].entity == CHEESE) {
                printf("<(]");
            } else if (board[row][col].entity == HOLE_UP) {
                printf("/O\\");
            } else if (board[row][col].entity == HOLE_DOWN) {
                printf("\\O/");
            } else if (board[row][col].entity == PORTAL) {
                printf("~~~");
            } else {
                printf("   ");
            }
        }
        printf("|\n");
        print_board_line();
    }
    print_player_stats(cheese_held, cheese_lander, oxy_capacity, oxy_level,
            oxy_rate);
    print_board_line();
    return;
}
