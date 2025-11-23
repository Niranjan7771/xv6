# How to Push to GitHub

Follow these steps to push your XV6 User Authentication project to GitHub.

## 📋 Prerequisites

1. ✅ GitHub account created
2. ✅ Git installed on your system
3. ✅ GitHub repository created (or ready to create)

## 🚀 Step-by-Step Instructions

### Step 1: Create GitHub Repository

1. Go to [GitHub](https://github.com)
2. Click the **"+"** icon → **"New repository"**
3. Fill in:
   - **Repository name**: `xv6-user-authentication` (or your choice)
   - **Description**: "User authentication and file permissions for XV6 OS"
   - **Visibility**: Public or Private
   - **DO NOT** initialize with README (we already have one)
4. Click **"Create repository"**
5. **Copy the repository URL** (looks like: `https://github.com/YOUR_USERNAME/xv6-user-authentication.git`)

### Step 2: Prepare Your Local Repository

Open terminal in your xv6-public directory and run:

```bash
# Clean build artifacts
cd xv6-source
make clean
cd ..

# Run the setup script
./setup_git.sh
```

### Step 3: Add GitHub Remote

Replace `YOUR_GITHUB_URL` with the URL you copied:

```bash
git remote add origin YOUR_GITHUB_URL
```

Example:
```bash
git remote add origin https://github.com/yourusername/xv6-user-authentication.git
```

### Step 4: Stage All Files

```bash
git add .
```

This adds all files except those in `.gitignore`.

### Step 5: Commit Your Changes

```bash
git commit -m "Initial commit: XV6 User Authentication & File Permissions

Features:
- User authentication system with login/logout
- File permissions with owner tracking
- Three user types (admin, user1, user2)
- Enhanced shell with tab completion
- New commands: whoami, chmod, logout, reboot
- Enhanced ls showing permissions
- Error messages for permission denied
- Comprehensive documentation

Bugs Fixed:
- Logout now properly exits shell
- Read-only files block writes for everyone
- Append (>>) now works correctly
- Added clear error messages"
```

### Step 6: Push to GitHub

```bash
# Set main as default branch
git branch -M main

# Push to GitHub
git push -u origin main
```

### Step 7: Verify on GitHub

1. Go to your GitHub repository URL
2. You should see:
   - ✅ README.md displayed on the main page
   - ✅ All source files
   - ✅ docs/ folder with documentation
   - ✅ No build artifacts (*.o, *.img, etc.)

## 🎉 Success!

Your project is now on GitHub! Share the URL with others.

## 📝 Making Future Changes

After the initial push, use this workflow:

```bash
# Make your changes to files

# Stage changes
git add .

# Commit with descriptive message
git commit -m "Description of changes"

# Push to GitHub
git push
```

## 🔧 Troubleshooting

### Problem: "remote origin already exists"

**Solution:**
```bash
git remote remove origin
git remote add origin YOUR_GITHUB_URL
```

### Problem: "Permission denied (publickey)"

**Solution:** You need to set up SSH keys or use HTTPS with personal access token.

For HTTPS:
```bash
git remote set-url origin https://github.com/YOUR_USERNAME/REPO_NAME.git
```

### Problem: "Updates were rejected"

**Solution:** Pull first, then push:
```bash
git pull origin main --rebase
git push origin main
```

### Problem: Files not showing up

**Solution:** Check .gitignore:
```bash
cat .gitignore
```

Make sure important files aren't ignored.

## 📊 What Gets Pushed

### ✅ Included
- All source code (*.c, *.h, *.S)
- Documentation (*.md, docs/*.txt)
- Makefile and build scripts
- README and project files

### ❌ Excluded (via .gitignore)
- Build artifacts (*.o, *.d)
- Binary files (kernel, *.img)
- Generated files
- Editor temporary files

## 🌟 Making Your Repository Stand Out

### Add Topics
On GitHub, click "Add topics" and add:
- `xv6`
- `operating-system`
- `authentication`
- `file-permissions`
- `educational`
- `c`
- `unix`

### Add Description
Edit the repository description:
> User authentication and file permissions implementation for MIT's XV6 operating system. Features login/logout, three user types, file ownership, permission checking, and enhanced shell.

### Pin Repository
If this is an important project, pin it to your profile!

## 📞 Need Help?

- Check [GitHub Docs](https://docs.github.com)
- Review [Git Basics](https://git-scm.com/book/en/v2/Getting-Started-Git-Basics)
- Ask in GitHub Issues

## ✨ Next Steps

After pushing:
1. ⭐ Star your own repository
2. 📝 Add a nice description
3. 🏷️ Add relevant topics
4. 📢 Share with others
5. 📊 Enable GitHub Pages (optional)

---

**Congratulations!** Your XV6 User Authentication project is now on GitHub! 🎉
