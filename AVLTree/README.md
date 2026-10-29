# AVL Tree in C

A self-balancing binary search tree (AVL tree) implemented in C, supporting
insertion, deletion, search, and the three classic tree traversals.

## Description

This project implements an **AVL tree**, a height-balanced binary search
tree that guarantees `O(log n)` time complexity for search, insertion, and
removal by automatically rebalancing itself through rotations after every
modification.

The stored value type (`Element`) is isolated behind a small abstraction
(`element.h` / `element.c`), so the underlying type — currently `int` — can
be changed by editing a single file, without touching the AVL logic itself.

This project was developed as an academic exercise in Algorithms and Data
Structures.

## Features

- Insertion with automatic rebalancing (LL, RR, LR, RL rotation cases)
- Removal with automatic rebalancing, covering leaf nodes, nodes with one
  child, nodes with two children, and removal of the root
- Search by key
- In-order, pre-order, and post-order traversals
- Full tree destruction with proper memory cleanup
- Automated test suite covering edge cases (empty tree, single element,
  duplicates, extreme values, and every removal case)

## Algorithm / Data Structure

**AVL Tree** — for every node, the heights of its left and right subtrees
differ by at most 1 (the *balance factor* is in `{-1, 0, 1}`). Whenever an
insertion or removal breaks this invariant, one of four rotations restores
it:

- **Left-Left (LL):** single right rotation
- **Right-Right (RR):** single left rotation
- **Left-Right (LR):** left rotation on the left child, then right rotation
- **Right-Left (RL):** right rotation on the right child, then left rotation

Because the invariant is restored after every single insertion or removal,
the tree height is always `O(log n)`, which is what keeps every operation
logarithmic.

## Complexity

Since the AVL invariant guarantees `O(log n)` height at all times, these
operations have the same time complexity in the best, average, and worst
case:

| Operation | Time Complexity | Space Complexity (auxiliary) |
|---|---|---|
| Search | O(log n) | O(log n) — recursion stack |
| Insert | O(log n) | O(log n) — recursion stack |
| Remove | O(log n) | O(log n) — recursion stack |
| Traversal (in/pre/post-order) | O(n) | O(log n) — recursion stack |
| Destroy | O(n) | O(log n) — recursion stack |

The recursion stack depth for search/insert/remove/traversal/destroy is
bounded by the tree height, which AVL guarantees to be `O(log n)` for `n`
nodes — this is the core property that distinguishes an AVL tree from an
unbalanced binary search tree, where these operations can degrade to
`O(n)` on already-sorted input.

## Project structure

```
AVLTree/
├── README.md
├── Makefile
├── .gitignore
├── include/
│   ├── avl.h          # Public interface of the AVL tree
│   └── element.h       # Definition of the stored element type
├── src/
│   ├── avl.c          # AVL tree implementation
│   └── element.c       # Element comparison/printing
├── examples/
│   └── example_1.c    # Usage demo (insert, search, remove, traversals)
└── tests/
    └── test_avl.c      # Automated tests (assert-based)
```

## Requirements

- A C compiler supporting C11 (e.g. GCC or Clang)
- `make`

No external libraries are required.

## Compilation and execution

Build and run the usage demo:

```bash
make
./build/avl_demo
```

Clean build artifacts:

```bash
make clean
```

## Tests

The test suite uses plain `assert()` checks (no external framework) and
covers:

- an empty tree (search and remove on it)
- a single-element tree
- inserting a duplicate key (must not create a new node)
- inserting values in increasing order (the case that forces the most
  rotations) and confirming the tree stays balanced
- removing a leaf, a node with one child, and the root (which has two
  children), confirming the tree stays balanced after each
- removing a key that does not exist (must be a no-op)
- extreme values (very large and very small integers)

Run them with:

```bash
make test
```

## Example

Running `./build/avl_demo` after inserting `30, 20, 10, 25, 40, 50, 60, 5`
produces:

```
=== AVL INSERT TEST ===

Inorder traversal:
5 10 20 25 30 40 50 60

Preorder traversal:
30 20 10 5 25 50 40 60

Postorder traversal:
5 10 25 20 40 60 50 30

=== AVL SEARCH TEST ===
Key 25 found
Key 100 not found

=== AVL REMOVE TEST ===

Removing leaf node (5):
10 20 25 30 40 50 60

Removing node with one child (60):
10 20 25 30 40 50

Removing node with two children (30):
10 20 25 40 50

Final preorder:
40 20 10 25 50

=== AVL DESTROY TEST ===
Tree destroyed successfully
```

## Author

Rodrigo Antonio Gustinelli Secundo — Computer Science student at UFABC — [GitHub](https://github.com/rgustinelli)

