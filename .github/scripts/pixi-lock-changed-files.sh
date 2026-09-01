#!/usr/bin/env bash
# Sets `pixi=true|false` on ${GITHUB_OUTPUT} depending on whether the pull
# request touches the pixi files.  The workflow has no `paths:` filter because a
# filtered-out required check never reports, so it decides here instead.
#
# Environment: GH_TOKEN, GITHUB_REPOSITORY, PR_NUMBER.

set -euo pipefail

: "${GITHUB_REPOSITORY:?must be set}"
: "${PR_NUMBER:?must be set}"

# Unset outside Actions.
GITHUB_OUTPUT="${GITHUB_OUTPUT:-/dev/null}"
GITHUB_STEP_SUMMARY="${GITHUB_STEP_SUMMARY:-/dev/null}"

watched='pixi\.(toml|lock)|\.github/workflows/pixi-lock\.yaml|\.github/scripts/pixi-lock-[a-z-]+\.sh'

changed="$(gh api "repos/${GITHUB_REPOSITORY}/pulls/${PR_NUMBER}/files" \
  --paginate --jq '.[].filename')"

if grep -qxE "${watched}" <<< "${changed}"; then
  echo 'pixi=true' >> "${GITHUB_OUTPUT}"
  echo 'Pixi files changed.'
else
  echo 'pixi=false' >> "${GITHUB_OUTPUT}"
  echo 'No pixi files changed.' | tee -a "${GITHUB_STEP_SUMMARY}"
fi
