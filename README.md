## Maximum clique finding and vertex color library

### This library supports maximum clique finding, minimum clique partitioning (aka minimum vertex coloring) for undirected graph.

#### 1. Prerequisite
g++ 4.8.2 or later.

#### 2. Directory structure
** 1. src/: **
   Contains source files for three classes: **Graph**, **Clique**, **VertexColor**.

** 2. test/: **
   Contains a simple test program (`test.cpp`) for Clique and VertexColor. 
   
   test.cpp can be considered as a sample program

** 3. target/: **
   The static library (`libngclique.a`) file will be put here after a successful 'make'.
   
**4. Makefile **

#### 3. How to build
** Build static library **

   `make`

** 4. Build test **

   `make test`

   `bin/test`

#### How to use
Assume that you are developing your own project, and you want to use this library.
Also, all your source code is put in `src/`.

* Put `Graph.*`, `Clique.*`, and `VertexColor.*` in your `headers/` directory.
* Put `libngclique.a` in your `lib/` directory.
* Refer to `test.cpp` to see how to use this library. Basically, everything is under `ngclique` namespace.
* Compile:

  `g++ -static your_program.cpp' -L /lib/ -l ngclique -o your_executable_file`
