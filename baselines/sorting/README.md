# DSSC - Algorithmic Design - Sorting Algorithms
This repository contains some code to simplify the implementation and testing of sorting algorithms. The code in this repository natively support insertion sort, quick sort (with and without the select algorithm to identify the pivot), bubble sort, selection sort, and heap sort, but other algorithms can easily be added by editing the main function in the file [main.c](src/main.c).

In order to test the differences in term of execution-time between the sorting algorithms, you need to implement all of them. The insertion sort algorithm must be implemented in the file [insertion_sort.c](src/insertion_sort.c) according to the API defined in [insertion_sort.h](src/insertion_sort.h); the quick sort algorithm in the file [quick_sort.c](src/quick_sort.c) and, so forward, for all the algorithms.


A Makefile can be produced by using [cmake](https://cmake.org/) as follows:
```bash
cmake -G "Unix Makefiles" CMakeLists.txt
```
If you have implemented the [`binheap` library](https://github.com/albertocasagrande/AD_bin_heaps), you can use it to code heap sort by using the command:
```bash
cmake -G "Unix Makefiles" -DBINHEAP_PATH=<BINHEAP_INSTALL_DIR> CMakeLists.txt
```
See [here](https://github.com/albertocasagrande/AD_bin_heaps) to have more details about `<BINHEAP_INSTALL_DIR>`.

Afterwards you can compile the code by executing `make`. This produces an executable named `test_sorting` which can be executed in POSIX systems by using the command:
```bash
./test_sorting
Size	Insertion Sort	          	        
    	(Random Case)	(Best Case)	(Worst Case)
2^2 	0.000000 (KO)	0.000000	0.000000 (KO)
2^3	0.000000 (KO)	0.000000	0.000000 (KO)
2^4	0.000000 (KO)	0.000000	0.000000 (KO)
2^5	0.000000 (KO)	0.000000	0.000000 (KO)
2^6	0.000000 (KO)	0.000000	0.000000 (KO)
2^7	0.000000 (KO)	0.000000	0.000000 (KO)
2^8	0.000000 (KO)	0.000000	0.000000 (KO)
2^9	0.000000 (KO)	0.000000	0.000000 (KO)
2^10	0.000000 (KO)	0.000000	0.000000 (KO)
2^11	0.000000 (KO)	0.000000	0.000000 (KO)
2^12	0.000000 (KO)	0.000000	0.000000 (KO)
2^13	0.000000 (KO)	0.000000	0.000000 (KO)


Size	Quick Sort	          	Quick Sort + Select
    	(Random Case)	(Worst Case)	(Random Case)	(Worst Case)
2^2 	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^3	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^4	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^5	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^6	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^7	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^8	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^9	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^10	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^11	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^12	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000
2^13	0.000000 (KO)	0.000000	0.000000 (KO)	0.000000


Size	Insertion Sort	Quick Sort	Bubble Sort	Selection Sort	Heap Sort
    	(Random Case)	(Random Case)			
2^2 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^3 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^4 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^5 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^6 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^7 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^8 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^9 	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^10	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^11	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^12	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)
2^13	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)	0.000000 (KO)


Size	Quick Sort  	Quick Sort +	Heap Sort
			  Select
    	(Random Case)	(Random Case)
2^14	0.000001 (KO)	0.000001 (KO)	0.000000 (KO)
2^15	0.000005 (KO)	0.000005 (KO)	0.000002 (KO)
2^16	0.000004 (KO)	0.000004 (KO)	0.000000 (KO)
2^17	0.000011 (KO)	0.000011 (KO)	0.000011 (KO)
2^18	0.000030 (KO)	0.000030 (KO)	0.000013 (KO)
2^19	0.000105 (KO)	0.000105 (KO)	0.000041 (KO)
2^20	0.000110 (KO)	0.000110 (KO)	0.000075 (KO)
```

The first column in the output report the size of the tested array. The remaining columns in the output report the execution-time in seconds of the implementations of sorting algorithms. Whenever the resulting arrays are not sorted (e.g., due to a bug) the word "KO" follows the execution-time. Since the algorithms are not implemented in the repository, `test_sorting` initially reports 0 seconds for all of the algorithms and all the resulting arrays (but the best case for insertion sort and the worst case for quick sort which are already ordered) are not sorted. 

In order to better compare quick sort and heap sort on the random cases, a futher set of tests on larger arrays are also performed.
