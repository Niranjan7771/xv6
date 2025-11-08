# xv6 Enhancements

## Overview
This tree extends the upstream xv6-public base with several user-facing utilities
and kernel improvements aimed at providing a more Unix-like experience while
maintaining the small xv6 codebase. The work adds new system calls, updates the
console driver to understand a subset of ANSI escape codes, and introduces
automated tests to preserve the new behavior.

## Added Features
- `getuid` system call and `whoami` user program for reporting the current user ID.
- **Persistent command history** in `sh` with circular buffer (200 commands), automatic save/load from `/.xv6_history`, and duplicate suppression.
- `history` user program to inspect recorded commands.
- `pstat` kernel interface and user command to display process accounting data.
- Standalone `clear` user program that emits standard ANSI sequences.
- Console driver support for `ESC[H`, `ESC[J`, and `ESC[2J` so ANSI-based tools
  like `clear` update both the serial and VGA consoles correctly.

## Implementation Notes
- User programs now live alongside kernel sources, with `Makefile` `VPATH` set to
  locate files under `user/` (for example `user/clear.c`).
- `console.c` contains a lightweight state machine that recognizes the minimal
  Control Sequence Introducer sequences required by the new utilities. The driver
  keeps UART output intact while updating the CGA buffer via helpers such as
  `cgahome` and `cgaclear`.
- `pstat` exposes per-process metadata by extending the process table with a new
  structure and copying it to user space through a dedicated system call.
- **Shell history**: `sh.c` maintains an in-memory circular buffer (200 entries) that persists commands to `/.xv6_history` after each command execution. On startup, the shell loads existing history. Commands are saved without duplicates. The file survives within a QEMU session but is reset when the filesystem image is rebuilt.

## Code Touchpoints
- `console.c`: new escape-sequence state machine inside `consputc`, plus VGA helpers `cgahome` and `cgaclear` to keep serial and CGA output aligned.
- `user/clear.c`: standalone ANSI clear utility used by interactive sessions and regression tests.
- `user/test_clear.sh`: non-interactive QEMU harness that verifies ESC-based clearing works on both serial and VGA consoles.
- **`sh.c`**: added `load_history()`, `save_history()`, `add_to_history()` functions with circular buffer logic; history loaded on startup, saved on exit; uses `/.xv6_history` file.
- **`user/test_history.sh`**: automated test that verifies history persistence within a single QEMU session by restarting the shell and checking file contents.
- `Makefile`: `VPATH` configured to find sources in `user/`, `UPROGS` extended with `_whoami`, `_clear`, `_history`, `_pstat`, and `grade` target scripted to exercise the new commands.
- `syscall.c`, `syscall.h`, `sysproc.c`, `usys.S`, `user.h`: wired `getuid` and `pstat` into the system call table and user stubs.
- `pstat.c`, `pstat.h`, `proc.c`, `defs.h`: defined the `struct pstat` ABI and implemented `fillpstat` to export process metadata from the kernel.
- `whoami.c`: minimal CLI around `getuid` mirroring GNU `whoami` behavior for xv6.
- `history.c`: standalone user program that reads and displays `/.xv6_history` (updated to read from new location).
- `kdebug.h`: optional kernel logging shim so extra instrumentation can be toggled without code churn.

## Testing
- `make` builds the kernel and user programs normally.
- `make qemu-nox` boots the image for manual exploration.
- `make grade` runs the automated checks, including the history and `pstat`
  exercises added for the new system calls.
- `user/test_clear.sh` performs a non-interactive regression test that boots xv6
  under QEMU, runs the `clear` command, and verifies that ANSI clear handling
  removes previous output before printing the prompt.
- **`user/test_history.sh`** validates persistent command history by: running commands in the first shell, exiting via Ctrl-D, checking that `/.xv6_history` exists in the restarted shell, and verifying file contents match the executed commands.

## Usage Notes
- The `clear` command is available in the xv6 shell path; invoking it clears both
  the QEMU serial console and the VGA display.
- **Command history**: Commands are automatically saved after each command execution to `/.xv6_history`. Type `history` to view all saved commands. The history persists within a QEMU session and survives shell restarts (within the same session).
- `pstat` may be run without arguments to print all tracked processes; combine it
  with `grep` for quick filtering in the shell.

## Limitations
- **Arrow-key navigation**: The current implementation uses line-buffered input (via `gets()`), so arrow keys are not processed character-by-character. To enable arrow-key history navigation, the console driver would need a "raw mode" that delivers each keystroke immediately, which requires modifying `console.c`'s input buffering logic.
- **History persistence across reboots**: The `/.xv6_history` file persists within a QEMU session but is lost when `make fs.img` rebuilds the filesystem. For true cross-reboot persistence, the history file would need to be included in the initial filesystem image or stored on a separate persistent disk.
- Duplicate commands at the end of history are suppressed, but duplicates elsewhere in history remain.

## Future Work Ideas
- Extend the ANSI parser to support cursor-relative motions and attribute changes.
- **Implement raw-mode console input** to enable character-by-character reading for arrow-key navigation and full readline-style editing.
- Add cross-reboot history persistence by including `/.xv6_history` in the base filesystem image or mounting a separate persistent volume.
- Implement `!N` command re-execution and reverse-search (Ctrl-R) for history.
- Add automated tests covering `pstat` edge cases and multi-user scenarios.
