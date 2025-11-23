#!/bin/bash

# XV6 User Authentication - Git Setup Script
# This script helps you push the project to GitHub

echo "=========================================="
echo "XV6 User Authentication - Git Setup"
echo "=========================================="
echo ""

# Check if git is initialized
if [ ! -d ".git" ]; then
    echo "Initializing git repository..."
    git init
    echo "✓ Git initialized"
else
    echo "✓ Git already initialized"
fi

# Add .gitignore
echo ""
echo "Setting up .gitignore..."
if [ -f ".gitignore" ]; then
    echo "✓ .gitignore exists"
else
    echo "⚠ .gitignore not found!"
fi

# Clean build artifacts
echo ""
echo "Cleaning build artifacts..."
make clean > /dev/null 2>&1
echo "✓ Build artifacts cleaned"

# Show what will be committed
echo ""
echo "Files to be committed:"
echo "----------------------------------------"
git status --short 2>/dev/null || echo "Run: git add ."
echo "----------------------------------------"

echo ""
echo "Next steps:"
echo "1. Add your GitHub repository:"
echo "   git remote add origin YOUR_GITHUB_URL"
echo ""
echo "2. Add all files:"
echo "   git add ."
echo ""
echo "3. Commit:"
echo "   git commit -m 'Initial commit: XV6 User Authentication & File Permissions'"
echo ""
echo "4. Push to GitHub:"
echo "   git branch -M main"
echo "   git push -u origin main"
echo ""
echo "=========================================="
echo "Ready to push to GitHub!"
echo "=========================================="
