#!/bin/bash
PROJECT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." >/dev/null 2>&1 && pwd )"
echo Project Root: $PROJECT_DIR
pushd $PROJECT_DIR/build >/dev/null
./hello_fmt
popd >/dev/null