# PPD Lectures Summary


## Lecture 1 - Intro

* **concurrent** (tasks executed in overlapping time periods) vs **parallel **(simultaneous execution, multi-core processor) vs **distributed** (spatial distribution, implies parallelism)
* Classification
    * **Flynn taxonomy**
        * SISD = single instruction, single data
        * SIMD = single instruction, multiple data
        * MISD = multiple instructions, single data
        * MIMD = multiple instructions, multiple data
    * **Shared memory**
        * SMP = symmetric multi-processing
            * identical processors (cores) accessing the same main memory
        * AMP = asymmetric multi-processing
            * like SMP, but processors have different capabilities (e.g., only one can request I/O)
        * NUMA = non-uniform memory access
            * each processor has a local memory, but it can also access a main memory and/or the local memory of the other processors


## Lecture 2 - Handling concurrency

[TODO]


## Lecture 3 - More concurrency issues

[TODO]
