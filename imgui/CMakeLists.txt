cmake_minimum_required(VERSION 3.1)

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

add_executable(imgui_demo demo.cpp)
target_include_directories(imgui_demo PRIVATE third_party/imgui)
target_link_libraries(imgui_demo OpenGL::GL)
target_link_libraries(imgui_demo GLEW::GLEW)
target_link_libraries(imgui_demo glfw)
target_link_libraries(imgui_demo imgui)
target_link_libraries(imgui_demo imgui_impl)

