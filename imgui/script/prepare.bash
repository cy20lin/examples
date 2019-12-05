#!/bin/bash
PROJECT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." >/dev/null 2>&1 && pwd )"
echo Project Root: $PROJECT_DIR
pushd $PROJECT_DIR >/dev/null
mkdir -p third_party
cd third_party
touch .gitkeep
git clone https://github.com/ocornut/imgui
cd imgui
git checkout v1.74
popd >/dev/null