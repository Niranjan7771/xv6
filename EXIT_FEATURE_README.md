# Shell `exit` Command Support

This document records the code changes that allow the xv6 shell to understand
an Ubuntu-like `exit` command, so users can terminate the shell (and therefore
“log out”) explicitly.

## xv6-source/sh.c
- Added a new built-in command check in the main shell loop: whenever the user
  inputs `exit` optionally followed by whitespace or a numeric status, the shell
  now prints `Exiting shell...` and terminates via `exit()`, rather than trying
  to exec a binary named `exit`.
- Retained the existing `logout` handling for authenticated sessions; `exit`
  acts as a generic convenience shortcut irrespective of login state.

## Usage
Type `exit` (with an optional status, e.g., `exit 0`) at the shell prompt.
The shell immediately quits without forking child processes, matching the
behavior users expect from Ubuntu and other Unix shells.
