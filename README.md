# Dynamic String Library in C

A dynamic string library written in C from scratch, built as a learning project to understand memory management, pointers, and data structures.

## What it does

- **Dynamic resizing** — automatically grows the buffer using a doubling strategy for amortized O(1) append
- **Search** — find substrings, check prefixes/suffixes
- **Replace** — replace all or first occurrence of a substring
- **Split / Join** — split a string by delimiter, join an array of strings
- **Interpolation** — replace `{placeholders}` with values

## Files

| File | Purpose |
|---|---|
| `dynstr.h` | Struct definition and function declarations |
| `dynstr.c` | Full implementation of all functions |
| `main.c` | Test file demonstrating all features |

## How to compile and run
```bash
gcc main.c dynstr.c -o test
./test
```

## What I learned

- How heap memory works in C (`malloc`, `realloc`, `free`)
- Pointer arithmetic and why `found - s->data` gives an index
- Why buffer doubling gives amortized O(1) performance
- How to split a project across `.h` and `.c` files
