# `algodes`

### Algorithmic Design: coursework, homework, code (in `C`), and other goodies.

This repository contains (mainly) the coursework and homework required to access to the oral examination for the *2nd part* of the course on *Advanced Programming and Algorithmic Design* held at the University of Trieste (Spring Semester, 2020) by prof. Alberto Casagrande.  

---

#### Overview of contents:

##### [Code](https://github.com/emaballarin/algodes/tree/master/code):

-   [Strassen’s Algorithm for Matrix Multiplication](https://github.com/emaballarin/algodes/tree/master/code/strassen):
    -   Based on [this repository](https://github.com/albertocasagrande/AD_strassen_template), by Prof. Alberto Casagrande
    -   *Padding-based* version: [here](https://github.com/emaballarin/algodes/tree/master/code/strassen/strassen_with_padding)
    -   *Peeling-based* version: [here](https://github.com/emaballarin/algodes/tree/master/code/strassen/strassen_with_peeling)
-   [Binary Heaps in array-based representation](https://github.com/emaballarin/algodes/tree/master/code/binheaps):
    -   Based on [this repository](https://github.com/albertocasagrande/AD_bin_heaps), by Prof. Alberto Casagrande
    -   *Swap-on-data* version: [here](https://github.com/emaballarin/algodes/tree/master/code/binheaps/binheaps_swapping)
    -   *Swap-on-index* version: [here](https://github.com/emaballarin/algodes/tree/master/code/binheaps/binheaps_swapless)
-   [Sorting algorithms](https://github.com/emaballarin/algodes/tree/master/code/sorting)
    -   Based on [this repository](https://github.com/albertocasagrande/AD_sorting), by Prof. Alberto Casagrande
-   [Edsger Dijkstra’s algorithm for SSSP problem](https://github.com/emaballarin/algodes/tree/master/code/dijkstra)

##### [Solved exercises](https://github.com/emaballarin/algodes/tree/master/sheets):

-   [On matrix multiplication and Strassen’s algorithm](https://github.com/emaballarin/algodes/blob/master/sheets/02_matmul_01/solutions.pdf)
-   On binary heaps: [part 1](https://github.com/emaballarin/algodes/blob/master/sheets/04_heaps_01/solutions.pdf) and [part 2](https://github.com/emaballarin/algodes/blob/master/sheets/04_heaps_02/solutions.pdf)
-   On sorting: [part 1](https://github.com/emaballarin/algodes/blob/master/sheets/05_sorting_01/solutions.pdf) and [part 2](https://github.com/emaballarin/algodes/blob/master/sheets/05_sorting_02/solutions.pdf)
-   [On weighted graphs and Dijkstra’s algorithm](https://github.com/emaballarin/algodes/blob/master/sheets/06_dijkstra_01/solutions.pdf)

---

How to compile the code:

The minimal setup requirements in order to successfully compile the code are:

-   A working `C` compiler (tested with: `gcc (GCC) 10.1.0`)
-   A working `make` binary and required libraries (tested with: `GNU Make 4.3`, for target: `x86_64-pc-linux-gnu`)
-   A working `cmake` setup (tested with: `cmake version 3.17.3`)

Inside a specific project directory (e.g. by following the ***code*** links above):

```bash
cmake -G "Unix Makefiles" CMakeLists.txt
make	# optionally: make -j<number of processes>
```

or just by using provided `build.sh` script.