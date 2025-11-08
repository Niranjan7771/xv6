#!/bin/bash
# Non-interactive xv6 clear test: runs echo hello; clear; echo ok and inspects serial output.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

make --quiet fs.img xv6.img

log_file=$(mktemp)
trap 'rm -f "$log_file"' EXIT

{
  printf 'echo hello\nclear\necho ok\n';
  sleep 1
  printf '\001x'
} | make -s qemu-nox >"$log_file" 2>&1 || true

if ! grep -q "ok" "$log_file"; then
  echo "clear test: missing ok output" >&2
  exit 1
fi

ok_line=$(awk '/ok/{line=$0} END{print line}' "$log_file")
if printf '%s' "$ok_line" | grep -q 'hello'; then
  echo "clear test: hello persisted on ok line" >&2
  exit 1
fi

echo "clear test: passed"
exit 0
