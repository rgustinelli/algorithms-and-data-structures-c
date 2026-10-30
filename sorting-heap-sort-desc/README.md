# Sorting Algorithms in C

A collection of sorting algorithm implementations in C, built as part
of an Algorithms and Data Structures microproject series. Each
algorithm lives in its own folder and operates on a shared `Element`
type.

Currently implemented:

- **`heap-sort-desc`** — heap sort that produces a descending order.

Planned / pending:

- **`insertion-sort`** — not yet implemented in this repository.

## Description

All algorithms in this project sort an array of `Element`, a small
struct shared across the different sorting implementations:

```c
typedef struct {
    int key;
    char name[ELEMENT_NAME_MAX];
} Element;
```

`key` is the value used for ordering; `name` is a label slot that
other producers of `Element` arrays may populate. In this project, the
only source of input is a plain array of integer keys, so `name` is
always left as an empty string (there is no name data to derive it
from) — see `element_make_array` in `src/shared/element.c`.

### heap-sort-desc

Heap sort is a comparison-based sorting algorithm that uses a binary
heap to repeatedly select an extreme element and move it to its final
position. The classic textbook version builds a **max-heap** to
produce an array in **ascending** order.

This implementation instead builds a **min-heap**: at each step, the
element with the smallest key is moved to the root and then swapped to
the end of the unsorted region. The end result is an array sorted in
**descending order** (largest key first). This is a deliberate
variation of the standard algorithm, not the conventional ascending
heap sort.

An optional callback (`on_step`) can be passed to `heap_sort` to
observe the array state after each element is placed in its final
position — useful for visualizing or logging the sorting process
without modifying the core algorithm.

## Features

- Shared `Element` type (`key` + `name`) reused across sorting
  algorithms in this project.
- In-place sorting of an `Element` array.
- `heap-sort-desc`: descending-order result via a min-heap.
- Optional step callback for observing intermediate states.
- Assert-based automated tests covering normal and edge cases.

## Algorithm: heap sort (min-heap variant, descending order)

1. Build a min-heap from the input array (`heapify` on every non-leaf
   node, from the last one up to the root).
2. Repeatedly swap the root (the element with the current minimum key)
   with the last element of the unsorted region, shrink the heap by
   one, and restore the heap property with `heapify`.
3. After all extractions, the array is sorted from the largest key to
   the smallest.

`heapify` is implemented recursively.

## Complexity (heap-sort-desc)

| Operation                  | Best case   | Average case | Worst case  |
|-----------------------------|-------------|---------------|-------------|
| Build heap                  | O(n)        | O(n)          | O(n)        |
| Full sort (`heap_sort`)     | O(n log n)  | O(n log n)    | O(n log n)  |

Unlike algorithms such as insertion sort, heap sort has **no linear
best case**: even on an already-sorted input, every extraction still
requires an O(log n) sift-down, so the total remains O(n log n) in
every case.

**Space complexity:** O(log n) auxiliary space. The sort is in-place
(no extra array is allocated), but `heapify` is implemented
recursively, so the call stack grows with the height of the heap,
which is O(log n). A fully iterative `heapify` would bring this down
to O(1) auxiliary space; that rewrite was not applied here in order to
preserve the original recursive implementation.

## Project structure

```
sorting/
├── README.md
├── Makefile
├── .gitignore
├── src/
│   ├── shared/
│   │   ├── element.h         # Element type shared by all algorithms
│   │   └── element.c
│   ├── heap-sort-desc/
│   │   ├── heap_sort.h       # Public interface and documentation
│   │   ├── heap_sort.c       # heap_sort and static heapify
│   │   └── main.c            # Usage example / demo
│   └── insertion-sort/       # Pending: not yet implemented
└── tests/
    └── test_heap_sort.c      # Assert-based test suite for heap sort
```

## Requirements

- A C compiler supporting C11 (developed and tested with `gcc`).
- `make` (optional, but recommended).

## Compilation and execution

Using the provided Makefile:

```bash
make        # builds the demo executable: heap_sort_demo
./heap_sort_demo
```

Manually, without `make`:

```bash
gcc -Wall -Wextra -Wpedantic -std=c11 -Isrc/heap-sort-desc \
    -o heap_sort_demo src/heap-sort-desc/main.c src/heap-sort-desc/heap_sort.c src/shared/element.c
./heap_sort_demo
```

The project compiles cleanly with `-Wall -Wextra -Wpedantic -std=c11`,
with no warnings.

## Tests

Run the automated test suite with:

```bash
make test
```

This compiles `tests/test_heap_sort.c` against `heap_sort.c` and
`element.c` and runs it. The suite checks:

- a typical unordered array;
- an empty array (`size == 0`);
- a single-element array;
- an array with duplicate keys;
- an array already in the target descending order;
- an ascending (reverse) input, which is the worst case for this
  algorithm since every element must move through the heap;
- negative numbers and extreme values.

## Example

```
Original array: [61, 73, 82, 28, 33, 57, 4, 15]
Sorted array (descending): [82, 73, 61, 57, 33, 28, 15, 4]
```

## Author

Rodrigo Antonio Gustinelli Secundo — Computer Science student at UFABC — [GitHub](https://github.com/rgustinelli)
