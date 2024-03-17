# Assignment 1
## Team Members
K201677 Umer 

## Major Problems Encountered

1. ### Issue 1: Performance Discrepancy in sequential_mXv Program
    - Solution1: Analyze the code for potential bottlenecks or inefficiencies.
    - Solution2: Profile the code to identify areas for optimization.
    - Resolved: Resolved by identifying and optimizing performance-critical sections of the code, resulting in improved execution times.

2. ### Issue 2: Performance Variation in openmp_mXv Program
    - Solution1: Check for load imbalances among threads in the OpenMP parallelization.
    - Solution2: Optimize thread synchronization to reduce overhead.
    - Resolved: Addressed by optimizing thread management and load distribution, leading to more consistent performance across different input sizes.

3. ### Issue 3: Inconsistent Performance in mpi_mXv Program
    - Solution1: Investigate communication overhead and latency in MPI message passing.
    - Solution2: Optimize MPI data distribution and message sizes.
    - Resolved: Mitigated by fine-tuning MPI message passing and optimizing communication patterns, resulting in more stable performance across different input sizes.

4. ### Issue 4: Performance Fluctuations in openmp_tiled_mXv Program
    - Solution1: Review the tile size and data partitioning strategy for better cache utilization.
    - Solution2: Optimize loop structures and memory access patterns for improved parallel efficiency.
    - Resolved: Addressed by adjusting the tile size and optimizing data partitioning strategies, leading to smoother performance across different input sizes.

5. ### Issue 5: High Execution Times in mpi_tiled_mXv Program
    - Solution1: Investigate potential inefficiencies in MPI-based tiled matrix-vector multiplication.
    - Solution2: Optimize data distribution and parallelization strategies for better scalability.
    - Resolved: Partially mitigated through optimizations, but further investigation required to fully resolve the high execution times observed, possibly indicating deeper architectural or algorithmic issues.
