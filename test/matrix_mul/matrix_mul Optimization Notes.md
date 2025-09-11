# Analysis of Matrix Multiplication Implementations

Performance analisys of the three implementations (for, do-while, and do-while single-step) for matrix multiplication, considering both 1-core and 8-core results.

---

## 1 Core (1C)

When using a single core, the **do-while single-step** implementation is the most efficient in terms of total cycles.

* **do-while single-step**: 447,332 cycles
* **do-while**: 459,611 cycles
* **for**: 467,930 cycles

The difference between the **`for`** and **`do-while`** implementations is minimal, but the **`do-while single-step`** shows a notable improvement, requiring about **4.4% fewer cycles** compared to the `for` implementation.

---

## 8 Cores (8C)

With 8 cores the **`for`** and **`do-while`** implementations are almost identical in terms of cycles, while the **`do-while single-step`** remains the highest-performing option.

* **do-while single-step**: 3,238 cycles
* **for**: 4,414 cycles
* **do-while**: 4,417 cycles

In this multi-core scenario, the **`do-while single-step`** is once again the fastest implementation, with about **26.6% fewer cycles** than the other two. This suggests that, while all implementations benefit from parallelism, the loop unrolling with a "single-step" approach further reduces the number of instructions and execution cycles per core, leading to superior efficiency.

---

## Conclusion

* **Best Implementation**: The **`do-while single-step`** implementation offers the best performance in both scenarios (1 core and 8 cores). This indicates that specific loop optimization has a significant impact on performance, especially when computation is distributed across multiple cores.
* **Minimal Differences (8C)**: The **`for`** and **`do-while`** implementations show a nearly negligible difference in a multi-core environment, suggesting that parallelism outweighs the minor inefficiencies between these two loop types.
