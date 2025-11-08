clear feature

Design choices:
- Adds a user program `clear` that emits ANSI escape sequences to clear the terminal and move the cursor home.
- No kernel changes required.

Failure modes:
- Terminals that do not support ANSI sequences will not clear correctly.
- Runs entirely in userland and is safe.
