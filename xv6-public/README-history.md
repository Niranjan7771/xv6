history feature

Design choices:
- The shell (`sh.c`) appends each entered command line to a simple file `sh_history` in the root directory.
- Adds a user program `history` that prints this file.
- Keeps on-disk format minimal (plain text, one command per line).

Failure modes and notes:
- If the filesystem is full or file creation fails, history silently doesn't record (design choice to avoid breaking shell).
- No migration or format changes are needed for disk layout.
- Concurrency: since only the parent shell writes to the file and writes are atomic for small writes, simple append is sufficient for this usage.
