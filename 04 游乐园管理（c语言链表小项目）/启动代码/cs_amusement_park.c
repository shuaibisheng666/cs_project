// CS Amusement Park
// cs_amusement_park.c
// Written by <YOUR-NAME>, <YOUR-ZID>
// on <TODAYS-DATE>

////////////////////////////////////////////////////////////////////////////////
// Provided Libraries
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "cs_amusement_park.h"

////////////////////////////////////////////////////////////////////////////////
// Your libraries
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Function Definitions
////////////////////////////////////////////////////////////////////////////////

// Stage 1.1
// Function to initialise the park
// Params:
//      name - the name of the park
// Returns: a pointer to the park
struct park *initialise_park(char name[MAX_SIZE]) {
    // TODO: Replace this with your code
    printf("Initialise park not yet implemented\n");
    return NULL;
}

// Stage 1.1
// Function to create a visitor
// Params:
//      name - the name of the visitor
//      height - the height of the visitor
// Returns: a pointer to the visitor
struct visitor *create_visitor(char name[MAX_SIZE], double height) {
    // TODO: Replace this with your code
    printf("Create visitor not yet implemented\n");
    return NULL;
}

// Stage 1.1
// Function to create a ride
// Params:
//      name - the name of the ride
//      type - the type of the ride
// Returns: a pointer to the ride
struct ride *create_ride(char name[MAX_SIZE], enum ride_type type) {
    // TODO: Replace this with your code
    printf("Create ride not yet implemented\n");
    return NULL;
}

// Stage 1.2
// Function to run the command loop
//
// Params:
//     park - a pointer to the park
// Returns: None
void command_loop(struct park *park) {
    // TODO: Replace this with your code
    printf("Command loop not yet implemented\n");
    return;
}

// Stage 1.3
// Function to add a ride to the park
// Params:
//      park - a pointer to the park
// Returns: None
void add_ride(struct park *park) {
    // TODO: Replace this with your code
    printf("Add ride not yet implemented\n");
    return;
}

// Stage 1.3
// Function to add a visitor to the park
// Params:
//      park - a pointer to the park
// Returns: None
void add_visitor(struct park *park) {
    // TODO: Replace this with your code
    printf("Add visitor not yet implemented\n");
    return;
}

// Stage 1.4
// Function to print the park
// Params:
//      park - a pointer to the park
// Returns: None
void print_park(struct park *park) {
    // TODO: Replace this with your code
    printf("Print park not yet implemented\n");
    return;
}

////////////////////////////////////////////////////////////////////////////////
// Providing function definitions
////////////////////////////////////////////////////////////////////////////////

// Function to print the usage of the program
// '?' command
// Params: None
// Returns: None
// Usage:
// ```
//      print_usage();
// ```
void print_usage(void) {
    printf(
        "======================[ CS Amusement Park ]======================\n"
        "      ===============[     Usage Info     ]===============       \n"
        "  a r [ride_name] [ride_type]                                    \n"
        "    Add a ride to the park.                                      \n"
        "  a v [visitor_name] [visitor_height]                            \n"
        "    Add a visitor to the park.                                   \n"
        "  i [index] [ride_name] [ride_type]                              \n"
        "    Insert a ride at a specific position in the park's ride list.\n"
        "  j [ride_name] [visitor_name]                                   \n"
        "    Add a visitor to the queue of a specific ride.               \n"
        "  m [visitor_name] [ride_name]                                   \n"
        "    Move a visitor from roaming to a ride's queue.               \n"
        "  d [visitor_name]                                               \n"
        "    Remove a visitor from any ride queue and return to roaming.  \n"
        "  p                                                              \n"
        "    Print the current state of the park, including rides and     \n"
        "    visitors.                                                    \n"
        "  t                                                              \n"
        "    Display the total number of visitors in the park, including  \n"
        "    those roaming and in ride queues.                            \n"
        "  c [start_ride] [end_ride]                                      \n"
        "    Count and display the number of visitors in queues between   \n"
        "    the specified start and end rides, inclusive.                \n"
        "  l [visitor_name]                                               \n"
        "    Remove a visitor entirely from the park.                     \n"
        "  r                                                              \n"
        "    Operate all rides, allowing visitors to enjoy the rides      \n"
        "    and moving them to roaming after their ride.                 \n"
        "  M [ride_type]                                                  \n"
        "    Merge the two smallest rides of the specified type.          \n"
        "  s [n] [ride_name]                                              \n"
        "    Split an existing ride into `n` smaller rides.               \n"
        "  q                                                              \n"
        "    Quit the program and free all allocated resources.           \n"
        "  T [n] [command]                                                \n"
        "    Scheduled the [command] to take place `n` ticks              \n"
        "    in the future.                                               \n"
        "  ~ [n]                                                          \n"
        "    Progress the schedule for `n` ticks.                         \n"
        "  ?                                                              \n"
        "    Show this help information.                                  \n"
        "=================================================================\n");
}

// Function to print a welcome message
// Params:
//      name - the name of the park
// Returns: None
// Usage:
// ```
//      print_welcome_message(name);
// ```
void print_welcome_message(char name[MAX_SIZE]) {
    printf("===================[ %s ]===================\n", name);
}

// Function to print a ride
// Params:
//      ride - the ride to print
// Returns: None
// Usage:
// ```
//      print_ride(ride);
// ```
void print_ride(struct ride *ride) {
    printf("  %s (%s)\n", ride->name, type_to_string(ride->type));
    printf("    Rider Capacity: %d\n", ride->rider_capacity);
    printf("    Queue Capacity: %d\n", ride->queue_capacity);
    printf("    Minimum Height: %.2lfcm\n", ride->min_height);
    printf("    Queue:\n");
    struct visitor *curr_visitor = ride->queue;
    if (curr_visitor == NULL) {
        printf("      No visitors\n");
    } else {
        while (curr_visitor != NULL) {
            printf(
                "      %s (%.2lfcm)\n", curr_visitor->name,
                curr_visitor->height);
            curr_visitor = curr_visitor->next;
        }
    }
}

// Scan in the a name string into the provided buffer, placing
// '\0' at the end.
//
// Params:
//      name - a char array of length MAX_SIZE, which will be used
//                  to store the name.
// Returns: None
// Usage:
// ```
//      char name[MAX_SIZE];
//      scan_name(name);
// ```
void scan_name(char name[MAX_SIZE]) {
    scan_token(name, MAX_SIZE);
}

// Scans a string and converts it to a ride_type.
//
// Params: None
// Returns:
//      The corresponding ride_type, if the string was valid,
//      Otherwise, returns INVALID.
//
// Usage:
// ```
//      enum ride_type type = scan_type();
// ```
//
enum ride_type scan_type(void) {
    char type[MAX_SIZE];
    scan_token(type, MAX_SIZE);
    return string_to_type(type);
}

////////////////////////////////////////////////////////////////////////////////
// Additional provided functions
////////////////////////////////////////////////////////////////////////////////

// You don't need to use any of these, or understand how they work!
// We use them to implement some of the provided helper functions.

enum ride_type string_to_type(char *type_str) {
    int len = strlen(type_str);

    if (strncasecmp(type_str, "roller_coaster", len) == 0) {
        return ROLLER_COASTER;
    }
    if (strncasecmp(type_str, "CAROUSEL", len) == 0) {
        return CAROUSEL;
    }
    if (strncasecmp(type_str, "FERRIS_WHEEL", len) == 0) {
        return FERRIS_WHEEL;
    }
    if (strncasecmp(type_str, "BUMPER_CARS", len) == 0) {
        return BUMPER_CARS;
    }

    return INVALID;
}

char *type_to_string(enum ride_type type) {
    if (type == ROLLER_COASTER) {
        return "ROLLER_COASTER";
    }
    if (type == CAROUSEL) {
        return "CAROUSEL";
    }
    if (type == FERRIS_WHEEL) {
        return "FERRIS_WHEEL";
    }
    if (type == BUMPER_CARS) {
        return "BUMPER_CARS";
    }
    return "INVALID";
}

int scan_token(char *buffer, int buffer_size) {
    if (buffer_size == 0) {
        return 0;
    }

    char c;
    int i = 0;
    int num_scanned = 0;

    scanf(" ");

    while (i < buffer_size - 1 && (num_scanned = scanf("%c", &c)) == 1 &&
           !isspace(c)) {
        buffer[i++] = c;
    }

    if (i > 0) {
        buffer[i] = '\0';
    }

    return num_scanned;
}