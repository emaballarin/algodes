# `FASTMAP`
### `FA`st `ST`rassen with `M`inimal `A`dditional `P`adding
#### Differences w.r.t. the baseline

- Reformat code with a Microsoft-based `ClangFormat` style;
- Update and refine `Cmake` release flagging: `-O3 -flto -march=native`;
- Tune stopping criterion for baseline Strassen: `side <= 64`;

- Implement rectangular matrix naive multiplication;
- Implement a `calloc`-based matrix allocator;
- Implement a `calloc`-based matrix padder;

- Implement an *allocate padded* matrix routine;
- Implement an *assign un-padded* matrix routine;

- Extend `strassen_aux` to handle square-odd matrices;

- Implement a memory-constrained version of `strassen_aux`;
- Implement a memory-optimized version of `strassen_aux`;

- Implement a matrix multiplication routine that hadles rectangular matrices multiplication for each of the `strassen_aux` versions.
