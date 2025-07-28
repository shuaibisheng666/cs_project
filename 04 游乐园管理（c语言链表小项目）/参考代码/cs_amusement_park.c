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
#include <stdlib.h>

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
    // Allocate memory
    struct park *new_park = malloc(sizeof(struct park));
    
    // Copy park name
    strcpy(new_park->name, name);
    
    // Initialize other fields
    new_park->total_visitors = 0;
    new_park->rides = NULL;
    new_park->visitors = NULL;
    new_park->scheduled_commands = NULL;
    
    return new_park;
}

// Stage 1.1
// Function to create a visitor
// Params:
//      name - the name of the visitor
//      height - the height of the visitor
// Returns: a pointer to the visitor
struct visitor *create_visitor(char name[MAX_SIZE], double height) {
    // Allocate memory
    struct visitor *new_visitor = malloc(sizeof(struct visitor));
    
    // Copy visitor name
    strcpy(new_visitor->name, name);
    
    // Set height
    new_visitor->height = height;
    
    // Initialize linked list pointer
    new_visitor->next = NULL;
    
    return new_visitor;
}

// Stage 1.1
// Function to create a ride
// Params:
//      name - the name of the ride
//      type - the type of the ride
// Returns: a pointer to the ride
struct ride *create_ride(char name[MAX_SIZE], enum ride_type type) {
    // Allocate memory
    struct ride *new_ride = malloc(sizeof(struct ride));
    
    // Copy ride name
    strcpy(new_ride->name, name);
    
    // Set type
    new_ride->type = type;
    
    // Set capacity and minimum height based on type
    switch (type) {
        case ROLLER_COASTER:
            new_ride->rider_capacity = 4;
            new_ride->queue_capacity = 7;
            new_ride->min_height = 120.0;
            break;
        case CAROUSEL:
            new_ride->rider_capacity = 6;
            new_ride->queue_capacity = 9;
            new_ride->min_height = 60.0;
            break;
        case FERRIS_WHEEL:
            new_ride->rider_capacity = 8;
            new_ride->queue_capacity = 11;
            new_ride->min_height = 75.0;
            break;
        case BUMPER_CARS:
            new_ride->rider_capacity = 10;
            new_ride->queue_capacity = 13;
            new_ride->min_height = 100.0;
            break;
        default:
            // For INVALID type, set default values
            new_ride->rider_capacity = 0;
            new_ride->queue_capacity = 0;
            new_ride->min_height = 0.0;
            break;
    }
    
    // Initialize linked list pointers
    new_ride->queue = NULL;
    new_ride->next = NULL;
    
    return new_ride;
}

// Stage 1.2
// Function to run the command loop
//
// Params:
//     park - a pointer to the park
// Returns: None
void command_loop(struct park *park) {
    char command;
    
    // Command loop - continue until CTRL+D (EOF)
    while (1) {
        printf("Enter command: ");
        
        // Scan for command character with space before %c to ignore whitespace
        if (scanf(" %c", &command) != 1) {
            // CTRL+D pressed (EOF), break out of loop
            break;
        }
        
        // Execute any ready scheduled commands before processing manual command
        // (except for T and ~ commands which don't advance time)
        if (command != 'T' && command != '~') {
            // Decrement tick counters for all scheduled commands
            decrement_tick_counters(park);
            
            // Execute any commands that are now ready
            execute_ready_commands(park);
        }
        
        // Process the command
        switch (command) {
            case 'a':
                // Add command - need to scan next character
                {
                    char add_type;
                    scanf(" %c", &add_type);
                    if (add_type == 'r') {
                        add_ride(park);
                    } else if (add_type == 'v') {
                        add_visitor(park);
                    } else {
                        printf("ERROR: Invalid command.\n");
                    }
                }
                break;
            case 'i':
                // Insert ride command
                insert_ride(park);
                break;
            case 'j':
                // Join ride queue command
                join_ride_queue(park);
                break;
            case 'd':
                // Remove visitor from queue command
                remove_visitor_from_queue(park);
                break;
            case 'm':
                // Move visitor to ride command
                move_visitor_to_ride(park);
                break;
            case 't':
                // Total visitors command
                total_visitors(park);
                break;
            case 'c':
                // Count visitors in range command
                count_visitors_in_range(park);
                break;
            case 'l':
                // Leave park command
                leave_park(park);
                break;
            case 'r':
                // Operate rides command
                operate_rides(park);
                break;
            case 'S':
                // Shut down ride command
                shut_down_ride(park);
                break;
            case 'M':
                // Merge rides command
                merge_rides(park);
                break;
            case 's':
                // Split ride command
                split_ride(park);
                break;
            case 'T':
                // Schedule command
                schedule_command(park);
                break;
            case '~':
                // Advance ticks command
                advance_ticks(park);
                break;
            case 'p':
                // Print park command
                print_park(park);
                break;
            case 'q':
                // Quit command - exit the program
                return;
            case '?':
                // Help command - print usage information
                print_usage();
                break;
            default:
                // Invalid command
                printf("ERROR: Invalid command.\n");
                break;
        }
    }
}

// Stage 1.3
// Function to add a ride to the park
// Params:
//      park - a pointer to the park
// Returns: None
void add_ride(struct park *park) {
    char name[MAX_SIZE];
    enum ride_type type;
    
    // Scan ride name and type
    scan_name(name);
    type = scan_type();
    
    // Error check: first check if type is INVALID
    if (type == INVALID) {
        printf("ERROR: Invalid ride type.\n");
        return;
    }
    
    // Error check: check if name already exists
    if (ride_name_exists(park, name)) {
        printf("ERROR: '%s' already exists.\n", name);
    return;
    }
    
    // Create new ride
    struct ride *new_ride = create_ride(name, type);
    
    // Add new ride to the tail of rides linked list
    if (park->rides == NULL) {
        // If list is empty, directly set head pointer
        park->rides = new_ride;
    } else {
        // Traverse list to find the last node
        struct ride *current = park->rides;
        while (current->next != NULL) {
            current = current->next;
        }
        // Connect new node to the end
        current->next = new_ride;
    }
    
    // Print confirmation message
    printf("Ride: '%s' added!\n", name);
}

// Stage 1.3
// Function to add a visitor to the park
// Params:
//      park - a pointer to the park
// Returns: None
void add_visitor(struct park *park) {
    char name[MAX_SIZE];
    double height;
    
    // Scan visitor name and height
    scan_name(name);
    scanf("%lf", &height);
    
    // Error check: first check if height is within 50-250 range
    if (height < 50 || height > 250) {
        printf("ERROR: Height must be between 50 and 250.\n");
        return;
    }
    
    // Error check: check if visitor count would exceed limit of 40
    if (park->total_visitors >= 40) {
        printf("ERROR: Cannot add another visitor to the park. The park is at capacity.\n");
        return;
    }
    
    // Error check: check if name already exists
    if (visitor_name_exists(park, name)) {
        printf("ERROR: '%s' already exists.\n", name);
        return;
    }
    
    // Create new visitor
    struct visitor *new_visitor = create_visitor(name, height);
    
    // Add new visitor to the tail of visitors linked list
    if (park->visitors == NULL) {
        // If list is empty, directly set head pointer
        park->visitors = new_visitor;
    } else {
        // Traverse list to find the last node
        struct visitor *current = park->visitors;
        while (current->next != NULL) {
            current = current->next;
        }
        // Connect new node to the end
        current->next = new_visitor;
    }
    
    // Increment total visitor count
    park->total_visitors++;
    
    // Print confirmation message
    printf("Visitor: '%s' has entered the amusement park!\n", name);
}

// Stage 2.1
// Function to insert a ride at a specific position
// Params:
//      park - a pointer to the park
// Returns: None
void insert_ride(struct park *park) {
    int n;
    char name[MAX_SIZE];
    enum ride_type type;
    
    // Scan position, ride name and type
    scanf("%d", &n);
    scan_name(name);
    type = scan_type();
    
    // Error check: check if position is at least 1
    if (n < 1) {
        printf("ERROR: n must be at least 1.\n");
        return;
    }
    
    // Error check: check if type is INVALID
    if (type == INVALID) {
        printf("ERROR: Invalid ride type.\n");
        return;
    }
    
    // Error check: check if name already exists
    if (ride_name_exists(park, name)) {
        printf("ERROR: '%s' already exists.\n", name);
        return;
    }
    
    // Create new ride
    struct ride *new_ride = create_ride(name, type);
    
    // Handle insertion at head (n == 1)
    if (n == 1) {
        new_ride->next = park->rides;
        park->rides = new_ride;
        printf("Ride: '%s' inserted!\n", name);
        return;
    }
    
    // Handle insertion at middle or tail
    struct ride *current = park->rides;
    int position = 1;
    
    // If list is empty and n > 1, insert at head
    if (current == NULL) {
        park->rides = new_ride;
        printf("Ride: '%s' inserted!\n", name);
        return;
    }
    
    // Find the node before insertion position
    while (current->next != NULL && position < n - 1) {
        current = current->next;
        position++;
    }
    
    // Insert new node
    new_ride->next = current->next;
    current->next = new_ride;
    
    printf("Ride: '%s' inserted!\n", name);
}

// Stage 2.2
// Function to add a visitor to a ride queue
// Params:
//      park - a pointer to the park
// Returns: None
void join_ride_queue(struct park *park) {
    char ride_name[MAX_SIZE];
    char visitor_name[MAX_SIZE];
    
    // Scan ride name and visitor name
    scan_name(ride_name);
    scan_name(visitor_name);
    
    // Error check: find ride
    struct ride *ride = find_ride(park, ride_name);
    if (ride == NULL) {
        printf("ERROR: No ride exists with name '%s'.\n", ride_name);
        return;
    }
    
    // Error check: find visitor (this will remove visitor from roaming list)
    struct visitor *visitor = find_and_remove_visitor(park, visitor_name);
    if (visitor == NULL) {
        printf("ERROR: No visitor exists with name '%s'.\n", visitor_name);
        return;
    }
    
    // Error check: check if visitor meets height requirement
    if (visitor->height < ride->min_height) {
        printf("ERROR: '%s' is not tall enough to ride '%s'.\n", visitor_name, ride_name);
        // Need to add visitor back to roaming list
        visitor->next = park->visitors;
        park->visitors = visitor;
        park->total_visitors++;
        return;
    }
    
    // Error check: check if queue is full
    int queue_length = count_queue_length(ride->queue);
    if (queue_length >= ride->queue_capacity) {
        printf("ERROR: The queue for '%s' is full. '%s' cannot join the queue.\n", ride_name, visitor_name);
        // Need to add visitor back to roaming list
        visitor->next = park->visitors;
        park->visitors = visitor;
        park->total_visitors++;
        return;
    }
    
    // Add visitor to the tail of the queue
    if (ride->queue == NULL) {
        // Queue is empty, directly set head pointer
        ride->queue = visitor;
    } else {
        // Traverse to the end of queue
        struct visitor *current = ride->queue;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = visitor;
    }
    
    // visitor->next is already set to NULL in find_and_remove_visitor
    
    // Print success message
    printf("Visitor: '%s' has entered the queue for '%s'.\n", visitor_name, ride_name);
}

// Stage 2.3
// Function to remove a visitor from any ride queue and return them to roaming
// Params:
//      park - a pointer to the park
// Returns: None
void remove_visitor_from_queue(struct park *park) {
    char visitor_name[MAX_SIZE];
    
    // Scan visitor name
    scan_name(visitor_name);
    
    // Try to find and remove visitor from all queues
    struct visitor *visitor = find_and_remove_from_queues(park, visitor_name);
    
    // Error check: if visitor not found
    if (visitor == NULL) {
        printf("ERROR: Visitor '%s' not found in any queue.\n", visitor_name);
        return;
    }
    
    // Add visitor to the tail of roaming list
    if (park->visitors == NULL) {
        // Roaming list is empty, directly set head pointer
        park->visitors = visitor;
    } else {
        // Traverse to the end of roaming list
        struct visitor *current = park->visitors;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = visitor;
    }
    
    // Increment total visitor count (visitor becomes roaming again)
    park->total_visitors++;
    
    // Print success message
    printf("Visitor: '%s' has been removed from their ride queue and is now roaming the park.\n", visitor_name);
}

// Stage 2.4
// Function to move a visitor to a specific ride's queue
// Params:
//      park - a pointer to the park
// Returns: None
void move_visitor_to_ride(struct park *park) {
    char visitor_name[MAX_SIZE];
    char ride_name[MAX_SIZE];
    
    // Scan visitor name and ride name
    scan_name(visitor_name);
    scan_name(ride_name);
    
    // Error check 1: find target ride
    struct ride *target_ride = find_ride(park, ride_name);
    if (target_ride == NULL) {
        printf("ERROR: No ride exists with name '%s'.\n", ride_name);
        return;
    }
    
    // Error check 2: check if visitor exists (anywhere in the park)
    // We need to check if visitor exists, but not remove, as there may be other errors
    int visitor_exists = 0;
    
    // Check if in roaming list
    struct visitor *temp = park->visitors;
    while (temp != NULL) {
        if (strcmp(temp->name, visitor_name) == 0) {
            visitor_exists = 1;
            break;
        }
        temp = temp->next;
    }
    
    // If not in roaming list, check if in any queue
    if (!visitor_exists) {
        struct ride *current_ride = park->rides;
        while (current_ride != NULL && !visitor_exists) {
            if (visitor_in_ride_queue(current_ride, visitor_name)) {
                visitor_exists = 1;
                break;
            }
            current_ride = current_ride->next;
        }
    }
    
    if (!visitor_exists) {
        printf("ERROR: No visitor with name: '%s' exists.\n", visitor_name);
        return;
    }
    
    // Error check 3: check if visitor is already in target ride's queue
    if (visitor_in_ride_queue(target_ride, visitor_name)) {
        printf("ERROR: '%s' is already in the queue for '%s'.\n", visitor_name, ride_name);
        return;
    }
    
    // Now we're sure visitor exists and is not in target queue, can try to remove visitor
    struct visitor *visitor = find_and_remove_visitor_anywhere(park, visitor_name);
    
    // Error check 4: check if visitor meets height requirement
    if (visitor->height < target_ride->min_height) {
        printf("ERROR: '%s' is not tall enough to ride '%s'.\n", visitor_name, ride_name);
        
        // Need to add visitor back to original location
        // For simplicity, we add visitor to the head of roaming list
        visitor->next = park->visitors;
        park->visitors = visitor;
        park->total_visitors++;
        return;
    }
    
    // Error check 5: check if queue is full
    int queue_length = count_queue_length(target_ride->queue);
    if (queue_length >= target_ride->queue_capacity) {
        printf("ERROR: The queue for '%s' is full. '%s' cannot join the queue.\n", ride_name, visitor_name);
        
        // Need to add visitor back to roaming list
        visitor->next = park->visitors;
        park->visitors = visitor;
        park->total_visitors++;
        return;
    }
    
    // All checks passed, add visitor to tail of target queue
    if (target_ride->queue == NULL) {
        // Queue is empty, directly set head pointer
        target_ride->queue = visitor;
    } else {
        // Traverse to end of queue
        struct visitor *current = target_ride->queue;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = visitor;
    }
    
    // visitor->next is already set to NULL in find_and_remove_visitor_anywhere
    
    // Print success message
    printf("Visitor: '%s' has been moved to the queue for '%s'.\n", visitor_name, ride_name);
}

// Stage 2.5
// Function to display total visitor statistics
// Params:
//      park - a pointer to the park
// Returns: None
void total_visitors(struct park *park) {
    // Count roaming visitors
    int roaming_visitors = 0;
    struct visitor *current_visitor = park->visitors;
    while (current_visitor != NULL) {
        roaming_visitors++;
        current_visitor = current_visitor->next;
    }
    
    // Count visitors in queues
    int queued_visitors = 0;
    struct ride *current_ride = park->rides;
    while (current_ride != NULL) {
        queued_visitors += count_queue_length(current_ride->queue);
        current_ride = current_ride->next;
    }
    
    // Calculate total visitors
    int total = roaming_visitors + queued_visitors;
    
    // Print statistics
    printf("Total visitors: %d\n", total);
    printf("Visitors walking around: %d\n", roaming_visitors);
    printf("Visitors in queues: %d\n", queued_visitors);
}

// Stage 2.5
// Function to count visitors in a range of rides
// Params:
//      park - a pointer to the park
// Returns: None
void count_visitors_in_range(struct park *park) {
    char start_name[MAX_SIZE];
    char end_name[MAX_SIZE];
    char direction;
    
    // Scan start ride name, end ride name and direction
    scan_name(start_name);
    scan_name(end_name);
    scanf(" %c", &direction);
    
    // Find start and end rides
    struct ride *start_ride = find_ride(park, start_name);
    struct ride *end_ride = find_ride(park, end_name);
    
    // Error check: check if rides exist
    if (start_ride == NULL || end_ride == NULL) {
        printf("ERROR: One or both rides do not exist ('%s' or '%s').\n", start_name, end_name);
        return;
    }
    
    // If start and end are the same ride
    if (strcmp(start_name, end_name) == 0) {
        int count = count_queue_length(start_ride->queue);
        if (direction == '>') {
            printf("Total visitors from '%s' to '%s': %d.\n", start_name, end_name, count);
        } else {
            printf("Total visitors from '%s' to '%s': %d.\n", end_name, start_name, count);
        }
        return;
    }
    
    int total_count = 0;
    
    if (direction == '>') {
        // Traverse from start_name to end_name direction
        struct ride *current = start_ride;
        int found_end = 0;
        
        // First traversal: from start_ride to end of linked list
        while (current != NULL && !found_end) {
            total_count += count_queue_length(current->queue);
            if (current == end_ride) {
                found_end = 1;
            }
            current = current->next;
        }
        
        // If end_ride not found, need to wrap around from head
        if (!found_end) {
            current = park->rides;
            while (current != start_ride) {
                total_count += count_queue_length(current->queue);
                if (current == end_ride) {
                    found_end = 1;
                    break;
                }
                current = current->next;
            }
        }
        
        printf("Total visitors from '%s' to '%s': %d.\n", start_name, end_name, total_count);
    } else {
        // direction == '<', traverse from end_name to start_name direction
        struct ride *current = end_ride;
        int found_start = 0;
        
        // First traversal: from end_ride to end of linked list
        while (current != NULL && !found_start) {
            total_count += count_queue_length(current->queue);
            if (current == start_ride) {
                found_start = 1;
            }
            current = current->next;
        }
        
        // If start_ride not found, need to wrap around from head
        if (!found_start) {
            current = park->rides;
            while (current != end_ride) {
                total_count += count_queue_length(current->queue);
                if (current == start_ride) {
                    found_start = 1;
                    break;
                }
                current = current->next;
            }
        }
        
        printf("Total visitors from '%s' to '%s': %d.\n", end_name, start_name, total_count);
    }
}

// Stage 3.2
// Function to remove a visitor entirely from the park
// Params:
//      park - a pointer to the park
// Returns: None
void leave_park(struct park *park) {
    char visitor_name[MAX_SIZE];
    
    // Scan visitor name
    scan_name(visitor_name);
    
    // First check if visitor is in roaming list
    struct visitor *visitor = find_and_remove_visitor(park, visitor_name);
    if (visitor != NULL) {
        // Visitor is in roaming list, find_and_remove_visitor has already decreased total_visitors
        free(visitor);
        printf("Visitor: '%s' has left the park.\n", visitor_name);
        return;
    }
    
    // If not in roaming list, try to find and remove from queues
    visitor = find_and_remove_from_queues(park, visitor_name);
    if (visitor != NULL) {
        // Visitor is in queue, need to manually decrease total_visitors
        park->total_visitors--;
        free(visitor);
        printf("Visitor: '%s' has left the park.\n", visitor_name);
        return;
    }
    
    // If visitor not found in either location
    printf("ERROR: Visitor '%s' not found in the park.\n", visitor_name);
}

// Stage 3.3
// Function to operate a single ride
// Params:
//      park - a pointer to the park
//      ride - a pointer to the ride to operate
// Returns: None
void operate_single_ride(struct park *park, struct ride *ride) {
    int riders_taken = 0;
    struct visitor *riders[ride->rider_capacity]; // Temporary storage for visitors to move
    
    // Take rider_capacity visitors from the head of the queue
    while (riders_taken < ride->rider_capacity && ride->queue != NULL) {
        struct visitor *rider = ride->queue;
        ride->queue = ride->queue->next;
        rider->next = NULL; // Clear next pointer
        riders[riders_taken] = rider;
        riders_taken++;
    }
    
    // Add taken visitors to the end of roaming list in order
    for (int i = 0; i < riders_taken; i++) {
        if (park->visitors == NULL) {
            // Roaming list is empty, directly set head pointer
            park->visitors = riders[i];
        } else {
            // Traverse to the end of roaming list
            struct visitor *current = park->visitors;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = riders[i];
        }
        // Increment total visitor count
        park->total_visitors++;
    }
}

// Helper function to recursively operate rides in reverse order
// Params:
//      park - a pointer to the park
//      ride - current ride in the linked list
// Returns: None
void operate_rides_recursive(struct park *park, struct ride *ride) {
    if (ride == NULL) {
        return;
    }
    
        // First recurse to the end of the linked list
    operate_rides_recursive(park, ride->next);
    
    // Operate current ride on return from recursion (implements reverse order)
    operate_single_ride(park, ride);
}

// Function to operate all rides in the park
// Params:
//      park - a pointer to the park
// Returns: None
void operate_rides(struct park *park) {
    // If no rides, return directly
    if (park->rides == NULL) {
    return;
    }
    
    // Recursively process all rides (in reverse order)
    operate_rides_recursive(park, park->rides);
}

// Stage 3.4
// Helper function to calculate available capacity for rides of the same type
// Params:
//      park - a pointer to the park
//      target_ride - the ride to be shut down (exclude from calculation)
//      ride_type - the type of ride to check
// Returns: total available capacity
int calculate_available_capacity(struct park *park, struct ride *target_ride, enum ride_type ride_type) {
    int total_capacity = 0;
    struct ride *current = park->rides;
    
    while (current != NULL) {
        if (current != target_ride && current->type == ride_type) {
            int current_queue_count = count_queue_length(current->queue);
            int available_space = current->queue_capacity - current_queue_count;
            total_capacity += available_space;
        }
        current = current->next;
    }
    
    return total_capacity;
}

// Helper function to redistribute visitors to rides of the same type
// Params:
//      park - a pointer to the park
//      visitors - array of visitors to redistribute
//      visitor_count - number of visitors
//      target_ride - the ride to be shut down (exclude from redistribution)
//      ride_type - the type of ride to redistribute to
// Returns: 1 if successful, 0 if failed
int redistribute_visitors(struct park *park, struct visitor **visitors, int visitor_count, 
                         struct ride *target_ride, enum ride_type ride_type) {
    struct ride *current = park->rides;
    int visitors_placed = 0;
    
    while (current != NULL && visitors_placed < visitor_count) {
        if (current != target_ride && current->type == ride_type) {
            // 将游客添加到当前游乐设施的队列末尾，直到达到容量
            while (visitors_placed < visitor_count) {
                int current_queue_count = count_queue_length(current->queue);
                if (current_queue_count >= current->queue_capacity) {
                    break; // 当前游乐设施已满
                }
                
                // 添加游客到队列末尾
                struct visitor *visitor_to_add = visitors[visitors_placed];
                if (current->queue == NULL) {
                    current->queue = visitor_to_add;
                } else {
                    struct visitor *queue_end = current->queue;
                    while (queue_end->next != NULL) {
                        queue_end = queue_end->next;
                    }
                    queue_end->next = visitor_to_add;
                }
                visitor_to_add->next = NULL;
                visitors_placed++;
            }
        }
        current = current->next;
    }
    
    return (visitors_placed == visitor_count);
}

// Helper function to remove a ride from the park and free its memory
// Params:
//      park - a pointer to the park
//      target_ride - the ride to remove
// Returns: None
void remove_ride_from_park(struct park *park, struct ride *target_ride) {
    if (park->rides == target_ride) {
        // Remove head ride
        park->rides = target_ride->next;
    } else {
        // Remove middle or tail ride
        struct ride *prev = park->rides;
        while (prev != NULL && prev->next != target_ride) {
            prev = prev->next;
        }
        if (prev != NULL) {
            prev->next = target_ride->next;
        }
    }
    
    // Free ride memory
    free(target_ride);
}

// Function to shut down a ride and redistribute its visitors
// Params:
//      park - a pointer to the park
// Returns: None
void shut_down_ride(struct park *park) {
    char ride_name[MAX_SIZE];
    
    // Scan ride name
    scan_name(ride_name);
    
    // Find the ride to shut down
    struct ride *target_ride = find_ride(park, ride_name);
    
    // Error check: does ride exist
    if (target_ride == NULL) {
        printf("ERROR: No ride exists with name: '%s'.\n", ride_name);
        return;
    }
    
    // Collect all visitors in the queue
    int visitor_count = count_queue_length(target_ride->queue);
    
    if (visitor_count == 0) {
        // Queue is empty, directly remove ride
        remove_ride_from_park(park, target_ride);
        printf("Ride: '%s' shut down.\n", ride_name);
        return;
    }
    
    // Create visitor array to temporarily store visitors in queue
    struct visitor **visitors = malloc(visitor_count * sizeof(struct visitor*));
    struct visitor *current_visitor = target_ride->queue;
    
    for (int i = 0; i < visitor_count; i++) {
        visitors[i] = current_visitor;
        current_visitor = current_visitor->next;
        visitors[i]->next = NULL; // Clear next pointer
    }
    
    // Clear target ride's queue
    target_ride->queue = NULL;
    
    // Calculate available capacity of same type rides
    int available_capacity = calculate_available_capacity(park, target_ride, target_ride->type);
    
    // Try to redistribute visitors
    if (available_capacity >= visitor_count) {
        // Sufficient capacity, redistribute visitors
        if (redistribute_visitors(park, visitors, visitor_count, target_ride, target_ride->type)) {
            // Successfully redistributed
            remove_ride_from_park(park, target_ride);
            printf("Ride: '%s' shut down.\n", ride_name);
        } else {
            // Redistribution failed, this shouldn't happen but for safety
            printf("ERROR: Not enough capacity to redistribute all visitors from '%s'.\n", ride_name);
            // Add visitors back to roaming list
            for (int i = 0; i < visitor_count; i++) {
                if (park->visitors == NULL) {
                    park->visitors = visitors[i];
                } else {
                    struct visitor *roaming_end = park->visitors;
                    while (roaming_end->next != NULL) {
                        roaming_end = roaming_end->next;
                    }
                    roaming_end->next = visitors[i];
                }
                park->total_visitors++;
            }
            remove_ride_from_park(park, target_ride);
            printf("Ride: '%s' shut down.\n", ride_name);
        }
    } else {
        // Insufficient capacity, add all visitors to roaming list
        printf("ERROR: Not enough capacity to redistribute all visitors from '%s'.\n", ride_name);
        for (int i = 0; i < visitor_count; i++) {
            if (park->visitors == NULL) {
                park->visitors = visitors[i];
            } else {
                struct visitor *roaming_end = park->visitors;
                while (roaming_end->next != NULL) {
                    roaming_end = roaming_end->next;
                }
                roaming_end->next = visitors[i];
            }
            park->total_visitors++;
        }
        remove_ride_from_park(park, target_ride);
        printf("Ride: '%s' shut down.\n", ride_name);
    }
    
    // Release temporary array
    free(visitors);
}

// Stage 4.1
// Helper function to find two rides with smallest queue lengths of a specific type
// Params:
//      park - a pointer to the park
//      ride_type - the type of ride to search for
//      smallest - pointer to store the smallest ride
//      second_smallest - pointer to store the second smallest ride
// Returns: 1 if found two rides, 0 otherwise
int find_two_smallest_rides(struct park *park, enum ride_type ride_type, 
                           struct ride **smallest, struct ride **second_smallest) {
    *smallest = NULL;
    *second_smallest = NULL;
    
    struct ride *current = park->rides;
    
    // Find all rides of the specified type and their queue lengths
    while (current != NULL) {
        if (current->type == ride_type) {
            int queue_length = count_queue_length(current->queue);
            
            if (*smallest == NULL) {
                *smallest = current;
            } else if (*second_smallest == NULL) {
                int smallest_length = count_queue_length((*smallest)->queue);
                if (queue_length < smallest_length) {
                    *second_smallest = *smallest;
                    *smallest = current;
                } else {
                    *second_smallest = current;
                }
            } else {
                int smallest_length = count_queue_length((*smallest)->queue);
                int second_smallest_length = count_queue_length((*second_smallest)->queue);
                
                if (queue_length < smallest_length) {
                    *second_smallest = *smallest;
                    *smallest = current;
                } else if (queue_length < second_smallest_length) {
                    *second_smallest = current;
                }
            }
        }
        current = current->next;
    }
    
    return (*smallest != NULL && *second_smallest != NULL);
}

// Helper function to merge two queues alternately
// Params:
//      target_ride - the ride to merge queues into
//      source_ride - the ride to merge queues from
// Returns: None
void merge_queues_alternately(struct ride *target_ride, struct ride *source_ride) {
    // Convert queues to arrays for easier manipulation
    int target_length = count_queue_length(target_ride->queue);
    int source_length = count_queue_length(source_ride->queue);
    
    struct visitor **target_array = NULL;
    struct visitor **source_array = NULL;
    
    // Convert target queue to array
    if (target_length > 0) {
        target_array = malloc(target_length * sizeof(struct visitor*));
        struct visitor *current = target_ride->queue;
        for (int i = 0; i < target_length; i++) {
            target_array[i] = current;
            current = current->next;
            target_array[i]->next = NULL;
        }
    }
    
    // Convert source queue to array
    if (source_length > 0) {
        source_array = malloc(source_length * sizeof(struct visitor*));
        struct visitor *current = source_ride->queue;
        for (int i = 0; i < source_length; i++) {
            source_array[i] = current;
            current = current->next;
            source_array[i]->next = NULL;
        }
    }
    
    // Clear both queues
    target_ride->queue = NULL;
    source_ride->queue = NULL;
    
    // Determine which queue should start first
    struct visitor **first_array, **second_array;
    int first_length, second_length;
    
    // Always keep the target ride and merge source into it
    // Start with the longer queue, or the target queue if same length
    if (source_length > target_length) {
        // Source queue starts first (longer queue)
        first_array = source_array;
        first_length = source_length;
        second_array = target_array;
        second_length = target_length;
    } else {
        // Target queue starts first (shorter or same length)
        first_array = target_array;
        first_length = target_length;
        second_array = source_array;
        second_length = source_length;
    }
    
    // Merge alternately
    struct visitor *merged_tail = NULL;
    int first_index = 0, second_index = 0;
    int turn = 0; // 0 for first array, 1 for second array
    
    while (first_index < first_length || second_index < second_length) {
        struct visitor *to_add = NULL;
        
        if (turn == 0 && first_index < first_length) {
            to_add = first_array[first_index++];
            turn = 1;
        } else if (turn == 1 && second_index < second_length) {
            to_add = second_array[second_index++];
            turn = 0;
        } else if (first_index < first_length) {
            to_add = first_array[first_index++];
        } else if (second_index < second_length) {
            to_add = second_array[second_index++];
        }
        
        if (to_add != NULL) {
            if (target_ride->queue == NULL) {
                target_ride->queue = to_add;
                merged_tail = to_add;
            } else {
                merged_tail->next = to_add;
                merged_tail = to_add;
            }
        }
    }
    
    // Free temporary arrays
    if (target_array) free(target_array);
    if (source_array) free(source_array);
}

// Function to merge two rides of the same type
// Params:
//      park - a pointer to the park
// Returns: None
void merge_rides(struct park *park) {
    enum ride_type type = scan_type();
    
    // Find two smallest rides of the specified type
    struct ride *smallest = NULL;
    struct ride *second_smallest = NULL;
    
    if (!find_two_smallest_rides(park, type, &smallest, &second_smallest)) {
        printf("ERROR: Not enough rides of the specified type to merge.\n");
        return;
    }
    
    // Determine which ride should be kept (the one with smaller queue, or closer to head if same)
    struct ride *keep_ride = NULL;
    struct ride *remove_ride = NULL;
    
    int smallest_length = count_queue_length(smallest->queue);
    int second_smallest_length = count_queue_length(second_smallest->queue);
    
    if (smallest_length < second_smallest_length) {
        keep_ride = smallest;
        remove_ride = second_smallest;
    } else if (second_smallest_length < smallest_length) {
        keep_ride = second_smallest;
        remove_ride = smallest;
    } else {
        // Same length, keep the one closer to the head
        struct ride *current = park->rides;
        while (current != NULL) {
            if (current == smallest || current == second_smallest) {
                if (keep_ride == NULL) {
                    keep_ride = current;
                } else {
                    remove_ride = current;
                    break;
                }
            }
            current = current->next;
        }
    }
    
    // Merge capacities
    keep_ride->rider_capacity += remove_ride->rider_capacity;
    keep_ride->queue_capacity += remove_ride->queue_capacity;
    
    // Merge queues alternately
    merge_queues_alternately(keep_ride, remove_ride);
    
    // Remove the other ride from the park
    remove_ride_from_park(park, remove_ride);
    
    printf("Merged the two smallest rides of type '%s'.\n", type_to_string(type));
}

// Stage 4.2
// Helper function to generate a unique ride name with suffix
// Params:
//      park - a pointer to the park
//      base_name - the base name for the ride
//      suffix - the suffix number
//      result - buffer to store the generated name
// Returns: None
void generate_unique_ride_name(struct park *park, char base_name[MAX_SIZE], int suffix, char result[MAX_SIZE]) {
    // Calculate space needed for suffix
    char suffix_str[20];
    sprintf(suffix_str, "_%d", suffix);
    int suffix_len = strlen(suffix_str);
    
    // Truncate base name if necessary to fit suffix
    int base_len = strlen(base_name);
    int max_base_len = MAX_SIZE - 1 - suffix_len;
    
    if (base_len > max_base_len) {
        base_len = max_base_len;
    }
    
    // Create the name
    strncpy(result, base_name, base_len);
    result[base_len] = '\0';
    strcat(result, suffix_str);
}

// Helper function to find next available suffix number
// Params:
//      park - a pointer to the park
//      base_name - the base name for the ride
//      start_suffix - the starting suffix number to check
// Returns: the next available suffix number
int find_next_available_suffix(struct park *park, char base_name[MAX_SIZE], int start_suffix) {
    char test_name[MAX_SIZE];
    int suffix = start_suffix;
    
    while (1) {
        generate_unique_ride_name(park, base_name, suffix, test_name);
        if (!ride_name_exists(park, test_name)) {
            return suffix;
        }
        suffix++;
    }
}

// Helper function to distribute visitors among new rides
// Params:
//      visitors - array of visitors to distribute
//      visitor_count - total number of visitors
//      new_rides - array of new rides
//      n - number of new rides
// Returns: None
void distribute_visitors_evenly(struct visitor **visitors, int visitor_count, struct ride **new_rides, int n) {
    int visitors_per_ride = visitor_count / n;
    int extra_visitors = visitor_count % n;
    
    int visitor_index = 0;
    
    for (int i = 0; i < n; i++) {
        int visitors_for_this_ride = visitors_per_ride;
        if (i < extra_visitors) {
            visitors_for_this_ride++; // First rides get extra visitors
        }
        
        // Add visitors to this ride's queue
        for (int j = 0; j < visitors_for_this_ride && visitor_index < visitor_count; j++) {
            struct visitor *visitor = visitors[visitor_index];
            visitor->next = NULL;
            
            if (new_rides[i]->queue == NULL) {
                new_rides[i]->queue = visitor;
            } else {
                struct visitor *current = new_rides[i]->queue;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = visitor;
            }
            visitor_index++;
        }
    }
}

// Function to split a ride into multiple smaller rides
// Params:
//      park - a pointer to the park
// Returns: None
void split_ride(struct park *park) {
    int n;
    char ride_name[MAX_SIZE];
    
    // Scan n and ride name
    scanf("%d", &n);
    scan_name(ride_name);
    
    // Error check 1: n must be > 1
    if (n <= 1) {
        printf("ERROR: Cannot split '%s' into %d rides. n must be > 1.\n", ride_name, n);
        return;
    }
    
    // Error check 2: find the ride to split
    struct ride *target_ride = find_ride(park, ride_name);
    if (target_ride == NULL) {
        printf("ERROR: No ride exists with name: '%s'.\n", ride_name);
        return;
    }
    
    // Collect all visitors from the original ride's queue
    int visitor_count = count_queue_length(target_ride->queue);
    struct visitor **visitors = NULL;
    
    if (visitor_count > 0) {
        visitors = malloc(visitor_count * sizeof(struct visitor*));
        struct visitor *current_visitor = target_ride->queue;
        
        for (int i = 0; i < visitor_count; i++) {
            visitors[i] = current_visitor;
            current_visitor = current_visitor->next;
            visitors[i]->next = NULL;
        }
    }
    
    // Create n new rides
    struct ride **new_rides = malloc(n * sizeof(struct ride*));
    
    // Keep track of used suffixes for this split operation
    int *used_suffixes = malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        // Find next available suffix, starting from i+1
        int suffix = i + 1;
        char test_name[MAX_SIZE];
        
        // Find an available suffix that hasn't been used in this split
        while (1) {
            generate_unique_ride_name(park, ride_name, suffix, test_name);
            
            // Check if name exists in park
            int name_exists = ride_name_exists(park, test_name);
            
            // Check if suffix already used in this split
            int suffix_used = 0;
            for (int j = 0; j < i; j++) {
                if (used_suffixes[j] == suffix) {
                    suffix_used = 1;
                    break;
                }
            }
            
            if (!name_exists && !suffix_used) {
                break; // Found available suffix
            }
            suffix++;
        }
        
        used_suffixes[i] = suffix;
        
        // Generate unique name
        char new_name[MAX_SIZE];
        generate_unique_ride_name(park, ride_name, suffix, new_name);
        
        // Create new ride with same properties as original
        new_rides[i] = create_ride(new_name, target_ride->type);
    }
    
    free(used_suffixes);
    
    // Distribute visitors evenly among new rides
    if (visitor_count > 0) {
        distribute_visitors_evenly(visitors, visitor_count, new_rides, n);
        free(visitors);
    }
    
    // Find the position of the target ride in the park's ride list
    struct ride *prev = NULL;
    struct ride *current = park->rides;
    
    while (current != NULL && current != target_ride) {
        prev = current;
        current = current->next;
    }
    
    // Replace target ride with new rides at the same position
    if (prev == NULL) {
        // Target ride is at head of list
        park->rides = new_rides[0];
    } else {
        // Target ride is in middle or at end
        prev->next = new_rides[0];
    }
    
    // Chain the new rides together
    for (int i = 0; i < n - 1; i++) {
        new_rides[i]->next = new_rides[i + 1];
    }
    
    // Connect the last new ride to what came after target ride
    new_rides[n - 1]->next = target_ride->next;
    
    // Free the original ride
    free(target_ride);
    free(new_rides);
    
    printf("Ride '%s' split into %d new rides.\n", ride_name, n);
}

// Stage 4.3
// Helper function to execute scheduled commands that are ready
// Params:
//      park - a pointer to the park
// Returns: None
void execute_ready_commands(struct park *park) {
    struct scheduled_command *current = park->scheduled_commands;
    struct scheduled_command *prev = NULL;
    
    while (current != NULL) {
        if (current->ticks_remaining == 0) {
            // Parse and execute the command
            char *command_str = current->command_string;
            
            // Check for quit command
            if (command_str[0] == 'q' && strlen(command_str) == 1) {  
                printf("ERROR: Cannot schedule quit command.\n");
            } else {
                // Execute the command by parsing it
                execute_scheduled_command_string(park, command_str);
            }
            
            // Remove this command from the list
            if (prev == NULL) {
                park->scheduled_commands = current->next;
            } else {
                prev->next = current->next;
            }
            
            struct scheduled_command *to_free = current;
            current = current->next;
            free(to_free);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// Helper function to execute a scheduled command string
// Params:
//      park - a pointer to the park
//      command_str - the command string to execute
// Returns: None
void execute_scheduled_command_string(struct park *park, char *command_str) {
    // Parse the command string and execute it
    // This is a simplified parser - in a real implementation you'd want more robust parsing
    
    char cmd = command_str[0];
    
    switch (cmd) {
        case 'a': {
            char type = command_str[2];
            if (type == 'v') {
                // Parse "a v [name] [height]"
                char name[MAX_SIZE];
                double height;
                sscanf(command_str + 4, "%s %lf", name, &height);
                
                // Create and add visitor directly
                if (height < 50 || height > 250) {
                    printf("ERROR: Height must be between 50 and 250.\n");
                    return;
                }
                if (park->total_visitors >= 40) {
                    printf("ERROR: Cannot add another visitor to the park. The park is at capacity.\n");
                    return;
                }
                if (visitor_name_exists(park, name)) {
                    printf("ERROR: '%s' already exists.\n", name);
                    return;
                }
                
                struct visitor *new_visitor = create_visitor(name, height);
                if (park->visitors == NULL) {
                    park->visitors = new_visitor;
                } else {
                    struct visitor *current = park->visitors;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = new_visitor;
                }
                park->total_visitors++;
                printf("Visitor: '%s' has entered the amusement park!\n", name);
                
            } else if (type == 'r') {
                // Parse "a r [name] [type]" 
                char name[MAX_SIZE];
                char type_str[MAX_SIZE];
                sscanf(command_str + 4, "%s %s", name, type_str);
                
                enum ride_type ride_type = string_to_type(type_str);
                if (ride_type == INVALID) {
                    printf("ERROR: Invalid ride type.\n");
                    return;
                }
                if (ride_name_exists(park, name)) {
                    printf("ERROR: '%s' already exists.\n", name);
                    return;
                }
                
                struct ride *new_ride = create_ride(name, ride_type);
                if (park->rides == NULL) {
                    park->rides = new_ride;
                } else {
                    struct ride *current = park->rides;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = new_ride;
                }
                printf("Ride: '%s' added!\n", name);
            }
            break;
        }
        case 's': {
            // Parse "s [n] [ride_name]"
            int n;
            char ride_name[MAX_SIZE];
            sscanf(command_str + 2, "%d %s", &n, ride_name);
            
            // Execute split command logic (full implementation)
            if (n <= 1) {
                printf("ERROR: Cannot split '%s' into %d rides. n must be > 1.\n", ride_name, n);
                return;
            }
            
            struct ride *target_ride = find_ride(park, ride_name);
            if (target_ride == NULL) {
                printf("ERROR: No ride exists with name: '%s'.\n", ride_name);
                return;
            }
            
            // Execute the actual split logic (copied from split_ride function)
            // Collect all visitors from the original ride's queue
            int visitor_count = count_queue_length(target_ride->queue);
            struct visitor **visitors = NULL;
            
            if (visitor_count > 0) {
                visitors = malloc(visitor_count * sizeof(struct visitor*));
                struct visitor *current_visitor = target_ride->queue;
                
                for (int i = 0; i < visitor_count; i++) {
                    visitors[i] = current_visitor;
                    current_visitor = current_visitor->next;
                    visitors[i]->next = NULL;
                }
            }
            
            // Create n new rides
            struct ride **new_rides = malloc(n * sizeof(struct ride*));
            
            // Keep track of used suffixes for this split operation
            int *used_suffixes = malloc(n * sizeof(int));
            
            for (int i = 0; i < n; i++) {
                // Find next available suffix, starting from i+1
                int suffix = i + 1;
                char test_name[MAX_SIZE];
                
                // Find an available suffix that hasn't been used in this split
                while (1) {
                    generate_unique_ride_name(park, ride_name, suffix, test_name);
                    
                    // Check if name exists in park
                    int name_exists = ride_name_exists(park, test_name);
                    
                    // Check if suffix already used in this split
                    int suffix_used = 0;
                    for (int j = 0; j < i; j++) {
                        if (used_suffixes[j] == suffix) {
                            suffix_used = 1;
                            break;
                        }
                    }
                    
                    if (!name_exists && !suffix_used) {
                        break; // Found available suffix
                    }
                    suffix++;
                }
                
                used_suffixes[i] = suffix;
                
                // Generate unique name
                char new_name[MAX_SIZE];
                generate_unique_ride_name(park, ride_name, suffix, new_name);
                
                // Create new ride with same properties as original
                new_rides[i] = create_ride(new_name, target_ride->type);
            }
            
            free(used_suffixes);
            
            // Distribute visitors evenly among new rides
            if (visitor_count > 0) {
                distribute_visitors_evenly(visitors, visitor_count, new_rides, n);
                free(visitors);
            }
            
            // Find the position of the target ride in the park's ride list
            struct ride *prev = NULL;
            struct ride *current = park->rides;
            
            while (current != NULL && current != target_ride) {
                prev = current;
                current = current->next;
            }
            
            // Replace target ride with new rides at the same position
            if (prev == NULL) {
                // Target ride is at head of list
                park->rides = new_rides[0];
            } else {
                // Target ride is in middle or at end
                prev->next = new_rides[0];
            }
            
            // Chain the new rides together
            for (int i = 0; i < n - 1; i++) {
                new_rides[i]->next = new_rides[i + 1];
            }
            
            // Connect the last new ride to what came after target ride
            new_rides[n - 1]->next = target_ride->next;
            
            // Free the original ride
            free(target_ride);
            free(new_rides);
            
            printf("Ride '%s' split into %d new rides.\n", ride_name, n);
            break;
        }
        case 'M': {
            // Parse "M [ride_type]"
            char type_str[MAX_SIZE];
            sscanf(command_str + 2, "%s", type_str);
            
            enum ride_type type = string_to_type(type_str);
            if (type == INVALID) {
                printf("ERROR: Invalid ride type.\n");
                return;
            }
            
            // Execute merge logic (full implementation)
            // Find two smallest rides of the specified type
            struct ride *smallest = NULL;
            struct ride *second_smallest = NULL;
            
            if (!find_two_smallest_rides(park, type, &smallest, &second_smallest)) {
                printf("ERROR: Not enough rides of the specified type to merge.\n");
                return;
            }
            
            // Determine which ride should be kept (the one with smaller queue, or closer to head if same)
            struct ride *keep_ride = NULL;
            struct ride *remove_ride = NULL;
            
            int smallest_length = count_queue_length(smallest->queue);
            int second_smallest_length = count_queue_length(second_smallest->queue);
            
            if (smallest_length < second_smallest_length) {
                keep_ride = smallest;
                remove_ride = second_smallest;
            } else if (second_smallest_length < smallest_length) {
                keep_ride = second_smallest;
                remove_ride = smallest;
            } else {
                // Same length, keep the one closer to the head
                struct ride *current = park->rides;
                while (current != NULL) {
                    if (current == smallest || current == second_smallest) {
                        if (keep_ride == NULL) {
                            keep_ride = current;
                        } else {
                            remove_ride = current;
                            break;
                        }
                    }
                    current = current->next;
                }
            }
            
            // Merge capacities
            keep_ride->rider_capacity += remove_ride->rider_capacity;
            keep_ride->queue_capacity += remove_ride->queue_capacity;
            
            // Merge queues alternately
            merge_queues_alternately(keep_ride, remove_ride);
            
            // Remove the other ride from the park
            remove_ride_from_park(park, remove_ride);
            
            printf("Merged the two smallest rides of type '%s'.\n", type_to_string(type));
            break;
        }
        default:
            printf("ERROR: Invalid command.\n");
            break;
    }
}

// Helper function to decrement tick counters
// Params:
//      park - a pointer to the park
// Returns: None
void decrement_tick_counters(struct park *park) {
    struct scheduled_command *current = park->scheduled_commands;
    
    while (current != NULL) {
        current->ticks_remaining--;
        current = current->next;
    }
}

// Function to schedule a command for future execution
// Params:
//      park - a pointer to the park
// Returns: None
void schedule_command(struct park *park) {
    int n;
    scanf("%d", &n);
    
    // Error check: n must be > 0
    if (n < 1) {
        printf("ERROR: Invalid tick delay: %d. Must be > 0.\n", n);
        return;
    }
    
    // Read the rest of the line as the command
    char command_string[1000];
    fgets(command_string, sizeof(command_string), stdin);
    
    // Remove newline if present
    int len = strlen(command_string);
    if (len > 0 && command_string[len-1] == '\n') {
        command_string[len-1] = '\0';
    }
    
    // Create new scheduled command
    struct scheduled_command *new_command = malloc(sizeof(struct scheduled_command));
    new_command->ticks_remaining = n;
    strcpy(new_command->command_string, command_string + 1); // Skip the space after n
    new_command->next = NULL;
    
    // Add to end of scheduled commands list
    if (park->scheduled_commands == NULL) {
        park->scheduled_commands = new_command;
    } else {
        struct scheduled_command *current = park->scheduled_commands;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_command;
    }
    
    printf("Command scheduled to run in %d ticks.\n", n);
}

// Function to advance the simulation by n ticks
// Params:
//      park - a pointer to the park
// Returns: None
void advance_ticks(struct park *park) {
    int n;
    scanf("%d", &n);
    
    // Error check: n must be > 0
    if (n < 1) {
        printf("ERROR: Invalid tick delay: %d. Must be > 0.\n", n);
        return;
    }
    
    // Advance by n ticks
    for (int i = 0; i < n; i++) {
        // Decrement all tick counters
        decrement_tick_counters(park);
        
        // Execute ready commands
        execute_ready_commands(park);
    }
}

// Stage 1.4
// Function to print the park
// Params:
//      park - a pointer to the park
// Returns: None
void print_park(struct park *park) {
    // Check if park is completely empty
    if (park->rides == NULL && park->visitors == NULL) {
     // Print welcome message with park name
        print_welcome_message(park->name);
        printf("The amusement park is empty!\n\n");
        return;
    }
    
    // Print welcome message with park name
    print_welcome_message(park->name);
    
    // Print rides section
    printf("Rides:\n");
    if (park->rides == NULL) {
        printf("  No rides!\n");
    } else {
        struct ride *current_ride = park->rides;
        while (current_ride != NULL) {
            print_ride(current_ride);
            current_ride = current_ride->next;
        }
    }
    
    // Print visitors section
    printf("Visitors:\n");
    if (park->visitors == NULL) {
        printf("  No visitors!\n");
    } else {
        struct visitor *current_visitor = park->visitors;
        while (current_visitor != NULL) {
            printf("  %s (%.2lfcm)\n", current_visitor->name, current_visitor->height);
            current_visitor = current_visitor->next;
        }
    }
    
    printf("\n");
}

// Helper function to check if a ride name already exists
// Returns 1 if exists, 0 if not
int ride_name_exists(struct park *park, char name[MAX_SIZE]) {
    struct ride *current = park->rides;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return 1; // Name exists
        }
        current = current->next;
    }
    return 0; // Name doesn't exist
}

// Helper function to check if a visitor name already exists
// Returns 1 if exists, 0 if not  
int visitor_name_exists(struct park *park, char name[MAX_SIZE]) {
    struct visitor *current = park->visitors;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return 1; // Name exists
        }
        current = current->next;
    }
    return 0; // Name doesn't exist
}

// Helper function to find a ride by name
// Returns pointer to ride if found, NULL if not found
struct ride *find_ride(struct park *park, char name[MAX_SIZE]) {
    struct ride *current = park->rides;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current; // Found the ride
        }
        current = current->next;
    }
    return NULL; // Ride not found
}

// Helper function to find and remove a visitor from the roaming list
// Returns pointer to visitor if found and removed, NULL if not found
struct visitor *find_and_remove_visitor(struct park *park, char name[MAX_SIZE]) {
    struct visitor *current = park->visitors;
    struct visitor *prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            // Found the visitor, remove from list
            if (prev == NULL) {
                // Removing head of list
                park->visitors = current->next;
            } else {
                // Removing from middle or end
                prev->next = current->next;
            }
            current->next = NULL; // Clear the next pointer
            park->total_visitors--; // Decrease total count
            return current; // Return the removed visitor
        }
        prev = current;
        current = current->next;
    }
    return NULL; // Visitor not found
}

// Helper function to count the length of a queue
// Returns the number of visitors in the queue
int count_queue_length(struct visitor *queue) {
    int count = 0;
    struct visitor *current = queue;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Helper function to find and remove a visitor from any ride queue
// Returns pointer to the visitor if found and removed, NULL if not found
struct visitor *find_and_remove_from_queues(struct park *park, char name[MAX_SIZE]) {
    struct ride *current_ride = park->rides;
    
    // Traverse all rides
    while (current_ride != NULL) {
        struct visitor *current_visitor = current_ride->queue;
        struct visitor *prev_visitor = NULL;
        
        // Search in current ride's queue
        while (current_visitor != NULL) {
            if (strcmp(current_visitor->name, name) == 0) {
                // Found visitor, remove from queue
                if (prev_visitor == NULL) {
                    // Remove head of queue
                    current_ride->queue = current_visitor->next;
                } else {
                    // Remove middle or tail
                    prev_visitor->next = current_visitor->next;
                }
                current_visitor->next = NULL; // Clear next pointer
                return current_visitor; // Return removed visitor
            }
            prev_visitor = current_visitor;
            current_visitor = current_visitor->next;
        }
        current_ride = current_ride->next;
    }
    return NULL; // Visitor not found
}

// Helper function to check if a visitor is in a specific ride's queue
// Returns 1 if visitor is in the queue, 0 if not
int visitor_in_ride_queue(struct ride *ride, char name[MAX_SIZE]) {
    struct visitor *current = ride->queue;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return 1; // Found visitor in this ride's queue
        }
        current = current->next;
    }
    return 0; // Visitor not in this ride's queue
}

// Helper function to find and remove a visitor from anywhere in the park
// (either roaming or in any ride queue)
// Returns pointer to the visitor if found and removed, NULL if not found
struct visitor *find_and_remove_visitor_anywhere(struct park *park, char name[MAX_SIZE]) {
    // First try to find and remove from roaming visitors
    struct visitor *visitor = find_and_remove_visitor(park, name);
    if (visitor != NULL) {
        return visitor; // Found in roaming list
    }
    
    // If not found in roaming, try to find and remove from ride queues
    visitor = find_and_remove_from_queues(park, name);
    return visitor; // Will return visitor if found, NULL if not found
}

// Stage 3.1
// Function to free all dynamically allocated memory in the park
// Params:
//      park - a pointer to the park
// Returns: None
void free_park(struct park *park) {
        if (park == NULL) {
    return;
    }
    
    // Free all rides and their queues
    struct ride *current_ride = park->rides;
    while (current_ride != NULL) {
        struct ride *next_ride = current_ride->next;
        
        // Free all visitors in current ride's queue
        struct visitor *current_visitor = current_ride->queue;
        while (current_visitor != NULL) {
            struct visitor *next_visitor = current_visitor->next;
            free(current_visitor);
            current_visitor = next_visitor;
        }
        
        // Free current ride
        free(current_ride);
        current_ride = next_ride;
    }
    
    // Free all roaming visitors
    struct visitor *current_visitor = park->visitors;
    while (current_visitor != NULL) {
        struct visitor *next_visitor = current_visitor->next;
        free(current_visitor);
        current_visitor = next_visitor;
    }
    
    // Free all scheduled commands
    struct scheduled_command *current_command = park->scheduled_commands;
    while (current_command != NULL) {
        struct scheduled_command *next_command = current_command->next;
        free(current_command);
        current_command = next_command;
    }
    
    // Free park structure itself
    free(park);
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