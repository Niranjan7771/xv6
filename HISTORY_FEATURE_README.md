# Shell History Command

Adds an `history` built-in to the xv6 shell so users can review their recent
commands just like in Ubuntu.

## Implementation Notes
- `xv6-source/sh.c`
  - Introduces a ring buffer (`MAX_HISTORY = 32`) that stores the most recent
    non-empty commands entered at the shell prompt. Each entry is trimmed of the
    trailing newline before storage.
  - Adds helpers `history_add()` and `history_print()` to manage the buffer and
    render the numbered list.
  - Hooks `history_add()` into the main REPL loop so every command is captured
    before any built-in handling mutates the buffer.
  - Implements a `history` built-in that prints the recorded commands with
    ordinal numbers, or reports when the buffer is empty.

## Usage
At the xv6 shell prompt simply type:
```
history
```
You will see up to the last 32 commands entered in the session, numbered in the
order they were run. The buffer wraps automatically as new commands arrive.
