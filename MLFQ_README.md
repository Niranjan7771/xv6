# MLFQ Scheduler Change Log

This document enumerates every repository file touched so far while implementing
the Multilevel Feedback Queue scheduler and related build fixes.

## xv6-source/Makefile
- Simplified toolchain detection: if `i686-elf-gcc` exists in `PATH`, keep the
  `i686-elf-` prefix, otherwise fall back to the host toolchain automatically.
- Removes the older shell script block that failed the build when a cross
  compiler was not installed, making native Linux builds work out of the box.
- Adds the `_clear` user program to the `UPROGS` list so it is packaged into
  the root file system image.

## xv6-source/param.h
- Declares global MLFQ configuration knobs:
  - `MLFQ_LEVELS` set to three priority levels.
  - `BOOST_INTERVAL` set to 100 timer ticks for periodic priority boosts.

## xv6-source/proc.h
- Extends `struct proc` with scheduler bookkeeping:
  - `queue_level` to record the current priority level.
  - `ticks_in_quantum` to count timer ticks consumed in the active timeslice.
  - `inqueue` boolean flag to track whether the process currently resides in a
    run queue.

## xv6-source/proc.c
- Adds an array of per-level run queues (`runqueues`) with fixed-size circular
  buffers plus helper functions: initialization, enqueue/dequeue, picking the
  next runnable process, requeueing, and rebuilding queues after a boost.
- Initializes the MLFQ subsystem inside `pinit()` and resets per-process
  bookkeeping inside `allocproc()` and when releasing process structures.
- Places newly runnable processes (init, forked children, wakeups, killed
  sleepers) into the correct queue with their quantum counters reset.
- Replaces the old linear scan scheduler with an MLFQ-aware scheduler loop that
  dequeues according to priority, sets `ticks_in_quantum` back to zero on
  context switch, and requeues a process when it yields but stays runnable.
- Ensures lifecycle transitions such as `wakeup()` and `kill()` keep queue state
  consistent, and provides a rebuild helper invoked during future boost events.

## xv6-source/clear.c
- New user program that emits the ANSI escape sequence `ESC[2J ESC[H]` to clear
  the console display and place the cursor in the upper-left corner, mirroring
  the UX of Ubuntu's `clear` command.

## xv6-source/mlfqtest.c
- User-space workload generator that now launches a heavier mix of CPU-bound,
  sleep-heavy, mixed, and interactive workers, each running dozens of rounds
  with varied spin/sleep patterns.
- The richer log stream makes it easier to confirm that CPU hogs get demoted,
  interactive workers stay responsive, and periodic boosts eventually cycle
  everyone back to the top queue.
