# Linked Lists — Algorithms and Data Structures

Three small, self-contained C programs exploring different flavors of
linked lists, developed as part of an Algorithms and Data Structures
course. Each exercise lives in its own directory with its own
`include/`, `src/`, `tests/` and `Makefile`.

| Exercise | Structure | Description |
|---|---|---|
| [`exercise-1-student-list`](exercise-1-student-list) | Singly linked list, insert-at-head | Student registry with grade filters (failed / passed / needs exam) |
| [`exercise-2-generic-list`](exercise-2-generic-list) | Singly linked list, first/last tracked | Generic list (`Element` abstraction) with insertion/removal at both ends and at arbitrary positions |
| [`exercise-3-sorted-list`](exercise-3-sorted-list) | Doubly linked, circular, sentinel-based | Student registry kept sorted by registration number (RA) |

## Requirements

- GCC (or any C11-compliant compiler)
- GNU Make
- (optional) AddressSanitizer / UndefinedBehaviorSanitizer support in the compiler, used by `make test`

## Compilation and execution

Each exercise is built independently:

```bash
cd exercise-1-student-list
make          # builds the ./student_list demo binary
./student_list
make test     # builds and runs the assert-based test suite (with ASan/UBSan)
make clean    # removes build artifacts
```

The same `make` / `make test` / `make clean` targets exist in
`exercise-2-generic-list` (binary: `linked_list`) and
`exercise-3-sorted-list` (binary: `sorted_list`).

All three compile cleanly with:

```
-Wall -Wextra -Wpedantic -std=c11
```

## Notes on file recovery

Two source files were missing or corrupted in the original project
snapshot and had to be reconstructed before this cleanup could proceed.
This is documented in detail in each exercise's section below and
should be verified by the author:

- `exercise-1-student-list/include/student_list.h` was an empty file. It
  was reconstructed strictly from how its functions are called in
  `student_list.c` and `main.c`.
- `exercise-2-generic-list/src/element.c` and `element.h` did not
  contain C source; they contained a saved GitHub web page (apparently
  from "Save Page As" on the file's GitHub view instead of downloading
  the raw file). The actual source was recovered from data embedded in
  that saved page and confirmed to compile and behave correctly.

## Author

Rodrigo Antonio Gustinelli Secundo — Computer Science student at UFABC — [GitHub](https://github.com/rgustinelli)

---

# Exercise 1 — Student List (singly linked, insert-at-head)

### Description

A singly linked list of `Student` records (registration number, name,
grade). New students are inserted at the head. The list supports
lookup by registration number, applying a flat grade adjustment to
every student, computing the class average, and building three
derived lists based on grade thresholds.

### Features

- Insert at head / insert after a given number of hops from the head
- Lookup by position or by registration number (RA)
- Bulk grade adjustment (`list_increment_grades`)
- Average grade calculation
- Three grade-based filters: `list_filter_failed`, `list_filter_passed`, `list_filter_exam`

### Grading scheme implemented

| Filter | Condition |
|---|---|
| Failed | `grade < 6.0` |
| Passed | `grade >= 6.0` |
| Needs exam | `4.0 <= grade < 6.0` |

Note that "Failed" and "Needs exam" intentionally overlap: a student
with a grade between 4.0 and 6.0 shows up in both lists. This matches
the reference program's behavior and was preserved as-is.

### Complexity

Let *n* be the number of students in the list.

| Operation | Time Complexity | Notes |
|---|---|---|
| `list_insert_first` | O(1) | |
| `list_insert_after` | O(n) worst case | walks up to `position` hops from the head |
| `list_get` | O(n) worst case | |
| `list_find_by_ra` | O(n) | linear search |
| `list_increment_grades` | O(n) | |
| `list_average_grade` | O(n) | |
| `list_filter_failed` / `_passed` / `_exam` | O(n) | one pass, allocates a new list |
| `list_destroy` | O(n) | |

Space complexity is O(n) for the list itself; each filter allocates an
additional O(k) list, where *k* is the number of matching students.

### Project structure

```
exercise-1-student-list/
├── Makefile
├── include/
│   ├── student.h
│   └── student_list.h
├── src/
│   ├── student.c
│   ├── student_list.c
│   └── main.c
└── tests/
    └── test_student_list.c
```

### Tests

`tests/test_student_list.c` covers: an empty list, single-element
list, insertion at the head and after a given position (including an
out-of-range position), lookup by RA (found/not found), bulk grade
increments and average calculation, and the three grade filters
(including the boundary values 4.0 and 6.0).

### Example

```
$ ./student_list
101. Alice: 1.00 -> 789. Peter: 6.00 -> 456. Mary: 3.00 -> 123. John: 7.00
Student found: Mary
Student not found
101. Alice: 2.00 -> 789. Peter: 7.00 -> 456. Mary: 4.00 -> 123. John: 8.00
Average grade: 5.25
Failed students:
456. Mary: 4.00 -> 101. Alice: 2.00
Passed students:
123. John: 8.00 -> 789. Peter: 7.00
Students that need to take the exam:
456. Mary: 4.00
```

---

# Exercise 2 — Generic Linked List

### Description

A singly linked list of `Element` values (currently `int`, isolated
behind `element.h`/`element.c` so the stored type can be swapped
without touching the list logic). The list tracks both its head and
tail pointers plus a running size counter, which keeps `list_size` and
tail insertion at O(1).

### Features

- Insertion at the head, tail, or an arbitrary position
- Removal from the head, tail, or an arbitrary position
- Bounds-checked access (`list_get_at`, `list_get_first`, `list_get_last`)
- Errors reported to `stderr` on invalid positions or operations on an empty list, returning a sentinel `element_null()` value instead of crashing

### Complexity

Let *n* be the number of elements in the list.

| Operation | Time Complexity | Notes |
|---|---|---|
| `list_insert_first` | O(1) | |
| `list_insert_last` | O(1) | tail pointer is tracked |
| `list_insert_at` | O(n) worst case | |
| `list_get_first` / `list_get_last` | O(1) | |
| `list_get_at` | O(n) worst case | |
| `list_remove_first` | O(1) | |
| `list_remove_last` | O(n) | singly linked: must walk to find the new tail |
| `list_remove_at` | O(n) worst case | |
| `list_size` / `list_is_empty` | O(1) | size is tracked incrementally |
| `list_destroy` | O(n) | |

Space complexity is O(n).

### Project structure

```
exercise-2-generic-list/
├── Makefile
├── include/
│   ├── element.h
│   └── linked_list.h
├── src/
│   ├── element.c
│   ├── linked_list.c
│   └── main.c
└── tests/
    └── test_linked_list.c
```

### Tests

`tests/test_linked_list.c` covers: an empty list, single-element list
(insert then remove down to empty), tail insertion with lookups,
head/positional insertion (including tail-position update),
out-of-range insert/get positions, removal from head/tail/middle,
removing from an empty list (must not crash), and duplicate values.

### Example

```
$ ./linked_list
Inserting elements: 10, 20, 30, 40, 50
List after insertions: 10 -> 20 -> 30 -> 40 -> 50
List size: 5
Is empty: false

Getting element at position 2: 30

Inserting 25 at position 2:
List after insert_at: 10 -> 20 -> 25 -> 30 -> 40 -> 50
...
Final list size: 4
```

---

# Exercise 3 — Sorted List (doubly linked, circular, sentinel-based)

### Description

A doubly linked, circular list with a sentinel node, keeping `Student`
records sorted by ascending registration number (RA) at all times.
Duplicate RAs are rejected on insertion. Because the list is doubly
linked, `slist_get_at` traverses from whichever end (head or tail) is
closer to the requested position.

### Features

- Sorted insertion with duplicate-RA rejection
- Removal, lookup, and grade update by RA
- O(min(pos, n − pos)) positional access thanks to the doubly linked structure
- Sentinel node removes special-casing for head/tail insertion and removal

### Complexity

Let *n* be the number of students in the list.

| Operation | Time Complexity | Notes |
|---|---|---|
| `slist_insert` | O(n) | linear scan to find the sorted insertion point |
| `slist_remove` | O(n) | linear scan by RA |
| `slist_find` | O(n) | linear scan by RA |
| `slist_update_grade` | O(n) | linear scan by RA |
| `slist_get_at` | O(min(pos, n − pos)) | walks from the closer end |
| `slist_get_min` / `slist_get_max` | O(1) | sentinel's neighbors |
| `slist_size` / `slist_is_empty` | O(1) | |
| `slist_destroy` | O(n) | |

Space complexity is O(n).

### Project structure

```
exercise-3-sorted-list/
├── Makefile
├── include/
│   ├── student.h
│   └── sorted_list.h
├── src/
│   ├── student.c
│   ├── sorted_list.c
│   └── main.c
└── tests/
    └── test_sorted_list.c
```

### Tests

`tests/test_sorted_list.c` covers: an empty list, single-element list,
insertion in non-sorted order (verifying the resulting order),
duplicate RA rejection, find/update by RA (found and not found),
removal of the head, the tail, a non-existent RA, and the last
remaining element, and positional access at both extremes (exercising
both traversal directions of `slist_get_at`).

### Example

```
$ ./sorted_list
123. Alice: 9.50 -> 456. Bob: 7.00 -> 789. Charlie: 8.00
```
