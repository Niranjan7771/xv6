# XV6 User Authentication & File Permissions

A comprehensive implementation of user authentication, file permissions, and enhanced shell features for the XV6 operating system.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-xv6-orange.svg)
![Language](https://img.shields.io/badge/language-C-green.svg)

## 📂 Repository Structure

```
xv6-user-authentication/
├── README.md                    # You are here
├── CHANGELOG.md                 # Version history
├── CONTRIBUTING.md              # How to contribute
├── docs/                        # All documentation (13 files)
│   ├── README_FIRST.txt         # ⭐ Start here
│   ├── DEMO_SCRIPT.txt          # Step-by-step demo
│   └── ...
└── xv6-source/                  # All XV6 source code
    ├── Makefile                 # Build system
    ├── *.c, *.h, *.S            # Source files
    └── ...
```

## 🎯 Features

- ✅ **User Authentication System** - Login/logout with username and password
- ✅ **File Permissions** - Owner-based access control with read/write permissions
- ✅ **Three User Types**:
  - `admin/admin` - Full access (read, write, chmod)
  - `user1/pass1` - Read-only access
  - `user2/pass2` - Read and write access
- ✅ **Enhanced Shell**:
  - Tab completion for filenames
  - User-specific prompt (admin$, user1$, user2$)
  - Built-in logout command
- ✅ **New Commands**:
  - `whoami` - Display current user
  - `chmod` - Change file permissions (admin only)
  - `logout` - Logout and return to login screen
  - `reboot` - Reboot the system
- ✅ **Enhanced ls** - Shows permissions (rwxa format) and owner UID
- ✅ **Error Messages** - Clear feedback for permission denied operations

## 🚀 Quick Start

### Build and Run

```bash
cd xv6-source
make clean
make
make qemu-nox
```

### Login

```
Username: admin
Password: admin
```

### Try It Out

```bash
admin$ whoami
admin (uid: 1)

admin$ echo "Hello World" > test.txt
admin$ ls
rw-- test.txt       uid:1 2 24 12

admin$ chmod test.txt 1
admin$ ls
r--- test.txt       uid:1 2 24 12

admin$ echo "try to write" >> test.txt
Permission denied: cannot open read-only file for writing

admin$ logout
```

## 📚 Documentation

All documentation is in the `docs/` folder:

- **[START HERE](docs/README_FIRST.txt)** - Quick start guide
- **[DEMO_SCRIPT.txt](docs/DEMO_SCRIPT.txt)** - Step-by-step demonstration (18 tests)
- **[EXPECTED_OUTPUT.txt](docs/EXPECTED_OUTPUT.txt)** - Exact output for every test
- **[QUICK_REFERENCE.txt](docs/QUICK_REFERENCE.txt)** - Command reference card

### Technical Documentation

- [IMPLEMENTATION_DETAILS.txt](docs/IMPLEMENTATION_DETAILS.txt) - Complete technical documentation
- [BUGS_FIXED.txt](docs/BUGS_FIXED.txt) - Bug fixes explained
- [APPEND_BUG_FIXED.txt](docs/APPEND_BUG_FIXED.txt) - Append (>>) fix
- [ERROR_MESSAGES_ADDED.txt](docs/ERROR_MESSAGES_ADDED.txt) - Error message improvements

### Testing

- [TESTING_GUIDE.txt](docs/TESTING_GUIDE.txt) - Comprehensive testing instructions
- [FINAL_VERIFICATION.txt](docs/FINAL_VERIFICATION.txt) - Verification checklist

## 🔐 Default Users

| Username | Password | UID | Permissions | Description |
|----------|----------|-----|-------------|-------------|
| admin | admin | 1 | Read, Write, Execute, Admin | Full system access |
| user1 | pass1 | 2 | Read, Execute | Read-only user |
| user2 | pass2 | 3 | Read, Write, Execute | Regular user |

## 📝 Permission Flags

Files display permissions in `rwxa` format:
- `r` = Read permission
- `w` = Write permission
- `x` = Execute permission
- `a` = Admin permission

Example: `rw--` means read+write, no execute, no admin

## 🛠️ New Commands

### whoami
Display current logged-in user and UID
```bash
admin$ whoami
admin (uid: 1)
```

### chmod
Change file permissions (admin only)
```bash
admin$ chmod file.txt 1    # Read-only
admin$ chmod file.txt 3    # Read+Write
```

### logout
Logout and return to login screen
```bash
admin$ logout
Logged out successfully. Exiting shell...
```

### reboot
Reboot the system
```bash
admin$ reboot
```

### ls (enhanced)
Shows permissions and owner UID
```bash
admin$ ls
rw-- README         uid:1 2 1 2286
rw-- test.txt       uid:1 2 24 12
```

### Tab Completion
Press TAB to auto-complete filenames
```bash
admin$ cat RE<TAB>
admin$ cat README
```

## 🐛 Bugs Fixed

1. ✅ **Logout Bug** - Logout now properly exits shell and returns to login
2. ✅ **Permission Bug** - Read-only files now block writes for everyone (including owner)
3. ✅ **Append Bug** - `>>` now correctly appends instead of overwriting
4. ✅ **Error Messages** - Added clear error messages for permission denied

## 🏗️ Architecture

### Modified Files

**Kernel Headers:**
- `stat.h`, `file.h`, `fs.h`, `proc.h` - Added uid and permissions fields
- `syscall.h` - Added new system calls
- `fcntl.h` - Added O_APPEND flag
- `user_auth.h` - New authentication structures

**Kernel Source:**
- `syscall.c`, `usys.S` - System call registration
- `sysproc.c` - Authentication implementation
- `sysfile.c` - Permission checking and error messages
- `fs.c` - Save/load permissions to/from disk
- `proc.c` - User credential management

**User Programs:**
- `init.c` - Login screen at boot
- `sh.c` - Tab completion, logout handling, append fix
- `ls.c` - Display permissions and owner

**New Programs:**
- `login.c`, `logout.c`, `whoami.c`, `chmod.c`, `reboot.c`

## 🧪 Testing

### Quick Test
```bash
$ cd xv6-source
$ make qemu-nox
Username: admin
Password: admin

admin$ echo "line 1" > test.txt
admin$ echo "line 2" >> test.txt
admin$ cat test.txt
line 1
line 2

admin$ chmod test.txt 1
admin$ echo "should fail" >> test.txt
Permission denied: cannot open read-only file for writing

admin$ logout
```

### Comprehensive Testing
See [DEMO_SCRIPT.txt](docs/DEMO_SCRIPT.txt) for 18 detailed test scenarios.

## 📊 Project Statistics

- **Lines of Code Added:** ~2000+
- **Files Modified:** 25+
- **New Programs:** 5
- **Documentation:** 13 comprehensive files (~100KB)
- **Features Implemented:** 9
- **Bugs Fixed:** 4

## 🎓 Educational Value

This project demonstrates:
- Operating system security concepts
- User authentication mechanisms
- File permission systems
- System call implementation
- Shell enhancements
- Error handling and user feedback

## 🤝 Contributing

This is an educational project based on MIT's XV6 operating system. Feel free to:
- Report issues
- Suggest improvements
- Fork and experiment
- Use for learning

## 📄 License

Based on XV6, which is licensed under the MIT License.

## 🙏 Acknowledgments

- MIT CSAIL for the original XV6 operating system
- The XV6 book and documentation
- All contributors to the XV6 project

## 📧 Contact

- **Author**: AnjaniNithin
- **GitHub**: [@Nithinchalamchala](https://github.com/Nithinchalamchala)
- **Repository**: [XV6_Modified](https://github.com/Nithinchalamchala/xv6-enhanced-kernel)

---

**Status:** ✅ Complete and Working  
**Last Updated:** November 23, 2025  
**Version:** 1.0.0
# xv6
# xv6
