#!/usr/bin/env bash

set -u

failures=0

pass() {
  printf 'PASS: %s\n' "$1"
}

fail() {
  printf 'FAIL: %s\n' "$1"
  failures=$((failures + 1))
}

require_file() {
  local path="$1"
  local description="$2"
  if [[ -f "$path" && -s "$path" ]]; then
    pass "$description"
  else
    fail "$description — missing or empty: $path"
  fi
}

require_text_length() {
  local path="$1"
  local minimum="$2"
  local description="$3"
  if [[ -f "$path" ]] && [[ $(wc -c < "$path") -ge "$minimum" ]]; then
    pass "$description"
  else
    fail "$description — add meaningful content to $path"
  fi
}

printf '%s\n' '=== Professional Portfolio automatic checks ==='

require_text_length "README.md" 300 "Main portfolio README"
require_text_length "TESTING.md" 250 "Testing record"
require_text_length "REFLECTION.md" 250 "Course reflection"
require_text_length "01-early-program/README.md" 200 "Early-program explanation"
require_text_length "02-midcourse-program/README.md" 200 "Mid-course explanation"
require_text_length "03-brobank/README.md" 300 "BroBank explanation"

require_file "03-brobank/main.c" "BroBank main.c"
require_file "03-brobank/bank.c" "BroBank bank.c"
require_file "03-brobank/bank.h" "BroBank bank.h"
require_file "03-brobank/sample_input.txt" "BroBank sample input"
require_file "03-brobank/sample_output.txt" "BroBank expected output"

diagram_count=$(find diagrams -maxdepth 1 -type f \( -iname '*.png' -o -iname '*.jpg' -o -iname '*.jpeg' -o -iname '*.pdf' -o -iname '*.svg' \) 2>/dev/null | wc -l)
if [[ "$diagram_count" -ge 1 ]]; then
  pass "At least one diagram or visualization"
else
  fail "Add at least one PNG, JPG, PDF, or SVG file to diagrams/"
fi

mapfile -d '' c_sources < <(find 03-brobank -maxdepth 1 -type f -name '*.c' -print0)
if [[ ${#c_sources[@]} -gt 0 ]]; then
  if gcc -std=c11 -Wall -Wextra -pedantic "${c_sources[@]}" -o /tmp/brobank_portfolio_check; then
    pass "BroBank compiles with GCC"
    if timeout 10s /tmp/brobank_portfolio_check < 03-brobank/sample_input.txt > /tmp/brobank_actual.txt; then
      pass "BroBank runs with sample input"
      if [[ -s /tmp/brobank_actual.txt ]]; then
        pass "BroBank produces output for the showcase"
      else
        fail "BroBank ran but did not produce any output"
      fi
    else
      fail "BroBank did not finish successfully within 10 seconds"
    fi
  else
    fail "BroBank does not compile"
  fi
else
  fail "No C source files found in 03-brobank/"
fi

unwanted=$(find . -type f \( -name '*.exe' -o -name '*.o' -o -name '*.obj' -o -name '*.out' -o -name '.env' \) -print)
if [[ -z "$unwanted" ]]; then
  pass "No compiled files or .env secrets detected"
else
  fail "Remove compiled files or secrets from the repository"
  printf '%s\n' "$unwanted"
fi

printf '\nTotal failed checks: %d\n' "$failures"

if [[ "$failures" -gt 0 ]]; then
  exit 1
fi

printf '%s\n' 'All automatic portfolio checks passed.'
