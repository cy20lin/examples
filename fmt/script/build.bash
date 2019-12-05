
#!/bin/bash
PROJECT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." >/dev/null 2>&1 && pwd )"
echo Project Root: $PROJECT_DIR
pushd "${PROJECT_DIR}"
mkdir -p build
cd build
cmake ..
cmake --build .
popd