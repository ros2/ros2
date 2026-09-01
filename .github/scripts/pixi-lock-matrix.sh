#!/usr/bin/env bash
# Builds the install matrix from `workspace.platforms` and writes it to
# ${GITHUB_OUTPUT}, so adding a platform starts testing it here.  An unmapped
# platform is an error rather than a silently skipped one.

set -euo pipefail

GITHUB_OUTPUT="${GITHUB_OUTPUT:-/dev/null}"

runner_for() {
  case "$1" in
    linux-64) echo ubuntu-latest ;;
    linux-aarch64) echo ubuntu-24.04-arm ;;
    win-64) echo windows-latest ;;
    osx-64) echo macos-15-intel ;;
    osx-arm64) echo macos-latest ;;
    *)
      echo "::error::No runner is mapped for platform '$1'. Add one here." >&2
      return 1
      ;;
  esac
}

# The list also carries a synthetic entry for the running machine, which belongs
# to no environment.
platforms="$(pixi workspace platform list --json \
  | jq -r '.platforms[] | select(.environments | length > 0) | .name' \
  | sort -u)"

include=''
while read -r platform; do
  [ -n "${platform}" ] || continue
  runner="$(runner_for "${platform}")"
  include+="$(jq -nc --arg p "${platform}" --arg r "${runner}" \
    '{platform: $p, runner: $r}')"$'\n'
done <<< "${platforms}"

matrix="$(jq -sc '{include: .}' <<< "${include}")"
echo "matrix=${matrix}" >> "${GITHUB_OUTPUT}"
echo "${matrix}"
