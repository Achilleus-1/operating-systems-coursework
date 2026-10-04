# Operating Systems Coursework

C linked-list exercises and a paged virtual-memory simulator with LRU replacement.

## Original coursework

- CS 3733-001 and CS 3733-004 — Operating Systems, Spring 2025

Originally completed at the University of Texas at San Antonio during the terms above and imported to GitHub later. This repository preserves the submitted implementation; repository documentation and import housekeeping were added separately.

**Languages and technologies:** C, POSIX/Unix toolchain, Make.

## Implementation

- The linked-list implementation used by a supplied C refresher driver.
- Logical-to-physical address translation with a 256-page virtual address space and 128 physical frames.
- LRU page replacement, page-fault counting, and page-table snapshots.

## Concepts

- Page/offset decomposition, backing-store reads, replacement policy bookkeeping, and dynamic list operations.

## Repository layout

| Directory | Contents |
|---|---|
| `linked-list-refresh` | List implementation and supplied driver |
| `virtual-memory-lru` | Address translation and LRU simulator |

## Running the source

Build the linked-list exercise with its supplied Makefile. Compile virtual-memory-lru/main.c with a C compiler. That program expects addresses.txt and BACKING_STORE.bin in its working directory; the binary backing store is deliberately not imported.

## Scope and limitations

- The virtual-memory simulator requires a backing-store fixture that was excluded because this import contains source and text configuration only.
- The list driver/header includes supplied course scaffolding.

Only source code, build configuration, and required text inputs are included. Written submissions, assignment instructions, PDFs, videos, generated outputs, binary builds, and private configuration are omitted. Anonymized contributor labels and supplied-code comments retain the distinction between submitted work and scaffolding. No license for course-provided material is inferred.
