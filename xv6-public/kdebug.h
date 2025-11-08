// Kernel debug macro header
#ifndef KDEBUG_H
#define KDEBUG_H

// Set to 1 to enable kernel debug prints compiled via cprintf_debug
#ifndef KDEBUG
#define KDEBUG 0
#endif

#if KDEBUG
#define cprintf_debug(...) cprintf(__VA_ARGS__)
#else
#define cprintf_debug(...) do { } while(0)
#endif

#endif
