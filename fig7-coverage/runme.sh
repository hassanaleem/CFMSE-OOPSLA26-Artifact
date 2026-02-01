#!/usr/bin/env bash
set -euo pipefail
ulimit -s unlimited


MAIN_DIR="$(pwd)"

echo "Running experiments"
echo "Output PDFs will be copied to: $MAIN_DIR"
echo

# Copy PDFs from current directory into MAIN_DIR (if any exist).
copy_pdfs() {
  shopt -s nullglob
  local pdfs=( *.pdf )
  if ((${#pdfs[@]})); then
    cp -v -- "${pdfs[@]}" "$MAIN_DIR/"
  else
    echo "  (no PDFs to copy here)"
  fi
}

run_exp() {
  local dir="$1"
  local script="$2"

  echo "==> $dir: running $script"
  pushd "$dir" >/dev/null
  "./$script"
  copy_pdfs
  popd >/dev/null
  echo
}

run_group() {
  local base="$1"
  local script="$2"
  shift 2

  echo "=============================="
  echo "Running group: $base"
  echo "=============================="

  pushd "$base" >/dev/null
  for sub in "$@"; do
    run_exp "$sub" "$script"
  done
  popd >/dev/null
}

# ---- Chopper experiments ----
run_group "chopper-experiments" "run-cfm-driver.sh" \
  "libosip" \
  "libtasn"

# ---- Coreutils ----
echo "=============================="
echo "Running CoreUtils Experiments"
echo "=============================="
pushd "coreutils-6.11" >/dev/null
./run-cfm-benchmarks.sh
copy_pdfs
popd >/dev/null
echo

# ---- JSON ----
run_exp "json" "run-bench.sh"

# ---- Protobuf ----
run_exp "protobuf-c" "run-bench.sh"

# ---- UTF8 ----
run_exp "utf8.h" "run-bench.sh"

echo "All experiments completed."
