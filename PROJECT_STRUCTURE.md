# Project Structure

This document describes the organization of the XV6 User Authentication project.

## 📁 Directory Structure

```
xv6-public/
├── README.md                    # Main project documentation
├── CHANGELOG.md                 # Version history and changes
├── CONTRIBUTING.md              # Contribution guidelines
├── PROJECT_STRUCTURE.md         # This file
├── LICENSE                      # MIT License (from original XV6)
├── .gitignore                   # Git ignore rules
├── setup_git.sh                 # Git setup helper script
├── Makefile                     # Build configuration
│
├── docs/                        # Documentation folder
│   ├── README_FIRST.txt         # ⭐ Start here!
│   ├── DEMO_SCRIPT.txt          # Step-by-step demonstration
│   ├── EXPECTED_OUTPUT.txt      # Expected output for all tests
│   ├── QUICK_REFERENCE.txt      # Command reference card
│   ├── IMPLEMENTATION_DETAILS.txt  # Technical documentation
│   ├── BUGS_FIXED.txt           # Bug fixes explained
│   ├── APPEND_BUG_FIXED.txt     # Append operator fix
│   ├── ERROR_MESSAGES_ADDED.txt # Error message improvements
│   ├── TESTING_GUIDE.txt        # Testing instructions
│   ├── FINAL_VERIFICATION.txt   # Verification checklist
│   ├── SUMMARY.txt              # Project overview
│   ├── ALL_DONE.txt             # Completion status
│   └── DOCUMENTATION_INDEX.txt  # Documentation guide
│
├── kernel/                      # Kernel source files
│   ├── main.c                   # Kernel initialization
│   ├── proc.c                   # Process management (modified)
│   ├── syscall.c                # System call handling (modified)
│   ├── sysproc.c                # Process syscalls (modified - auth)
│   ├── sysfile.c                # File syscalls (modified - permissions)
│   ├── fs.c                     # File system (modified)
│   └── ...                      # Other kernel files
│
├── include/                     # Header files
│   ├── types.h                  # Type definitions
│   ├── stat.h                   # File stat structure (modified)
│   ├── file.h                   # File structures (modified)
│   ├── fs.h                     # File system structures (modified)
│   ├── proc.h                   # Process structures (modified)
│   ├── syscall.h                # System call numbers (modified)
│   ├── user.h                   # User-space API (modified)
│   ├── fcntl.h                  # File control (modified - O_APPEND)
│   ├── user_auth.h              # ⭐ NEW: Authentication structures
│   └── ...                      # Other headers
│
├── user/                        # User-space programs
│   ├── init.c                   # Init process (modified - login)
│   ├── sh.c                     # Shell (modified - tab, logout)
│   ├── ls.c                     # List files (modified - permissions)
│   ├── login.c                  # ⭐ NEW: Login program
│   ├── logout.c                 # ⭐ NEW: Logout program
│   ├── whoami.c                 # ⭐ NEW: Show current user
│   ├── chmod.c                  # ⭐ NEW: Change permissions
│   ├── reboot.c                 # ⭐ NEW: Reboot system
│   ├── ulib.c                   # User library (modified)
│   └── ...                      # Other user programs
│
└── build/                       # Build artifacts (gitignored)
    ├── *.o                      # Object files
    ├── *.d                      # Dependency files
    ├── kernel                   # Kernel binary
    ├── fs.img                   # File system image
    └── xv6.img                  # Bootable image
```

## 📝 File Categories

### Core Documentation
- `README.md` - Main entry point, quick start
- `CHANGELOG.md` - Version history
- `CONTRIBUTING.md` - How to contribute
- `PROJECT_STRUCTURE.md` - This file

### Documentation (docs/)
All user-facing documentation organized by purpose:
- **Getting Started**: README_FIRST.txt
- **Testing**: DEMO_SCRIPT.txt, EXPECTED_OUTPUT.txt, TESTING_GUIDE.txt
- **Reference**: QUICK_REFERENCE.txt, DOCUMENTATION_INDEX.txt
- **Technical**: IMPLEMENTATION_DETAILS.txt, BUGS_FIXED.txt
- **Status**: ALL_DONE.txt, FINAL_VERIFICATION.txt

### Modified Kernel Files
Files changed to implement authentication and permissions:
- `proc.c` - User credential management
- `syscall.c` - New system call registration
- `sysproc.c` - Authentication system calls
- `sysfile.c` - Permission checking
- `fs.c` - Save/load permissions

### Modified Headers
Headers updated with new fields and definitions:
- `stat.h` - Added uid, permissions to stat
- `file.h` - Added uid, permissions to inode
- `fs.h` - Added uid, permissions to dinode
- `proc.h` - Added uid, permissions to proc
- `syscall.h` - Added new system call numbers
- `fcntl.h` - Added O_APPEND flag

### New Files
Files created for this project:
- `user_auth.h` - Authentication structures
- `login.c` - Login program
- `logout.c` - Logout program
- `whoami.c` - Display current user
- `chmod.c` - Change file permissions
- `reboot.c` - Reboot system

### Modified User Programs
Existing programs enhanced:
- `init.c` - Login screen at boot
- `sh.c` - Tab completion, logout, append
- `ls.c` - Show permissions and owner
- `ulib.c` - Added getchar, strncmp

## 🔧 Build System

### Makefile Targets
- `make` - Build everything
- `make clean` - Remove build artifacts
- `make qemu` - Run with graphics
- `make qemu-nox` - Run without graphics (recommended)
- `make fs.img` - Build file system image

### Build Process
1. Compile kernel sources (*.c → *.o)
2. Link kernel binary
3. Compile user programs
4. Create file system image
5. Create bootable image

## 📦 What Gets Committed to Git

### Included
✅ Source files (*.c, *.h, *.S)
✅ Documentation (*.md, docs/*.txt)
✅ Build configuration (Makefile)
✅ Scripts (setup_git.sh)
✅ License and README files

### Excluded (via .gitignore)
❌ Build artifacts (*.o, *.d, *.asm, *.sym)
❌ Binary files (kernel, *.img, _*)
❌ Generated files (vectors.S, .gdbinit)
❌ Editor files (.vscode/, *.swp)
❌ OS files (.DS_Store)

## 🎯 Key Components

### Authentication System
- **Location**: `sysproc.c`, `user_auth.h`
- **Functions**: `sys_login()`, `sys_logout()`, `sys_getuid()`
- **Storage**: In-memory user database

### Permission System
- **Location**: `sysfile.c`, `fs.c`
- **Functions**: `sys_write()`, `sys_open()`, `sys_chmod()`
- **Storage**: On-disk in inode structure

### Shell Enhancements
- **Location**: `sh.c`
- **Features**: Tab completion, logout handling, append fix
- **Functions**: `tab_complete()`, `getcmd()`

### User Programs
- **Location**: `login.c`, `logout.c`, `whoami.c`, `chmod.c`, `reboot.c`
- **Purpose**: User-facing commands for authentication and permissions

## 📊 Statistics

### Code Changes
- **Lines Added**: ~2000+
- **Files Modified**: 25+
- **New Files**: 10+
- **Documentation**: 13 files (~100KB)

### Features
- **System Calls**: 5 new
- **Commands**: 5 new
- **Users**: 3 default
- **Permission Flags**: 4 types

## 🔍 Finding Things

### Looking for...
- **How to build?** → README.md, Makefile
- **How to test?** → docs/DEMO_SCRIPT.txt
- **How it works?** → docs/IMPLEMENTATION_DETAILS.txt
- **What changed?** → CHANGELOG.md
- **Bug fixes?** → docs/BUGS_FIXED.txt
- **Commands?** → docs/QUICK_REFERENCE.txt
- **Contributing?** → CONTRIBUTING.md

### Code Locations
- **Authentication**: `sysproc.c` (lines 100-200)
- **Permissions**: `sysfile.c` (sys_write, sys_open)
- **Login screen**: `init.c` (main function)
- **Tab completion**: `sh.c` (tab_complete function)
- **User database**: `sysproc.c` (users array)

## 🚀 Quick Navigation

```bash
# View main documentation
cat README.md

# Start testing
cat docs/README_FIRST.txt

# See all documentation
ls docs/

# Check what's changed
cat CHANGELOG.md

# Understand structure
cat PROJECT_STRUCTURE.md  # This file!
```

## 📞 Support

For questions about:
- **Structure**: This file
- **Building**: README.md
- **Testing**: docs/DEMO_SCRIPT.txt
- **Contributing**: CONTRIBUTING.md
- **Technical**: docs/IMPLEMENTATION_DETAILS.txt

---

**Last Updated**: November 23, 2025  
**Version**: 1.0.0
