# `FASTMAP`
### `FA`st `ST`rassen with `M`inimal `A`dditional `P`adding

This repository contains the implementation of a variant of the original Strassen Matrix Multiplication Algorithm (note: not the Strassen-Winograd version) in order to deal with square-odd and general rectangular matrices.  

The approach adopted to generalize the algorithm involves matrix padding, while keeping it at the required minimum for the class of matrix-embedding Strassen Algorithm generalizations. Other ways to tackle the same problem may involve matrix cutting or partial-overlap square matrix multiplication.  

More specifically, our implementation choice builds upon the sliding-square blockwise matrix multiplication approach, and further reframes the algorithm in order to achieve a decreased memory footprint. Lastly, some plaform-specific optimizations are introduced.  

The code shipped together with this `README.md` is part of the coursework/homework required for the Algorithmic Design final examination (Spring 2020, University of Trieste) and is based on the [baselines](../../baselines/) provided by Prof. Alberto Casagrande. The original readme for the baseline code can be found [here](./ORIGINAL_README.md).  

The differences and improvements with regard to the [baseline version](../../baselines/strassen) is summarized [here](./DIFF.md).
