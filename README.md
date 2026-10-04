# Operating Systems Coursework

C linked-list exercises and a paged virtual-memory simulator with LRU replacement.

## Original coursework

- CS 3733-001 and CS 3733-004 — Operating Systems, Spring 2025

Originally completed at the University of Texas at San Antonio and imported to GitHub later. This repository retains the coursework implementation with documented maintenance fixes and demonstration assets.

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

See DEVELOPMENT.md for compile commands and the synthetic backing-store generator.

## Scope and limitations

- The virtual-memory simulator requires a backing-store fixture that was excluded because this import contains source and text configuration only.
- The list driver/header includes supplied course scaffolding.

Only source code, build configuration, and required text inputs are included. Written submissions, assignment instructions, PDFs, videos, generated outputs, binary builds, and private configuration are omitted. Anonymized contributor labels and supplied-code comments retain the distinction between submitted work and scaffolding. No license for course-provided material is inferred.

## Development and reuse

See [DEVELOPMENT.md](DEVELOPMENT.md) for reproducible checks and known archival dependencies, [CONTRIBUTING.md](CONTRIBUTING.md) for contribution guidance, and [SECURITY.md](SECURITY.md) for private reports.

Reuse terms and provenance are documented in [NOTICE.md](NOTICE.md) and [LICENSE](LICENSE). The maintenance license does not grant rights to original course or team material.
