// CS Amusement Park
// cs_amusement_park.h
// Written by <YOUR-NAME>, <YOUR-ZID>
// on <TODAYS-DATE>

////////////////////////////////////////////////////////////////////////////////
// Provided Constants
////////////////////////////////////////////////////////////////////////////////
#define MAX_SIZE 100

////////////////////////////////////////////////////////////////////////////////
// Your constants
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Provided Enums
////////////////////////////////////////////////////////////////////////////////

enum ride_type { ROLLER_COASTER, CAROUSEL, FERRIS_WHEEL, BUMPER_CARS, INVALID };

////////////////////////////////////////////////////////////////////////////////
// Provided Structs
////////////////////////////////////////////////////////////////////////////////

// Structure to hold scheduled commands
struct scheduled_command {
    int ticks_remaining;
    char command_string[1000]; // Store the full command string
    struct scheduled_command *next;
};

struct park {
    // The name of the park
    char name[MAX_SIZE];
    // The total number of visitors in the park
    int total_visitors;
    // The list of rides in the park
    struct ride *rides;
    // The list of visitors in the park
    struct visitor *visitors;
    // The list of scheduled commands
    struct scheduled_command *scheduled_commands;
};

struct ride {
    // The name of the ride
    char name[MAX_SIZE];
    // The type of the ride i.e. ROLLER_COASTER, CAROUSEL, FERRIS_WHEEL, BUMPER_CARS, INVALID
    enum ride_type type;
    // The number of riders the ride can hold
    int rider_capacity;
    // The number of visitors that can be in the queue
    int queue_capacity;
    // The minimum height required to ride
    double min_height;
    // The queue of visitors waiting to ride
    struct visitor *queue;
    // The next ride in the list
    struct ride *next;
};

struct visitor {
    // The name of the visitor
    char name[MAX_SIZE];
    // The height of the visitor
    double height;
    // The next visitor in the list
    struct visitor *next;
};

////////////////////////////////////////////////////////////////////////////////
// Provided function prototypes
////////////////////////////////////////////////////////////////////////////////
void print_usage(void);
void scan_name(char name[MAX_SIZE]);
void print_ride(struct ride *ride);
enum ride_type scan_type(void);
void print_welcome_message(char name[MAX_SIZE]);

// Additional provided function prototypes
// You won't need to use these functions!
// We use just them to implement some of the provided helper functions.
int scan_token(char *buffer, int buffer_size);
char *type_to_string(enum ride_type type);
enum ride_type string_to_type(char *type_str);

////////////////////////////////////////////////////////////////////////////////
// Your function prototypes
////////////////////////////////////////////////////////////////////////////////

// Stage 1
struct park *initialise_park(char name[MAX_SIZE]);
struct visitor *create_visitor(char name[MAX_SIZE], double height);
struct ride *create_ride(char name[MAX_SIZE], enum ride_type type);
void add_ride(struct park *park);
void add_visitor(struct park *park);
void print_park(struct park *park);
void insert_ride(struct park *park);
void join_ride_queue(struct park *park);
void remove_visitor_from_queue(struct park *park);
void move_visitor_to_ride(struct park *park);
void total_visitors(struct park *park);
void count_visitors_in_range(struct park *park);
void free_park(struct park *park);
void leave_park(struct park *park);
void operate_rides(struct park *park);
void shut_down_ride(struct park *park);
void merge_rides(struct park *park);
void split_ride(struct park *park);
void schedule_command(struct park *park);
void advance_ticks(struct park *park);
void execute_ready_commands(struct park *park);
void execute_scheduled_command_string(struct park *park, char *command_str);
void decrement_tick_counters(struct park *park);
void command_loop(struct park *park);

// Helper functions for error checking
int ride_name_exists(struct park *park, char name[MAX_SIZE]);
int visitor_name_exists(struct park *park, char name[MAX_SIZE]);
struct ride *find_ride(struct park *park, char name[MAX_SIZE]);
struct visitor *find_and_remove_visitor(struct park *park, char name[MAX_SIZE]);
int count_queue_length(struct visitor *queue);
struct visitor *find_and_remove_from_queues(struct park *park, char name[MAX_SIZE]);
int visitor_in_ride_queue(struct ride *ride, char name[MAX_SIZE]);
struct visitor *find_and_remove_visitor_anywhere(struct park *park, char name[MAX_SIZE]);