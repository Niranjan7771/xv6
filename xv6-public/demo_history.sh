#!/bin/bash
echo "=== Demonstrating xv6 History Feature ==="
echo ""
echo "Starting xv6 and running some commands..."
echo ""

(sleep 0.5; printf "echo Hello World\nls\nwhoami\nhistory\n") | \
  timeout 8s qemu-system-i386 -nographic \
    -drive file=fs.img,index=1,media=disk,format=raw \
    -drive file=xv6.img,index=0,media=disk,format=raw \
    -smp 1 -m 512 2>&1 | \
  grep -A 20 "Hello World"

echo ""
echo "=== Demo Complete ==="
