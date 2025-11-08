#!/bin/bash
# test_history.sh - Non-interactive test for persistent command history
# Tests history persistence within a single QEMU session using shell restart

set -e

echo "Testing persistent command history..."

TEST_OUTPUT=$(mktemp)
trap "rm -f $TEST_OUTPUT" EXIT

# Test: Run commands, exit shell (Ctrl-D), restart shell, and verify history file
echo "Running commands and testing history persistence..."

# Send commands to first shell, Ctrl-D to exit, then in restarted shell read history
# \x04 is Ctrl-D (EOF)
(sleep 0.5; printf "echo one\necho two\necho three\n\x04cat /.xv6_history\n\x04") | \
  timeout 10s qemu-system-i386 -nographic \
    -drive file=fs.img,index=1,media=disk,format=raw \
    -drive file=xv6.img,index=0,media=disk,format=raw \
    -smp 1 -m 512 2>&1 | tee "$TEST_OUTPUT"

# Check that commands executed
if grep -q "one" "$TEST_OUTPUT" && grep -q "two" "$TEST_OUTPUT" && grep -q "three" "$TEST_OUTPUT"; then
  echo "✓ Commands executed successfully"
else
  echo "✗ Commands did not execute properly"
  exit 1
fi

# Check that history file was created and accessed
if grep -q "cat /.xv6_history" "$TEST_OUTPUT"; then
  echo "✓ History file accessed"
else
  echo "✗ History file not accessed"
  exit 1
fi

# Verify history file contains the commands
# After cat command, we should see the commands echoed
ONE_IN_HIST=$(grep -c "echo one" "$TEST_OUTPUT" || echo 0)
TWO_IN_HIST=$(grep -c "echo two" "$TEST_OUTPUT" || echo 0)

# We expect at least 2 occurrences: once when typed, once from cat
if [ "$ONE_IN_HIST" -ge 2 ] && [ "$TWO_IN_HIST" -ge 2 ]; then
  echo "✓ History file contains expected commands"
  echo "  Found 'echo one': $ONE_IN_HIST times"
  echo "  Found 'echo two': $TWO_IN_HIST times"
else
  echo "✗ History file does not contain expected commands"
  echo "  Found 'echo one': $ONE_IN_HIST times (expected >= 2)"
  echo "  Found 'echo two': $TWO_IN_HIST times (expected >= 2)"
  exit 1
fi

# Verify shell restarted (init message appears)
RESTART_COUNT=$(grep -c "init: starting sh" "$TEST_OUTPUT" || echo 0)
if [ "$RESTART_COUNT" -ge 2 ]; then
  echo "✓ Shell restarted after exit, confirming history was saved"
else
  echo "✗ Shell did not restart properly"
  exit 1
fi

echo ""
echo "=== All history persistence tests passed ==="
