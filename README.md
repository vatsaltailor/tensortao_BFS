# Graph Processing with BFS

This repository contains a C++ implementation of graph processing using the Breadth-First Search (BFS) algorithm. BFS is a fundamental graph traversal algorithm that explores vertices in the order of their distance from the source node, layer by layer. It's widely used in various applications such as finding the shortest path in unweighted graphs, connectivity checking, and level-order traversal of trees.

## Features

- **Graph Representation**: Utilizes an efficient graph representation using CSR (Compressed Sparse Row) format to store vertices and edges.
- **BFS Implementation**: Implements the BFS algorithm to traverse the graph from a given source vertex, exploring all connected components.
- **Single Threaded**: The current implementation is single-threaded, suitable for educational and straightforward graph processing tasks.

## How to Run

To compile and run the BFS implementation, follow these steps:

1. **Compilation**: Use the following command to compile the project. Ensure you have a C++ compiler installed.

    ```bash
    g++ -o graph_bfs main.cpp -std=c++11
    ```

2. **Running the Program**: The executable expects three input files representing the graph: a beginning file (beg), a CSR file, and a weights file. Run the program using the command below:

    ```bash
    ./graph_bfs <beg_file> <csr_file> <weight_file>
    ```

    Replace `<beg_file>`, `<csr_file>`, and `<weight_file>` with your actual file paths.

### Example

Assuming you have `graph_beg.txt`, `graph_csr.txt`, and `graph_weights.txt` as your input files, run:

```bash
./graph_bfs graph_beg.txt graph_csr.txt graph_weights.txt
```

----
Major Contributors
----
Vatsal Tailor

