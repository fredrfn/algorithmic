# Data structures / Algorithmic practice

This repo contains some custom implementations of standard data structures and algorithms in several languages.
The purpose of this repo is to showcase how a developer could go about implementing its own standard library. All the classes included are tested comprehensively.
It is not meant to replace the C++ STL Library or any other framework, even though it is heavily inspired by it.

## Data structures (in progress)

- Array (fixed size)
- Vector (dynamically sized array)
- Linked list
- Stack
- Queue
- Tree and Binary tree
- Heap
- Graph
- Complex number
- Hash table (Map)

## Showcased algorithms (in progress)

- Sorting algorithms (insertion, selection, bubble, mergesort, quicksort, heapsort, introsort)
- Search algorithms (linear, dichotomic/binary, DFS/BFS)
- Shortest distances algorithms (Dijkstra, A*, Bellman Ford)
- Fermat Primality Test
- KMP Algorithm (String matching)
- FFT (unoptimized Cooley-Tukey algorithm)

## Compilation / execution / use

### C++ 

Tested with g++ compiler and CMake. 

```sh
cd repo
mkdir build
cd build
cmake ..
make
./Algorithmic
```

This will execute a set of tests - ensuring the classes are valid and showcasing how to use them. It uses the Catch2 testing framework.

Feel free to copy paste, extend and include any of the .hpp files inside your projects, even though the STL makes a much safer work, portable and battle-tested. They also include latest features of C++, with the right usage of semantics (move in particular), and come with a lot more utilities functions.

### Typescript

Work in progress, stay tuned for updates.
Will contain the same contents than the C++ counterpart

## License

MIT

