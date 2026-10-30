# BST User Database

A small in-memory user database backed by two binary search trees (BSTs),
allowing user records to be looked up efficiently by either **email** or
**id**.

## Description

This project implements a simple user record store on top of two
independent, unbalanced binary search trees:

- `BST_UInt` — keyed by the user's unsigned integer `id`.
- `BST_Str` — keyed by the user's `email` string.

Both trees store pointers to the same `User` records, so a single
`Database` instance keeps the two indexes in sync: inserting or removing a
user updates both trees at once, giving O(log n) average-case lookups by
either key without duplicating the underlying data.

This project was developed as an academic exercise in Algorithms and Data
Structures, focused on classic (unbalanced) BST operations: insertion,
search, removal (including the three standard removal cases — leaf,
one child, two children via in-order successor), and the three traversal
orders (pre-order, in-order, post-order).

## Features

- Insert, query, and remove users by `id` or by `email`.
- Three traversal orders (pre-order, in-order, post-order) for either index.
- Dual-index database that keeps both trees consistent on insert/remove.
- Node count (`size`) for either individual tree.
- Zero compiler warnings under `-Wall -Wextra -Wpedantic -std=c11`.

## Algorithms / Data Structures

| Component  | Structure                          | Ordered by |
|------------|-------------------------------------|------------|
| `bst_uint` | Unbalanced binary search tree       | `User.id`  |
| `bst_str`  | Unbalanced binary search tree       | `User.email` (lexicographic, `strcmp`) |
| `database` | Composition of the two trees above  | both       |

Neither tree performs any self-balancing (no AVL/red-black rotations), so
their performance depends directly on insertion order, as described below.

Node removal follows the standard BST algorithm:
1. **Leaf node** — simply detached and freed.
2. **One child** — the child replaces the removed node.
3. **Two children** — the node's value is replaced by its in-order
   successor (left-most node of the right subtree), and that successor is
   then removed from the right subtree.

## Complexity

Let `n` be the number of users stored and `h` the height of the relevant
tree (`h = O(log n)` for a well-balanced/random insertion order, and
`h = O(n)` in the worst case, e.g. ids or emails inserted in sorted order,
since these are plain unbalanced BSTs with no rebalancing).

| Operation                          | Best case   | Average case | Worst case | Notes |
|-------------------------------------|-------------|---------------|------------|-------|
| `insert` (single tree)             | O(1)        | O(log n)      | O(n)       | Recursive descent to an empty slot. |
| `query` (single tree)              | O(1)        | O(log n)      | O(n)       | Recursive descent, stops at first match. |
| `remove` (single tree)             | O(1)        | O(log n)      | O(n)       | Descent + O(h) successor search when the node has two children. |
| `size` (single tree)               | O(n)        | O(n)          | O(n)       | Recomputed by visiting every node on each call — no count is cached. |
| `print_*_order` (single tree)      | O(n)        | O(n)          | O(n)       | Visits every node exactly once. |
| `db_insert` / `db_remove_by_*`     | —           | O(log n)      | O(n)       | Touches both trees, so cost is the sum of both individual operations. |
| `db_query_by_*`                    | O(1)        | O(log n)      | O(n)       | Delegates to a single tree. |

**Space complexity:** O(n) for the stored nodes in each tree (the `User`
payloads themselves are owned by the caller, not by the trees), plus
O(h) auxiliary space for the recursion stack used by every recursive
operation.

> Note on `size()`: unlike a typical production dictionary, this
> implementation does not cache a node count — every call to `bst_uint_size`
> / `bst_str_size` / `db_size` walks the whole tree. This is accurate to the
> actual implementation and worth knowing if `size()` is called frequently
> in a hot loop.

## Project structure

```
bst-user-database/
├── README.md
├── Makefile
├── .gitignore
├── include/            # Public headers (interfaces)
│   ├── user.h
│   ├── bst_uint.h
│   ├── bst_str.h
│   └── database.h
├── src/                # Implementations
│   ├── user.c
│   ├── bst_uint.c
│   ├── bst_str.c
│   ├── database.c
│   └── main.c
└── tests/              # Assert-based unit tests
    ├── test_user.c
    ├── test_bst_uint.c
    ├── test_bst_str.c
    └── test_database.c
```

## Requirements

- A C11-compatible compiler (developed and tested with `gcc`).
- `make`.
- No external libraries; only the C standard library is used.

## Compilation and execution

```bash
make          # builds build/bst_user_database
./build/bst_user_database
```

`make clean` removes the `build/` directory.

## Tests

The `tests/` directory contains assert-based unit tests covering, for each
module: normal insertion/lookup, an empty structure, a single element,
duplicate keys, root removal, leaf removal, removal of a node with one and
with two children, and queries/removals for keys that do not exist.

```bash
make test
```

Each test binary prints its own `... : all tests passed` line and the
`test` target exits non-zero if any test binary fails (via `assert`).

## Example

Running `./build/bst_user_database` inserts 6 sample users, prints them
in-order by email, looks each one up by email, then removes them one at a
time (printing the tree after each removal). Excerpt of the output:

```
Id, Email, Name, Password
987, a@a.a, name6, password6
123, a@a.c, name1, password1
321, b@c.d, name4, password4
789, m@a.b, name3, password3
456, m@z.x, name2, password2
654, z@w.c, name5, password5

Found user: 123, a@a.c, name1, password1
...
```

## Known behavior / limitations

- **Duplicate keys are silently ignored.** If `insert` is called with a
  key (`id` or `email`) that already exists in that tree, the existing
  node is left untouched and the new value is not linked into the tree.
  This is the original insertion algorithm's behavior and has been left
  unchanged; it is documented here (and exercised by the test suite) so it
  isn't mistaken for an update operation.
- **The two indexes can, in principle, disagree** if a user is inserted
  with a duplicate `id` but a unique `email` (or vice versa): the record
  is silently dropped by one tree's duplicate-key rule but linked into the
  other. This follows directly from the point above and from `Database`
  composing two independently-keyed trees; it is not something this
  revision changes, since doing so would alter the original insertion
  logic rather than just clean it up.
- Trees are **not self-balancing**, so worst-case behavior degrades to
  O(n) under adversarial (e.g. sorted) insertion order, as noted in the
  complexity table above.

## Author

Rodrigo Antonio Gustinelli Secundo — Computer Science student at UFABC — [GitHub](https://github.com/rgustinelli)
