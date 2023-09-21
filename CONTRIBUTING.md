# Contribution rules

The following subsections address how to contribute to the Space ROS project.

All contributors should follow these rules when submitting contributions to
Space ROS. These rules have been designed to simplify the process of
establishing compliance with requirements of space software.

## Commits

- All commits must reference the issue they address. *A consequence of this is
  that no commits can be made unless there is a corresponding issue for them.*

## Issues

- All issues being addressed must be assigned a milestone (ideally, prior to
  engaging in the work).

## Milestones

- All releases are tagged with their version number, which also corresponds to
  a milestone.

## Pull Requests

- All changes are incorporated via pull requests (even changes by the core
  team).

- All PR merges introduce a separate merge commit (i.e., git merge --no-ff),
  that closes the issue that the PR addresses, as well as any other issues
  that are fixed as a side effect, or that can no longer be reproduced after the
  change. The commit uses the syntax `Closes #<Ref>`, `Fix #<Ref>` or a command
  supported by github to automatically close the issue.

- There'll be a preference for PRs to address only one issue at a time, but
  we'll be flexible especially for cases in which a fix addresses multiple
  related issues at the same time (see point above).

- All PRs must be approved by a maintainer. When the author of the PR is one of
  the maintainers, a different maintainer must approve the PR.

- All PRs must pass the tests for the repository they are being committed to.

- The commit history must be clean. Contributors and maintainers are
  recommended to rebase and squash as needed *prior to accepting a PR and
  merging the changes*, so that the commits present how to introduce the change
  onto the HEAD in an understandable way (rather than describing all the
  intermediate steps taken until the final solution was discovered).
