
# See for detail: http://www.open3d.org/docs/release/tutorial/C++/cplusplus_interface.html
cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

project(open3d-point-cloud-visualizer)

# Find installed Open3D, this imports
#   Open3D_INCLUDE_DIRS
#   Open3D_LIBRARIES
#   Open3D_LIBRARY_DIRS
#   Open3D_C_FLAGS
#   Open3D_CXX_FLAGS
#   Open3D_EXE_LINKER_FLAGS
find_package(Open3D REQUIRED)

# link_directories must be before add_executable
link_directories(${Open3D_LIBRARY_DIRS})

# Open3D
if (Open3D_FOUND)
    message(STATUS "Found Open3D ${Open3D_VERSION}")
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${Open3D_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Open3D_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${Open3D_EXE_LINKER_FLAGS}")
set(CMAKE_CXX_STANDARD 14)

# Add target
add_executable(simple_pointcloud_visualizer simple_pointcloud_visualizer.cpp)
target_link_libraries(simple_pointcloud_visualizer ${Open3D_LIBRARIES})
target_include_directories(simple_pointcloud_visualizer PUBLIC ${Open3D_INCLUDE_DIRS})

# Add target
add_executable(TestVisualizer TestVisualizer.cpp)
target_link_libraries(TestVisualizer ${Open3D_LIBRARIES})
target_include_directories(TestVisualizer PUBLIC ${Open3D_INCLUDE_DIRS})


