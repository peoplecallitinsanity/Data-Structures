# Graph Simulation - City Routes and Wear Levels

This project implements a graph structure to represent city routes and the wear levels of roads (edges) between cities (nodes). The primary structures include nodes for cities, edges for routes, and cost lists representing the wear levels of roads over time. Several functions allow for adding routes, updating wear levels, and extracting key routes based on specific criteria.

## Data Structures

### 1. **Node Structure (`nodLista`)**
   - `destinatie`: Holds the destination city's name.
   - `costuri`: Pointer to a list of wear levels (costs) representing the degree of wear.
   - `nrCosturi`: Number of wear levels.
   - `urmator`: Pointer to the next node (city) in the adjacency list.

### 2. **Adjacency List Structure (`ListaAdiacenta`)**
   - `sursa`: The name of the source city.
   - `noduriAdiacente`: Pointer to a vector of adjacent city nodes in the undirected graph.

### 3. **Graph Structure (`Graf`)**
   - `nrVarfuri`: Number of vertices (cities) in the graph.
   - `listeAdiacenta`: Pointer to the adjacency list representing city connections.
   - `muchii`: Pointer to an array of edges (routes).
   - `numarRute`: Number of routes (edges) in the graph.

### 4. **Edge Structure (`Muchie`)**
   - `sursa`: The name of the source city.
   - `destinatie`: The name of the destination city.
   - `costuri`: Pointer to the list of wear levels.
   - `nrCosturi`: Number of wear levels.

## Function Implementations

### 1. **Node and Graph Creation**
   - Functions to create nodes for the adjacency list, dynamically allocating memory for both the city and the wear level lists.
   - `creareGraf()`: Allocates memory for the adjacency list and the edge array and initializes them for each vertex. The number of vertices is calculated as twice the number of routes.

### 2. **Adding Edges**
   - `adaugaMuchie()`: Adds a route between two cities (source and destination) in the graph, updating the adjacency lists of both cities. This function ensures that if a city does not exist in the adjacency list, it is added, and memory is allocated for a new node. It also updates the edge array of the graph, allocating memory for the wear level lists.

### 3. **Wear Level Calculation**
   - `gasesteGradUzuraMaxVecin()`: Finds the maximum wear level among the neighbors of a specific edge and degree (index). The function checks the wear levels of adjacent nodes on the same edge and updates the maximum wear level (`maxGrad`). If the index is at the boundary of the list, it also checks indirect neighbors by traversing the entire graph.
   
   - `actualizareGradeUzura()`: Updates the wear levels of edges in the graph for a given number of years. This is done in two stages:
     - **Stage 1**: For each edge with a wear level of zero, it is updated to half the maximum wear level among its neighbors.
     - **Stage 2**: Doubles the wear levels of all non-zero values, ensuring they do not exceed a maximum of 100.

### 4. **Route Extraction**
   - `extrageRuteDePastrat()`: Selects routes from the graph with an average wear level below a given threshold. It stores the indices of these edges in a vector and returns the vector, which is displayed in the `main()` function.

### 5. **Memory Management**
   - `elibereazaGraf()`: Frees all memory used by the graph, including nodes, edges, and cost lists.

### 6. **Graph Output**
   - `afiseazaGraf()`: Outputs the results to a file, including the structure of the graph and the selected routes.

## Overview of Implementation
The project revolves around creating a graph representing city routes, updating the wear levels of these routes over time, and extracting routes that meet specific criteria. The dynamic memory management and two-stage wear level update process allow for efficient simulation and analysis of road degradation over the years.

