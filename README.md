# Frugal Sort

**Frugal Sort** is an intentionally inefficient sorting algorithm designed to perform sorting operations using opportunistically available computing resources.

Unlike traditional sorting algorithms that prioritize execution speed, Frugal Sort prioritizes minimizing interference with other running processes.

## How It Works

Frugal Sort combines **Bozo Sort** with low-priority operating-system scheduling.

1. Accept an array of numbers, characters, or strings.
2. Check whether the array is sorted.
3. If unsorted, randomly select two elements and swap them.
4. Repeat until the array becomes sorted.

The program requests low scheduling priority using `SCHED_IDLE` on Linux or `setpriority()` on macOS, allowing higher-priority processes to receive preferential CPU scheduling.

## Compilation and Execution

```bash
gcc -O2 -Wall -Wextra frugal_sort.c -o frugal_sort
./frugal_sort
```

## Example

```text
Enter number of elements: 5
Enter 5 elements:
5 3 1 4 2

Random swaps: 124
Sorted: 1 2 3 4 5
```

The number of swaps varies between executions.

## Complexity

| Property | Complexity |
|---|---|
| Expected sorting time | Extremely inefficient; depends on random swaps |
| Worst-case time | Unbounded |
| Sortedness check | O(n) |
| Auxiliary sorting space | O(1) |
| Termination | Probabilistic, assuming continued execution |

## Limitations

- Sorting may require an extremely large number of random swaps.
- Low-priority scheduling does not guarantee zero CPU consumption.
- The current implementation does not directly reuse fragmented or garbage memory.
- Completion time depends on both randomness and operating-system scheduling.

## Future Work

- Detect idle CPU capacity using Linux kernel interfaces.
- Investigate cooperative reuse of reclaimable memory.
- Suspend sorting under resource pressure.
- Measure foreground-process interference and CPU utilization.

## Motivation

**Why spend dedicated computing resources sorting efficiently when you can sort inefficiently using whatever resources the operating system happens to spare?**

Frugal Sort is an experimental exploration of randomized sorting and opportunistic resource scheduling, rather than a practical replacement for conventional sorting algorithms.