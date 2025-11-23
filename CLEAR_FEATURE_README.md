# Clear Command Enhancements

This note explains the kernel/userland work required to make the `clear`
command behave like Ubuntu's terminal clear operation.

## Summary
- Introduced a kernel primitive (`consoleclear`) that wipes the CGA text buffer
  and homes the cursor while holding the console lock.
- Added a `clearconsole()` system call so user programs can request the clear
  operation safely.
- Updated the user-space `clear` utility to invoke the syscall instead of
  emitting unsupported ANSI escape codes.

## File-by-file Changes

### xv6-source/console.c
- Added `consoleclear_locked()` helper that writes blanks to the entire CGA
  buffer and resets the hardware cursor registers.
- Exported `consoleclear()` which acquires the console lock before invoking the
  helper, so callers (including syscalls) can safely refresh the screen.

### xv6-source/defs.h
- Declared `consoleclear()` to make the primitive available to other kernel
  components.

### xv6-source/syscall.h / syscall.c / sysproc.c
- Assigned syscall number `SYS_clearconsole`.
- Registered `sys_clearconsole()` in the syscall dispatch table.
- Implemented `sys_clearconsole()` to call into `consoleclear()`.

### xv6-source/user.h / usys.S
- Added the user-space prototype and trampoline (`clearconsole()`) so libc and
  applications can issue the syscall.

### xv6-source/clear.c
- Replaced the previous ANSI escape print with a call to `clearconsole()`, so
  the command now truly clears the xv6 console.

### xv6-source/Makefile
- (Earlier change) ensured the `_clear` binary is bundled into the disk image;
  no additional Makefile edits were needed for this fix.

## Usage
Rebuild the system (`make clean && make`) and boot xv6. Running `clear` at the
shell prompt now wipes the screen immediately, matching the behavior of the
Ubuntu `clear` command.
