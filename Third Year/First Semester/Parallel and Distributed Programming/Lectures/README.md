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


## Lecture 4 - Higher level multithreading concepts

### Thread creation issues
* creating many threads had two issues:
    * creating and switching between threads is expensive
    * there is an OS-dependent upper limit on the number of threads

### Thread pools
* we precreate a number of threads which are waiting (on a conditional variable, so that the OS doesn't give them any CPU time yet)
* when some work comes in, we give it to a free thread
* when the work is done, the thread returns to the waiting state (don't destroy the thread)
* when work comes in, but all threads are busy, there are a few possibilities:
    * temporarily increase the number of threads (therefore, you risk reaching the OS limit)
    * just block waiting for a thread to finish its work (therefore, you risk having deadlocks)

### Futures and promises
* promise
* future
* set a continuation on a future


## Lecture 5 - Futures with continuations

* async/await mechanism
