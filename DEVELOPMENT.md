# Development

Python 3.12 and GCC are required for `python tools/check_repository.py`.
The check compiles both supported C programs and exercises valid, empty,
malformed and truncated inputs for the virtual-memory simulator.

The original BACKING_STORE.bin was unavailable. Run `python
tools/generate_backing_store.py` to generate deterministic fictional page bytes.
From `virtual-memory-lru`, compile `gcc -std=c11 -Wall -Wextra main.c -o simulator`,
then run `./simulator` (Windows: `simulator.exe`). It reads addresses.txt and the
generated store in that directory. Generated backing stores and reports stay ignored.
This replacement demonstrates paging behavior; values will not match an original
assignment answer key. Snapshots are emitted only after their actual checkpoints.
