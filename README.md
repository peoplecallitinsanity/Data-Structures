# Train Simulation - Circular Doubly Linked List

This project implements a circular doubly linked list structure, simulating a train with a locomotive, carriages, and a mechanic. The project includes various operations for manipulating the train, such as:

- **Search Operations**: Find sequences of characters within the train.
- **Update Operations**: Modify the train by moving the mechanic or altering carriages.
- **Query Operations**: Display train or carriage information.
- **Execute Operation**: Executes operations from a queue.

## Function Implementations

### Core Data Structures
- **Train Structure**: Represents the train with a circular doubly linked list of carriages and a pointer to the current position of the mechanic.
- **Operation Queue**: A structure with pointers to the first and last operations in the queue, where each operation holds a name and a pointer to the next operation.

### Train Initialization
- `Tren initializareTren()`: Initializes the train with a dynamic allocation for the locomotive and mechanic. The train is set up as a circular list, where the locomotive is linked to the first carriage.
- `coadaOperatii *InitQ()`: Initializes and allocates memory for the operation queue.

### Update Operations
1. **MOVE_LEFT**: Moves the mechanic left, with special handling for moving past the locomotive in a circular fashion.
2. **MOVE_RIGHT**: Moves the mechanic right, adding new carriages when the mechanic reaches the end of the train.
3. **WRITE**: Writes a character in the carriage where the mechanic is currently positioned.
4. **CLEAR_CELL**: Removes the carriage where the mechanic is, with special cases for the first and last carriages.
5. **CLEAR_ALL**: Deallocates all carriages and resets the train to its initial state.
6. **INSERT_LEFT**: Inserts a new carriage to the left of the mechanic.
7. **INSERT_RIGHT**: Inserts a new carriage to the right of the mechanic.

### Search Operations
- **SEARCH**: Searches for a string within the train's carriages and moves the mechanic to the first match.
- **SEARCH_LEFT**: Similar to `SEARCH`, but searches leftward from the mechanic's position.
- **SEARCH_RIGHT**: Similar to `SEARCH`, but searches rightward.

### Query Operations
1. **SHOW_CURRENT**: Prints the inscription of the current carriage where the mechanic is located.
2. **SHOW**: Displays all the carriages and marks the mechanic's position.
3. **SWITCH**: Reverses the order of operations in the queue.

### Execute Operation
- `EXECUTE`: Executes the next operation in the queue and deallocates the memory for completed operations.

### Additional Functions
- **eliberareTrenulet**: Deallocates the train and its carriages.
- **eliberareCoada**: Frees the memory allocated for the operation queue.

This project covers train simulation using a circular doubly linked list, with the mechanic performing operations based on commands in the queue.
