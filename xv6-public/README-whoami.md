whoami feature

Design choices:
- Adds a minimal `getuid` syscall returning 0 (root) because xv6 has no user accounts.
- Adds a small user utility `whoami` that prints `root` when uid == 0 and `user<uid>` otherwise.

Failure modes and notes:
- Since xv6 lacks user database, `whoami` always reports `root` unless further user/account work is added.
- The syscall is cheap and safe; no on-disk changes.
