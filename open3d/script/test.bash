#!/bin/bash
PROJECT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." >/dev/null 2>&1 && pwd )"
echo Project Root: $PROJECT_DIR
pushd $PROJECT_DIR/build >/dev/null
./simple_pointcloud_visualizer "${PROJECT_DIR}/resource/50.pcd"
./TestVisualizer pointcloud "${PROJECT_DIR}/resource/50.pcd"
popd >/dev/null