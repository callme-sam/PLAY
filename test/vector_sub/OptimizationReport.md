# **Performance Analysis of the `vector_sub` Test on the PULP Cluster**

This report provides a comprehensive analysis of the `vector_sub` operation's performance on a PULP Cluster. It evaluates the impact of different loop constructs (`for` and `while`) and optimization techniques (loop unrolling, interleaved access and their combination, data reuse, index pre-computation, accumulation, for loop VS while loops), based on both performance metrics and insights from the generated assembly code.

---

## **Single-Core Execution**

The primary performance bottleneck in single-core execution is identified as **load stalls**, which are pipeline delays caused by data dependencies (`read-after-write` hazards).

* **Standard Loops (`for` and `do-while`):** The standard implementations of both `for` and `do-while` loops show similar performance, characterized by a high cycle count (~10,278) and a low IPC (~0.8). This is directly attributed to a significant number of load stalls (~2,050). *The performance is not affected by how source vectors (`src_X`) or indices are loaded.*
* **Loop Interleaving:** This optimization, when applied in isolation, does not mitigate the load stall issue (as expected). Performance metrics remain comparable to the standard loops, confirming that the primary limitation is not a memory access pattern problem.
* **Loop Unrolling:** **Unrolling is the most effective optimization for single-core performance.** It drastically reduces the number of load stalls to a minimal count (2 or 3), leading to a 20% reduction in total cycles and a near-perfect IPC (~0.998). This is achieved by processing multiple elements per loop iteration, allowing the compiler to schedule memory loads and computations more efficiently, thereby hiding memory latency. The best performances are obtained with a **step-2** unroll.
* **The "Both" (`unroll` + `interleave`) Option:** This configuration yields performance results that are virtually identical to the `unroll` version alone. This demonstrates that unrolling is the dominant optimization, and interleaving provides no additional benefit in this single-core context.
* **Assembly-Level Nuance:** The "first version" of unrolled `do-while` loop has approximately 1,000 more instructions than the `for` counterpart. This is because the compiler cannot use hardware loops with a step size of 2, a limitation overcome by refactoring the `do-while` loop to a `do-while` with a step of 1, which then makes its performance equivalent to the `for` loop.

---

### **Multi-Core (8-Core) Execution**

On the 8-core cluster, the benefits of unrolling continue to be the main factor driving performance improvements.

* **Standard Loops (`for` and `do-while`):** Both standard loops demonstrate effective parallelization, achieving a speedup of roughly 7.9. However, the presence of TDCM (Tightly-Coupled Data Memory) contentions indicates potential resource conflicts between cores.
* **Unrolling:** The unrolled versions consistently record the lowest cycle counts per core (~1,070), indicating the fastest execution time for the assigned workload. While their speedup (7.72 for `for_unroll`) is slightly lower than the standard loops, the reduced cycle count per core ensures superior overall execution speed. Assembly analysis shows a minor overhead of approximately 18 extra instructions for thread-specific calculations.
* **Interleaving and "Both":** Interleaving alone provides no significant performance improvement. The `both` version performs on par with the `unroll` version, confirming that while it eliminates TDCM contentions, the performance gains from unrolling are the most significant and the contentions are not a primary bottleneck.

---

### **Conclusion**

The most critical optimization identified across all test cases is **loop unrolling**. It successfully addresses the primary performance bottleneck of load stalls, resulting in the most significant performance improvements for both single-core and multi-core executions. The choice between a `for` and `do-while` loop has a minimal impact on final performance, provided *one-step loops*. The interleaving optimization, both alone and in combination with unrolling, offers no sensible performance advantage and its benefits are negligible compared to the effectiveness of unrolling. (Note that the number of TCDM contentions was negligible in the first place)
