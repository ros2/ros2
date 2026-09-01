#!/usr/bin/env bash
# Checks that pixi.toml solves on every platform it declares and that the
# committed pixi.lock is what that solve produces.  Sets
# `outcome=current|unsolvable|stale` on ${GITHUB_OUTPUT} and leaves the
# regenerated pixi.lock in the working tree.

# The backticks below are Markdown for the step summary, not command
# substitution.
# shellcheck disable=SC2016
set -uo pipefail

GITHUB_OUTPUT="${GITHUB_OUTPUT:-/dev/null}"
GITHUB_STEP_SUMMARY="${GITHUB_STEP_SUMMARY:-/dev/null}"

# Checked up front: `git diff` cannot see an untracked file, so a missing lock
# would otherwise be reported as unsolvable below.
if [ ! -f pixi.lock ]; then
  echo '::error::pixi.lock is missing. Run `pixi lock` and commit the result.'
  exit 1
fi

if pixi lock --check --no-progress; then
  echo 'outcome=current' >> "${GITHUB_OUTPUT}"
  echo '`pixi.lock` is current and solves on every platform.' \
    >> "${GITHUB_STEP_SUMMARY}"
  exit 0
fi

# `--check` fails both for an unsolvable manifest and for a stale lock file, and
# rewrites pixi.lock as it goes.  Only the stale case moves the working tree.
if git diff --quiet -- pixi.lock; then
  echo 'outcome=unsolvable' >> "${GITHUB_OUTPUT}"
  {
    echo '### `pixi.toml` cannot be solved'
    echo ''
    echo 'At least one platform in `workspace.platforms` has no solution.'
    echo 'See the log above for the conflicting package.'
  } >> "${GITHUB_STEP_SUMMARY}"
  echo '::error::pixi.toml does not solve on every platform.'
  exit 1
fi

echo 'outcome=stale' >> "${GITHUB_OUTPUT}"
{
  echo '### `pixi.lock` does not match `pixi.toml`'
  echo ''
  echo 'This pull request changes the dependencies but does not carry the lock'
  echo 'file they produce. Run `pixi lock` and commit the result, or download'
  echo 'the `pixi-lock-suggested` artifact from this run and commit that file.'
  echo ''
  echo '```'
  git --no-pager diff --stat -- pixi.lock
  echo '```'
} >> "${GITHUB_STEP_SUMMARY}"
echo '::error::pixi.lock is out of date with pixi.toml.'
exit 1
