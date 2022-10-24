# Bank Accounts Problem - Assignment 1 Documentation

## Overview
### Intro
A complete description of the task can be found [here](https://www.cs.ubbcluj.ro/~rlupsa/edu/pdp/lab-1-noncooperative-mt.html).

### Problem Statement
At a bank, we have to keep track of the balance of some accounts. Also, each account has an associated log (the list of records of operations performed on that account). Each operation record shall have a unique serial number, that is incremented for each operation performed in the bank.

We have concurrently run transfer operations, to be executer on multiple threads. Each operation transfers a given amount of money from one account to someother account, and also appends the information about the transfer to the logs of both accounts.

From time to time, as well as at the end of the program, a consistency check shall be executed. It shall verify that the amount of money in each account corresponds with the operations records associated to that account, and also that all operations on each account appear also in the logs of the source or destination of the transfer.

Two transaction involving distinct accounts must be able to proceed independently (without having to wait for the same mutex).

## Implementation
### Input Parameters/Data
- ```number of threads``` - given as a command line argument
- file ```Files/accounts.txt``` - contains the accounts that are registered in the bank, together with the initial sum in each one of them

### Randomly Generated Data
- each thread executes a random number of transfers
- at each operation, a consistency check occurs, with a given probability

### Invariants
- the amount of money in each account corresponds with the operations records associated to that account
- all operations on each account appear also in the logs of the source or destination of the transfer

### Mutexes
- each account has its own mutex, which guards it during a transfer involving it
- the rule is that the mutexes must be locked always according to a given order (i.e., the ID of the accounts being involved in the transaction), so that deadlocks are avoided
- moreover, the way the mutexes are used make sure that the amount of money in each account correspond to its logs, at all times

## Experiments
- 50 threads, with an average of 50 operations/thread - running time was ```8406us```
- 100 threads, with an average of 50 operations/thread - running time was ```13577us```
- 1000 threads, with an average of 50 operations/thread - running time was ```259329us```
