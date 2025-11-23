# Feature Overview

Single reference for the custom work added on top of upstream xv6.

## MLFQ Scheduler
- Introduces Multilevel Feedback Queue scheduling with three levels and a 100 tick boost interval (see `param.h`).
- `proc.c` maintains fixed-size per-level run queues, enqueue/dequeue helpers, requeue logic, and a rebuild routine used during boosts.
- `struct proc` (`proc.h`) now tracks `queue_level`, `ticks_in_quantum`, and `inqueue` so the scheduler knows each process's state.
- `scheduler()` consumes runnable processes via MLFQ order, and lifecycle hooks (`allocproc`, `fork`, `wakeup`, `kill`, etc.) ensure every RUNNABLE process is represented in exactly one queue.
- `mlfqtest` (see below) and manual QEMU sessions help validate responsiveness.

## Console Clear Command
- `console.c` exposes `consoleclear()` which wipes the CGA buffer while holding the console lock; it backs a new `sys_clearconsole()` syscall.
- Kernel surface (`defs.h`, `syscall.[ch]`, `sysproc.c`, `user.h`, `usys.S`) wires the syscall into user space.
- User program `clear.c` now invokes `clearconsole()` so `clear` mirrors Ubuntu's behavior instead of printing raw escape codes.

## Shell Exit Built-in
- `sh.c` checks for the literal `exit` before spawning children and terminates the shell immediately with a friendly message.
- Complements the existing `logout` path so both authenticated and generic sessions have a quick exit command.

## Shell History Built-in
- `sh.c` keeps a circular buffer (`MAX_HISTORY=32`) that records each non-empty command after it is read.
- A new `history` built-in prints the numbered list or reports when the buffer is empty, providing a lightweight recall mechanism similar to Ubuntu shells.

## mlfqtest Workload
- `mlfqtest.c` is bundled in the user image and launches a mix of CPU-bound, sleep-heavy, mixed, and interactive workers.
- Each worker logs its PID, iteration, and uptime ticks so you can observe demotions, responsiveness of I/O-friendly tasks, and periodic boosts in action.
- Run `mlfqtest` inside xv6 to generate sustained load while you interact with the shell.
