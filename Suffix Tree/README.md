# Suffix Tree Implementation

This project implements a suffix tree to efficiently handle suffix-related operations. The following functionalities are provided, with a total score of **50 points + 10 points from Valgrind**.

## Functionality Overview

### Building the Suffix Tree

#### `createNode()`
This function initializes a new node for the suffix tree. Each new node contains an array of pointers to its children, all initialized to `NULL`.

#### `addSuffix()`
This function iterates through each suffix of a given word, starting from each character, and inserts the remaining substring as a suffix into the tree. For each character in the suffix, the index in the children array of the current node is calculated using the function `characterIndex()`.

#### `printTree()`
This function displays the suffix tree. It uses a queue to manage the order of node visitation, starting from the root and successively adding all children of each visited node to the queue. The function performs a breadth-first search (BFS) to ensure that the tree is displayed level by level, from left to right. For each node, the characters of its children are shown, which are then added to the queue for further processing.

### Additional Functions
- `int characterIndex(char c);`
  - This function helps determine the ASCII code of a character.

- `Node *dequeue(Queue *q);`
  - This function removes an element from the queue.

- `void freeTree(Node *root);`
  - This function deallocates the memory used by the tree.

## Checking for Suffixes in the Tree

The function `checkSuffix` determines whether a specified suffix exists in the constructed suffix tree. It takes the number of words to be inserted as suffixes and the number of suffixes to be searched for as input.

Within the function, each character of the given suffix is traversed until the terminal character (`\0`) is reached. For each character, its index is determined using the `characterIndex()` function. Then, we check if a child node exists at the determined index (`if (current->children[index] == NULL)`). If the child node at that index is `NULL`, it indicates that the searched suffix does not exist in the tree, and the function returns `false`. If the child node exists, the search continues.
