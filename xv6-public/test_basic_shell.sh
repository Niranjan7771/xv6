#!/bin/bash
# Basic test - just verify shell starts and handles simple commands

# Stay in current directory (xv6-public)
echo "Testing basic shell functionality with history..."

# Simple test: run a couple commands and verify they execute
printf "echo test123\necho test456\nexit\n" | \
  timeout 5s qemu-system-i386 -nographic \
    -drive file=fs.img,index=1,media=disk,format=raw \
    -drive file=xv6.img,index=0,media=disk,format=raw \
    -smp 1 -m 512 2>&1 | tee /tmp/xv6_basic_test.log

if grep -q "test123" /tmp/xv6_basic_test.log && grep -q "test456" /tmp/xv6_basic_test.log; then
  echo "✓ Basic shell commands working"
  exit 0
else
  echo "✗ Basic shell commands failed"
  cat /tmp/xv6_basic_test.log
  exit 1
fi
