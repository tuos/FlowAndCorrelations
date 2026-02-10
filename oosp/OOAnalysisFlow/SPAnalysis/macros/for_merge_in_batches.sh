#!/usr/bin/env bash
set -euo pipefail

# merge_in_batches.sh
# Usage:
#   ./merge_in_batches.sh output.root  "/store/.../nene_miniA*.root"
#   ./merge_in_batches.sh output.root file_with_paths.txt
#   ./merge_in_batches.sh output.root "/store/.../nene_*.root" "/other/pattern/*.root"
#
# The script accepts multiple patterns or file-list arguments after the output name.

if [ $# -lt 2 ]; then
  cat <<EOF
Usage: $0 OUTPUT.root PATTERN|LIST [PATTERN|LIST ...]
  PATTERN: shell glob (quote it or not). Example: "/store/.../nene_miniA*.root"
  LIST: a text file with one file path per line
Example:
  $0 merged_nene_tmp.root "/store/user/tuos/.../nene_miniA*.root"
  $0 merged.root file_with_paths.txt
EOF
  exit 1
fi

OUT="$1"
shift

# batch size (change if you want)
BATCH_SIZE=100

# temporary working dir
TMPDIR=$(mktemp -d -t hadd_batches.XXXXXX)
echo "Working in temporary dir: $TMPDIR"

# Collect files into an array `files`
declare -a files=()
for arg in "$@"; do
  if [ -f "$arg" ]; then
    # treat arg as a filelist
    while IFS= read -r line; do
      line="${line%%$'\r'}"   # strip possible CR
      [ -z "$line" ] && continue
      files+=("$line")
    done < "$arg"
  else
    # expand glob pattern safely using compgen (allows quoted globs)
    mapfile -t matches < <(compgen -G "$arg" 2>/dev/null || true)
    if [ ${#matches[@]} -eq 0 ]; then
      echo "Warning: pattern '$arg' matched no files" >&2
    else
      for m in "${matches[@]}"; do files+=("$m"); done
    fi
  fi
done

nfiles=${#files[@]}
if [ $nfiles -eq 0 ]; then
  echo "No input files found. Exiting."
  rm -rf "$TMPDIR"
  exit 2
fi

echo "Found $nfiles input files."

# If total files <= batch size -> just run hadd directly
if [ $nfiles -le $BATCH_SIZE ]; then
  echo "Number of files <= $BATCH_SIZE, doing single hadd to $OUT"
  hadd -f "$OUT" "${files[@]}"
  echo "Done. Output: $OUT"
  rm -rf "$TMPDIR"
  exit 0
fi

# Optionally detect if hadd supports -j (parallel merges)
HADD_PARALLEL_SUPPORTED=false
if hadd --help 2>&1 | grep -q -- '-j'; then
  HADD_PARALLEL_SUPPORTED=true
fi

# Merge in batches
batch_no=0
i=0
while [ $i -lt $nfiles ]; do
  batch_no=$((batch_no+1))
  start=$i
  end=$(( i + BATCH_SIZE - 1 ))
  if [ $end -ge $((nfiles-1)) ]; then end=$((nfiles-1)); fi

  # slice array
  batch=( "${files[@]:$start:$((end-start+1))}" )
  batch_file="$TMPDIR/batch_$(printf "%03d" "$batch_no").root"

  echo "Merging batch $batch_no: files $((start+1)) - $((end+1)) --> $batch_file (count=${#batch[@]})"

  if $HADD_PARALLEL_SUPPORTED; then
    # use -j 4 if supported (change if you want)
    hadd -f -j 4 "$batch_file" "${batch[@]}"
  else
    hadd -f "$batch_file" "${batch[@]}"
  fi

  # check exit
  if [ $? -ne 0 ]; then
    echo "Error: hadd failed on batch $batch_no" >&2
    exit 3
  fi

  i=$((end+1))
done

# Final merge of all batch files
tmp_batches=( "$TMPDIR"/batch_*.root )
echo "Merging ${#tmp_batches[@]} batch files into final output $OUT"
hadd -f "$OUT" "${tmp_batches[@]}"

echo "Final merge done: $OUT"

# Optional cleanup prompt
read -p "Delete temporary batch files in $TMPDIR ? [y/N] " yn
if [[ "$yn" =~ ^[Yy]$ ]]; then
  rm -rf "$TMPDIR"
  echo "Temporary files removed."
else
  echo "Temporary files left in: $TMPDIR"
fi

echo "All done."



