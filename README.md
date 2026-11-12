# Frugal Sort

Frugal Sort is a deliberately inefficient sorting algorithm that tries to use leftover computing resources instead of competing with other running processes.

The idea is simple. Why rush to sort an array when the computer has other things to do?

### How it works

Frugal Sort currently uses random swaps, similar to Bozo Sort. It picks two elements, swaps them, and repeats until the array is sorted.

It also requests a low scheduling priority so other processes get preference.

### Run

```bash
gcc frugal_sort.c
./a.out
```

### Example

```text
Enter number of elements: 3
Enter 3 elements:
3 1 2

Random swaps: 8
Sorted: 1 2 3
```

The number of swaps changes every time.

### Complexity

The worst-case running time is unbounded. It might sort in a few swaps or take an absurdly long time.

### Current status

#### V.1
- The current version uses random swapping and low-priority scheduling. It does not yet directly use leftover or reclaimable memory.


The goal is to eventually make Frugal Sort perform its work only when the operating system has resources to spare.

**Frugal Sort is not designed to be fast. It is designed to be frugal.**
