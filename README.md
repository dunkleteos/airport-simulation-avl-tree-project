# airport-simulation-avl-tree-project
An AVL Tree-based flight management system in C that efficiently indexes, searches, and prioritizes Istanbul Airport flight data by destination and distance.

-Istanbul Airport Flight Data Analysis

This project implements a robust flight management and indexing system for **Istanbul Airport** using an **AVL Tree** data structure. It was developed as part of a data structures assignment and achieved a score of **98/100**.

-Overview
The application processes flight data including destination, airline, flight type, date, and distance from an external text file. It organizes this data into a self-balancing binary search tree (AVL Tree) to ensure efficient indexing and searching.

-Features
* **Automated Data Loading:** Parses a text file (e.g., `sampleData.txt`) to build the AVL tree based on flight destinations.
* **Duplicate Destination Handling:** Flights to the same destination are stored within the same node, ensuring no data is lost.
* **Alphabetical Indexing:** Displays the full flight index in alphabetical order using in-order traversal.
* **Search Functionality:** Provides detailed information for a specific destination with O(log n) average complexity.
* **Distance Analysis:** Finds and displays the flight(s) with the highest mileage (furthest destination).

-Project Structure
* `avltree.h`: Header file containing the AVL Tree ADT and function prototypes.
* `avltree.c`: Implementation of the AVL Tree balancing algorithms and rotations.
* `flightsApp.c`: Main application logic, menu interface, and file processing functions.
* `sampleData.txt`: Sample input file containing flight records separated by semicolons.

-How to Run
1. Ensure you have a C compiler (like GCC) or an IDE like CLion installed.
2. Compile the source files:
   ```bash
   gcc flightsApp.c avltree.c -o flightsApp
