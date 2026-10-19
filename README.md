# Algorithms

This repository contains a collection of standalone C++ implementations prepared
for algorithm and data-structure laboratory exercises. Each source file has its
own `main()` function, so the projects are intended to be compiled and run
independently.

The implementations are primarily written in Polish and include small
experiments that measure execution time, structure height, search results, or
other algorithm statistics.

## Repository contents

All source files are located in [`Algorithms/`](./Algorithms/).

| Project | File | Description |
| --- | --- | --- |
| Doubly linked list | [`Linked_list.cpp`](./Algorithms/Linked_list.cpp) | A templated doubly linked list with insertion at the beginning and end, deletion at the beginning and end, indexed access, element replacement, printing, and clearing. The `main()` function measures insertion and deletion times for input sizes from `10` to `10^6`. |
| Dynamic array | [`dynamic_array.cpp`](./Algorithms/dynamic_array.cpp) | A templated dynamically growing array. It supports `push_back`, bounds-checked access, element replacement, clearing, status output, and bubble sort with a caller-provided comparison function. The example also measures insertion performance. |
| Binary search tree | [`Bst_tree.cpp`](./Algorithms/Bst_tree.cpp) | A templated, unbalanced binary search tree with unique keys, insertion, lookup, deletion, tree clearing, height calculation, preorder/inorder traversal, and structural output. The benchmark inserts random values and compares tree height and lookup timing for increasing input sizes. |
| Red-black tree | [`RBTree.cpp`](./Algorithms/RBTree.cpp) | A templated self-balancing binary search tree. Insertion uses recoloring and left/right rotations to preserve red-black tree properties. The example prints the tree, measures its height, and performs random lookups. |
| Binary max-heap | [`binary_heap.cpp`](./Algorithms/binary_heap.cpp) | A max-heap built on top of the custom dynamic array. It supports insertion, removing the maximum element (`poll`), displaying the internal array, and clearing the heap. The example measures insertion and removal times. |
| Kruskal minimum spanning tree | [`Kruskal_Algorithm_with_Union_find.cpp`](./Algorithms/Kruskal_Algorithm_with_Union_find.cpp) | Loads weighted graphs from text files and computes a minimum spanning forest using Kruskal's algorithm. The program compares union-find configurations with and without union by rank and path compression, reporting the MST cost, sorting time, Kruskal-loop time, and `find` statistics. |

## Algorithms and data structures

### Doubly linked list

`lista<T>` stores a pointer to both the head (`glowa`) and tail (`ogon`).
Because both ends are tracked, insertion and deletion at either end are
constant-time operations. Indexed access and replacement traverse the list from
the head and therefore take linear time.

### Dynamic array

`dynamic_array<T>` starts with capacity `2` and doubles its capacity whenever it
becomes full. This gives amortized constant-time append operations while
individual reallocations take linear time. The included bubble sort is
quadratic in the number of stored elements.

### Binary search tree

The `bst<T>` implementation stores a key, associated data, parent pointer, and
child pointers in every node. Duplicate keys are ignored. Insertion and lookup
are proportional to the tree height; because this tree is not self-balancing,
the worst case can be linear.

### Red-black tree

`RBTree<T>` maintains balancing through node colors and rotations after
insertion. It supports insertion, lookup, traversal, height calculation,
printing, and clearing. Deletion balancing is not implemented.

### Binary max-heap

`Heap<T>` stores the largest value at the root. Insertion restores the heap
property by moving the new element upward, while `poll()` moves the last
element to the root and moves it downward. These operations are logarithmic in
the number of elements.

### Kruskal's algorithm and union-find

The graph program:

1. Loads vertices and weighted edges from a file.
2. Sorts the edges by ascending cost.
3. Uses union-find to reject edges that would create a cycle.
4. Adds edges until the spanning tree contains `|V| - 1` edges.

Four union-find configurations are measured:

- no union by rank and no path compression;
- union by rank without path compression;
- path compression without union by rank;
- union by rank with path compression.

## Building and running

The programs use only the C++ standard library and can be compiled separately
with a C++17-compatible compiler such as `g++` or `clang++`.

From the repository root, for example:

```powershell
g++ -std=c++17 -O2 Algorithms\Linked_list.cpp -o Linked_list.exe
.\Linked_list.exe
```

The same pattern can be used for the other standalone sources:

```powershell
g++ -std=c++17 -O2 Algorithms\dynamic_array.cpp -o dynamic_array.exe
g++ -std=c++17 -O2 Algorithms\Bst_tree.cpp -o Bst_tree.exe
g++ -std=c++17 -O2 Algorithms\RBTree.cpp -o RBTree.exe
g++ -std=c++17 -O2 Algorithms\Kruskal_Algorithm_with_Union_find.cpp -o Kruskal.exe
```

### Binary heap dependency

`binary_heap.cpp` includes `dynamiczna.h`, but that header is not currently
present in the repository. The heap source depends on the `dynamic_array<T>`
implementation from `dynamic_array.cpp`, which is currently defined in a
separate translation unit. Before compiling the heap, provide a header
containing the dynamic array template (or move the template implementation into
a header) and update the include as needed.

### Kruskal input files

The Kruskal executable looks for `g1.txt`, `g2.txt`, and `g3.txt` in its
current working directory. These files are not included in the repository. If
an input file is missing or invalid, the program prints an error message and
continues with the remaining files.

The expected graph format is:

```text
<number of vertices>
<x_0> <y_0>
<x_1> <y_1>
...
<x_n-1> <y_n-1>
<number of edges>
<u_0> <v_0> <cost_0>
<u_1> <v_1> <cost_1>
...
```

Vertices are referenced by zero-based indices. The coordinates are loaded and
stored, but the current Kruskal computation uses the edge endpoints and costs.

## Notes

- There is no shared build system or test suite; each `.cpp` file is an
  independent laboratory exercise.
- Several example programs generate random data, so timing and lookup results
  vary between runs.
- The benchmark sizes can be changed in each file's `main()` function.
- The source files contain the original exercise-specific names and output
  messages; the README uses English descriptions for convenience.
