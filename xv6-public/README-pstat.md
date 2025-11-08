pstat feature

Design choices:
- Adds a kernel helper `fillpstat()` (in `proc.c`) that copies live process info into a `struct pstat` array.
- Adds a `pstat` syscall that copies up to N entries into user memory and returns the number of entries.
- Adds a user utility `pstat` that prints a simple table (PID, STATE, SIZE, NAME).
- The shared `pstat.h` header defines the small struct used by both kernel and userland.

Failure modes and notes:
- `pstat` reads process table under `ptable.lock` to avoid races.
- The syscall limits to 64 entries to keep kernel stack usage bounded; callers can request fewer or more (truncated to 64).
- No on-disk changes required.
