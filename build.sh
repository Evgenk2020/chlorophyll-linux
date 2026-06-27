#!/usr/bin/env bash

set -e

curr="$(cd "$(dirname "$0")" && pwd)"
bld_target="$curr/build"

mkdir -p "$bld_target"
cd "$bld_target"

cmake ..
cmake --build . --parallel
cpack

exec "$SHELL"