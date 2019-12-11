cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)

project(imgui_demo)

add_library(imgui 
    third_party/imgui/imconfig.h
    third_party/imgui/imgui.cpp
    third_party/imgui/imgui_demo.cpp
    third_party/imgui/imgui_draw.cpp
    third_party/imgui/imgui.h
    third_party/imgui/imgui_internal.h
    third_party/imgui/imgui_widgets.cpp
    third_party/imgui/imstb_rectpack.h
    third_party/imgui/imstb_textedit.h
    third_party/imgui/imstb_truetype.h
)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_library(imgui_impl
    third_party/imgui/examples/imgui_impl_glfw.cpp # platform binding
    third_party/imgui/examples/imgui_impl_opengl3.cpp # renderer binding
)
target_include_directories(imgui_impl PRIVATE third_party/imgui)

# demo.cpp is taken from imgui (v1.74) 
# path: imgui/examples/example_glfw_opengl3/main.cpp
add_executable(imgui_demo demo.cpp)
target_include_directories(imgui_demo PRIVATE third_party/imgui)
target_include_directories(imgui_demo PRIVATE third_party/imgui/examples)
target_link_libraries(imgui_demo OpenGL::GL)
target_link_libraries(imgui_demo GLEW::GLEW)
target_link_libraries(imgui_demo glfw)
target_link_libraries(imgui_demo imgui)
target_link_libraries(imgui_demo imgui_impl)

# demo.cpp is taken from imgui (v1.74) 
# path: imgui/examples/example_glfw_opengl3/main.cpp
add_executable(imgui_demo2 demo_with_triangle_in_background.cpp)
target_include_directories(imgui_demo2 PRIVATE third_party/imgui)
target_include_directories(imgui_demo2 PRIVATE third_party/imgui/examples)
target_link_libraries(imgui_demo2 OpenGL::GL)
target_link_libraries(imgui_demo2 GLEW::GLEW)
target_link_libraries(imgui_demo2 glfw)
target_link_libraries(imgui_demo2 imgui)
target_link_libraries(imgui_demo2 imgui_impl)

# demo.cpp is taken from imgui (v1.74) 
# path: imgui/examples/example_glfw_opengl3/main.cpp
add_executable(imgui_demo3 demo_with_window_in_background.cpp)
target_include_directories(imgui_demo3 PRIVATE third_party/imgui)
target_include_directories(imgui_demo3 PRIVATE third_party/imgui/examples)
target_link_libraries(imgui_demo3 OpenGL::GL)
target_link_libraries(imgui_demo3 GLEW::GLEW)
target_link_libraries(imgui_demo3 glfw)
target_link_libraries(imgui_demo3 imgui)
target_link_libraries(imgui_demo3 imgui_impl)

# Build example directly from imgui example source code
# without modifing its source
add_executable(imgui_native_demo third_party/imgui/examples/example_glfw_opengl3/main.cpp)
target_compile_definitions(imgui_native_demo PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLEW)
target_include_directories(imgui_native_demo PRIVATE third_party/imgui)
target_include_directories(imgui_native_demo PRIVATE third_party/imgui/examples)
target_link_libraries(imgui_native_demo OpenGL::GL)
target_link_libraries(imgui_native_demo GLEW::GLEW)
target_link_libraries(imgui_native_demo glfw)
target_link_libraries(imgui_native_demo imgui)
target_link_libraries(imgui_native_demo imgui_impl)